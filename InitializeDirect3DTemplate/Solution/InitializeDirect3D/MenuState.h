#pragma once
#include "State.h"
#include "Skybox.h"
#include "UIHandler.h"
class MenuState :
    public State
{
public:
    MenuState(StateStack& stack, Context context);

	virtual void   draw();
	virtual bool   update(const GameTimer& gt);
	virtual bool   handleEvent(WPARAM btnStat);
	virtual void   buildScene();
	virtual void   SetScene();
	virtual void   HideScene();
	virtual States::ID  getStateID() { return States::Menu; }

private:
	BackGround* mBackground;
	UIHandler* mUIHandler;
	SceneNode* mSceneGraph;
	Game* mGame;
};

