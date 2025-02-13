#pragma once
#include "State.h"
#include "UIHandler.h"

class PauseState :
    public State
{
public: 
    PauseState(StateStack& stack, Context context);
	virtual void   draw();
	virtual bool   update(const GameTimer& gt);
	virtual bool   handleEvent(WPARAM btnStat);
	virtual void   buildScene();
	virtual void   SetScene();
	virtual void   HideScene();
	virtual States::ID  getStateID() { return States::Pause; }

private:
	BackGround* mBackground;
	UIHandler* mUIHandler;
	SceneNode* mSceneGraph;
	Game* mGame;

};

