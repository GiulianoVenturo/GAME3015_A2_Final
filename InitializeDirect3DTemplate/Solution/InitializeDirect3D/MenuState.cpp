#include "MenuState.h"
#include "Skybox.h"
#include "Input.h"
#include "Game.h"

MenuState::MenuState(StateStack& stack, Context context)
	:State(stack, context)
	, mSceneGraph(new SceneNode(context.mGame))
	, mGame(context.mGame)
{
	
	SetIsActive(false);
}

void MenuState::draw()
{
	mSceneGraph->draw();
}

bool MenuState::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);

	return true;
}

bool MenuState::handleEvent(WPARAM btnStat)
{
	if (btnStat == Input::R && GetIsActive() == true)
	{
		/*ChangeScene(States::Game);
		SetIsActive(false);*/
		//requestStackPop();
		requestChangeState(States::Game);
		SetIsActive(false);

		original = mBackground->getWorldScale();
		mBackground->setScale(0, 0, 0);

		//requestStateRemoval(getStateID());

			//(100.0, 100.0, 100.0);
		//mBackground->setPosition(0.0, 7.0, -1.5);
		//mSceneGraph->detachChild(std::move(*mBackground));
		//requestStackPop();

	}
	else if (btnStat == Input::T && GetIsActive() == true)
	{
		PostQuitMessage(0);
	}

	return true;
}


void MenuState::buildScene()
{
	std::unique_ptr<BackGround> backgroundSprite(new BackGround(BackGround::MainMenu, mGame));
	mBackground = backgroundSprite.get();

	mBackground->setPosition(0.0, 7.0, -6.1);
	mBackground->setWorldRotation(3.14 / 10, 0, 0);
	mBackground->setScale(7.0, 5.8, 5.0);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	mSceneGraph->build();
}

void MenuState::SetScene()
{
	//mBackground->setWorldRotation(3.14 / 10, 0, 0);
	//mBackground->setScale(7.0, 5.8, 5.0);

	//mBackground->setScale(7.0, 5.8, 5.0);

}
void MenuState::HideScene()
{
	//mBackground->setScale(0.0, 0.0, 0.0);

}