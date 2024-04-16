#pragma once
#include "State.h"
#include "UIHandler.h"

class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);
	virtual States::ID   getStateID() { return States::Title; }

	virtual void		draw();
	virtual bool		update(const GameTimer& gt);
	virtual bool		handleEvent(WPARAM btnStat);
	virtual void		buildScene();
	virtual void		SetScene();
	virtual void		HideScene();

private:
	BackGround* mBackground;
	UIHandler* mUIHandler;
	SceneNode* mSceneGraph;
	Game* mGame;
};
