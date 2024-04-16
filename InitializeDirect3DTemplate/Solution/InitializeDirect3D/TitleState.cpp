#pragma region step 11
#include "TitleState.h"
#include "Game.h"
#include "SpriteNode.h"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	, mSceneGraph(new SceneNode(context.mGame))
	, mGame(context.mGame)
{
	SetIsActive(true);
}

void TitleState::draw()
{
	if (GetIsActive() == true)
		mSceneGraph->draw();
}

bool TitleState::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);
	return true;
}

bool TitleState::handleEvent(WPARAM btnStat)
{
	if (btnStat != 0 && GetIsActive() == true)
	{
		requestChangeState(States::Menu);
		SetIsActive(false);
		original = mBackground->getWorldScale();
		mBackground->setScale(0, 0, 0);
	}
	return true;
}

void TitleState::buildScene()
{
	std::unique_ptr<BackGround> backgroundSprite(new BackGround(BackGround::TitleScreen, mGame));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(0.0, 5.0, -6.1);
	mBackground->setWorldRotation(3.14/10, 0, 0);
	mBackground->setScale(15.f, 8.f, 5.f);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	mSceneGraph->build();
}
void TitleState::SetScene()
{
}
void TitleState::HideScene()
{
}
#pragma endregion
