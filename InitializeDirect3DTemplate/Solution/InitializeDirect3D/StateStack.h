
#pragma once
#include "StateIdentifiers.h"
#include "../../Common/GameTimer.h"
#include "State.h"
#include "CommandQueue.h"// add it for input
#include "Command.h"// add it for input

#include <vector>
#include <utility>
#include <functional>
#include <map>




class StateStack 
{
public:
	enum Action
	{
		Push,
		Remove, 
		Pop,
		Clear,

	};


public:
	explicit			StateStack(State::Context context);


	template <typename T>
	void				registerState(States::ID stateID);

	void				update(const GameTimer& gt);
	void				draw();
	void				handleEvent(WPARAM btnStat);
	void				buildScene();
	void buildScene		(States::ID ID);
	// add it

	void				pushState(States::ID stateID);
	void				popState();
	void				clearStates();
	void				RemoveState(States::ID stateID);
	//void				something(States::ID stateID);

	void				changeStateCondition(States::ID stateID, bool OnlyScene);
	////// test for states

	bool				isEmpty() const;

	CommandQueue& getCommandQueue(); /// add it for input


private:
	State::Ptr			createState(States::ID stateID);
	void				applyPendingChanges();


private:
	struct PendingChange
	{
		explicit			PendingChange(Action action, States::ID stateID = States::None);

		Action				action;
		States::ID			stateID;
	};


private:
	std::vector<State::Ptr>								mStack;
	std::vector<PendingChange>							mPendingList;

	State::Context										mContext;
	std::map<States::ID, std::function<State::Ptr()>>	mFactories;

	CommandQueue										mCommandQueue;// add it for input

};

template <typename T>
void StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this]()
		{
			return State::Ptr(new T(*this, mContext));
		};
}