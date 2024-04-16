#pragma once
#include "State.h"
#include "UIHandler.h"


class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);


	virtual void		draw();
	virtual bool		update(const GameTimer& gt);
	virtual bool		handleEvent(WPARAM btnStat);
	virtual void		buildScene();
	virtual void		SetScene();
	virtual void		HideScene();

	virtual States::ID   getStateID() { return States::Title; }


private:
	BackGround* mBackground;
	UIHandler* mUIHandler;
	SceneNode* mSceneGraph;
	Game* mGame;

	//bool mShowText;
	//float mTextEffectTime;
};
