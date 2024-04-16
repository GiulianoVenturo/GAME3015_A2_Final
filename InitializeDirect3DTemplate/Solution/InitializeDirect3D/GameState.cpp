#include "GameState.h"
GameState::GameState(StateStack& stack, Context context)
	:State(stack, context)
	, mWorld(context.mGame)
	, mPlayer(context.mPlayer), mGame(context.mGame) 
{
	m_InitializeCamera = false;
	m_GamePaused = false;
	SetIsActive(false);
}

void GameState::draw()
{
	if (GetIsActive() == true)
		mWorld.draw();
}

bool GameState::update(const GameTimer& gt)
{
	if (GetIsActive()&&!mWorld.isPaused)
		mWorld.update(gt);

	mWorld.updateSceneGraph(gt);
	return true;
}

void GameState::buildScene()
{
	mWorld.buildScene();
}

bool GameState::handleEvent(WPARAM btnStat)
{
	if (GetIsActive())
	{
		if (btnStat == Input::P && !mWorld.isPaused)
		{
			requestChangeState(States::Pause);
			mWorld.isPaused = true;
		}
	}
	if (GetIsActive() && !mWorld.isPaused)
	{
		CommandQueue& commands = mWorld.getCommandQueue();
		mPlayer->handleRealtimeInput(commands);
		mPlayer->handleEvent(commands, btnStat);
	}
	return true;
}

void GameState::SetScene()
{
	if (GetIsActive())
		mWorld.isPaused = false;

}
void GameState::HideScene()
{
}
