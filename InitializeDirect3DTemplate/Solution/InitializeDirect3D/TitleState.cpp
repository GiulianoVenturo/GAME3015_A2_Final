#pragma region step 11
#include "TitleState.h"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	, mSceneGraph(new SceneNode(context.mGame))
	, mGame(context.mGame)
{
	std::unique_ptr<BackGround> backgroundSprite(new BackGround(BackGround::TitleScreen, mGame));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(0.0, 7.0, -6.1);
	mBackground->setWorldRotation(3.14 / 10, 0, 0);
	mBackground->setScale(7.0, 5.8, 5.0);
	mSceneGraph->attachChild(std::move(backgroundSprite));

}

void TitleState::draw()
{
	mSceneGraph->draw();
}

bool TitleState::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);

	return true;
}

bool TitleState::handleEvent(WPARAM btnStat)
{
	// Press Any key
	if (btnStat != 0)
	{
		//requestStackPush(States::Menu);
		ChangeScene(States::Menu);
		//mStateStack.pushState(States::Menu);
		//requestChangeState(States::Menu);

		//requestStackPop();

		/*requestStackPop();
		//requestStackPush(States::Pause);

		
		//ChangeScene(States::Menu);
		//requestChangeState(States::Menu);
		SetIsActive(false);	
		//requestStackPop();
		//requestStateRemoval(getStateID());
		
		original = mBackground->getWorldScale();
		mBackground->setScale(0, 0, 0);
		//ChangeScene(States::Pause);
		*/
	}
	return true;
}


void TitleState::buildScene()
{
	mSceneGraph->build();
}
void TitleState::SetScene()
{
	mBackground->setScale(7.0, 5.8, 5.0);

}
void TitleState::HideScene()
{
	//mBackground->setScale(0.0, 0.0, 0.0);

}
#pragma endregion
