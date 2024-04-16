#pragma once
#include "StateIdentifiers.h"
#include "../../Common/GameTimer.h"
#include "BackGround.h"

#include <memory>

class StateStack;
class Player;
class Game;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;
	struct Context
	{
		Context(Game* game, Player& player);
		Game* mGame;
		Player* mPlayer;
	};

	 

public:
	State(StateStack& stack, Context context);
	
	virtual				~State();

	virtual void		draw() = 0;
	virtual bool		update(const GameTimer& gt) = 0;
	virtual bool		handleEvent(WPARAM btnStat) = 0;
	virtual void		buildScene() = 0; // add it
	virtual States::ID  getStateID() = 0;
	bool				GetIsActive();/// test for states
	void				SetIsActive(bool isActive);//!!!!

	virtual void		SetScene() = 0;
	virtual void		HideScene() = 0;
	/// test for states
	void				requestChangeState(States::ID stateID, bool isOnlyScene =false);///!!! test for states

protected:
	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStateClear();
	void				requestStateRemoval(States::ID stateID);
	void				ChangeScene(States::ID stateID);

	Context            getContext() const;
	XMFLOAT3			original;


private:
	StateStack*         mStack;
	Context				mContext;
	bool				mIsActive = false;/// test for states
};

