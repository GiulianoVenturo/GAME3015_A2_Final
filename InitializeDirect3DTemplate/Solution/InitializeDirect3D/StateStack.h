
#pragma once
#include "StateIdentifiers.h"
#include "../../Common/GameTimer.h"
#include "State.h"
#include "CommandQueue.h"
#include "Command.h"

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
	void				pushState(States::ID stateID);
	void				popState();
	void				clearStates();
	void				RemoveState(States::ID stateID);
	void				changeStateCondition(States::ID stateID, bool OnlyScene);
	bool				isEmpty() const;
	void				applyPendingChanges();

	void buildScene		(States::ID ID);
	CommandQueue& getCommandQueue();

private:
	State::Ptr			createState(States::ID stateID);
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
	CommandQueue										mCommandQueue;
};

template <typename T>
void StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this](){
			return State::Ptr(new T(*this, mContext));
	};
}