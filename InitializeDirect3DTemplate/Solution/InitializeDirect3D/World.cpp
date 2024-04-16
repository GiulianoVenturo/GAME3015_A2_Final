#include "World.hpp"

World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mRaptor1(nullptr)
	, mRaptor2(nullptr)
	, mBackground(nullptr)
	, mBackground2(nullptr)
	, mBackground3(nullptr)
    , mBackgroundIndex(0)
	, mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f) //Left, Right, Down, Up
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(-5.0f)//(-1.0f)
	, Floorloopcounter(0)
	, IsRaptorOneLimitX(false)
	, IsRaptorTwoLimitX(true)
	, Raptor1_X(0.0)
	, Raptor2_X(0.0)
{
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::update(const GameTimer& gt)
{
	const float dt = gt.DeltaTime();
	mPlayerAircraft->setVelocity(0.0f, 0.0f, 0.0f);

	while (!mCommandQueue.isEmpty())
	{
		mSceneGraph->onCommand(mCommandQueue.pop(), dt);

	}

	PlayerBorderDistance(gt);
}

void World::updateSceneGraph(const GameTimer& gt)
{
	mSceneGraph->update(gt);

}

void World::draw()
{
	mSceneGraph->draw();
}

void World::SetScene()
{
}

void World::HideScene()
{
}

bool World::handleEvent(WPARAM btnStat, bool isActive)
{
	return true;
}

void World::buildScene()
{
	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mGame));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(0, 1.0, 0.0);
	mPlayerAircraft->setScale(3.0f, 0.0f, 3.0f);//(0.5, 0.01, 0.5);
	mSceneGraph->attachChild(std::move(player));

	std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Raptor, mGame));
	mRaptor1 = enemy1.get();
	mRaptor1->setPosition(-0.5, 1.0, 20.0);
	mRaptor1->setScale(3.0f, 0.0f, 3.0);
	mRaptor1->setWorldRotation(0, XM_PI, 0);
	//mSceneGraph->attachChild(std::move(enemy1));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	mRaptor2 = enemy2.get();
	mRaptor2->setPosition(10.0, 1.0, 20.0);
	mRaptor2->setScale(3.0f, 0.0f, 3.0);
	mRaptor2->setWorldRotation(0, XM_PI, 0);
	//mSceneGraph->attachChild(std::move(enemy2));


	std::unique_ptr<Skybox> skyboxSprite(new Skybox(mGame));
	mSkybox = skyboxSprite.get();
	mSkybox->setPosition(0, 0, 0);
	mSkybox->setScale(5000.0, 5000.0, 5000.0);
	mSceneGraph->attachChild(std::move(skyboxSprite));

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(SpriteNode::Desert,mGame));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(0.0f, -50, 50.0);
	mBackground->setScale(600.0f, 100.0f, 200.0f);
	//mBackground->setVelocity(0.f, 0.f, mScrollSpeed);
	mSceneGraph->attachChild(std::move(backgroundSprite));
	
	std::unique_ptr<SpriteNode> backgroundSprite2(new SpriteNode(SpriteNode::Desert, mGame));
	mBackground2 = backgroundSprite2.get();
	mBackground2->setPosition(0.0f, -50, 150.0);
	mBackground2->setScale(600.0f, 100.0f, 200.0f);
	mBackground->setVelocity(0.f, 0.f, mScrollSpeed);
	mSceneGraph->attachChild(std::move(backgroundSprite2));

	std::unique_ptr<SpriteNode> backgroundSprite3(new SpriteNode(SpriteNode::bricks0, mGame));
	mBackground3 = backgroundSprite3.get();
	mBackground3->setPosition(0.0f, -50, 250.0);
	mBackground3->setScale(100.0f, 100.0f, 100.0f);
	mBackground->setVelocity(0.f, 0.f, mScrollSpeed);
	mSceneGraph->attachChild(std::move(backgroundSprite3));



	std::unique_ptr<DebugShadowMap> shadowMap(new DebugShadowMap(mGame));
	mDebugMap = shadowMap.get();
	mSceneGraph->attachChild(std::move(shadowMap));



	mSceneGraph->build();
}


void World::PlayerBorderDistance(const GameTimer& gt)
{
	//Keep player's position inside the screen bounds, at least borderDistance units from the border
	XMFLOAT3 position = mPlayerAircraft->getWorldPosition();

	if (position.x > 9.6f )
	{
		position.x = 9.6f ;
	}
	else if (position.x < -10.0f)
	{
		position.x = - 10.0f;
	}
	else if (position.z < -4.0f)
	{
		position.z = -4.0f;
	}
	else if (position.z > 26.0f)
	{
		position.z = 26.0f;
	}

	mPlayerAircraft->setPosition(position.x, position.y, position.z);
}
