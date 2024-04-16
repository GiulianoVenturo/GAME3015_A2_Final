#pragma once
#include"World.hpp"
#include "Player.h"
#include "../../Common/GameTimer.h"
#include "UIHandler.h"
#include "State.h"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void   draw();
	virtual bool   update(const GameTimer& gt);
	virtual bool   handleEvent(WPARAM btnStat);
	virtual void   buildScene();
	virtual void   SetScene();
	virtual void   HideScene();

	virtual States::ID  getStateID() { return States::Game; }

private: 
	World               mWorld;
	Player*             mPlayer;
	bool                m_InitializeCamera;
	bool                m_GamePaused;
	Game*               mGame;

};

