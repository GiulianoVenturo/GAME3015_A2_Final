#include "PauseState.h"
#include "Skybox.h"
#include "Input.h"


PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
	, mSceneGraph(new SceneNode(context.mGame))
	, mGame(context.mGame)
{
	SetIsActive(false);
}

void PauseState::draw()
{
	if (GetIsActive() == true)
		mSceneGraph->draw();
}

bool PauseState::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);

	return true;
}

bool PauseState::handleEvent(WPARAM btnStat)
{
	if (GetIsActive())
	{
		if (btnStat == Input::P)
		{
			SetIsActive(false);
			requestChangeState(States::Game, true);

			mBackground->setScale(0.0, 0, 0);
			return false;
		}
		if (btnStat == Input::Z)
		{
			SetIsActive(false);
			mBackground->setScale(0.0, 0, 0);
			requestChangeState(States::Game);
			requestChangeState(States::Menu);
		}
	}
	return true;
}


void PauseState::buildScene()
{
	std::unique_ptr<BackGround> backgroundSprite(new BackGround(BackGround::PauseScreen, mGame));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(0.0, 8.5, -12.5);
	mBackground->setScale(0.0, 0, 0);
	
	mBackground->setWorldRotation(3.14 / 10, 0, 0);
	mSceneGraph->attachChild(std::move(backgroundSprite));
	mSceneGraph->build();
}

void PauseState::SetScene()
{
	mBackground->setScale(7.0, 5.8, 5.0);
}
void PauseState::HideScene()
{
}
