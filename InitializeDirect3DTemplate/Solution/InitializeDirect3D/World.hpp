#pragma once
#include "SceneNode.hpp"
#include <fstream>
#include "Aircraft.hpp"
#include "SpriteNode.h"
#include "CommandQueue.h"
#include "Command.h"
#include "DebugShadowMap.h"
#include "Skybox.h"

class World 
{
public:
	explicit							World(Game* window);
	void								update(const GameTimer& gt);
	void								updateSceneGraph(const GameTimer& gt);
	void                                PlayerBorderDistance(const GameTimer& gt);
	void								draw();
	void								SetScene();
	void								HideScene();
	bool								handleEvent(WPARAM btnStat, bool isActive);
	bool								isPaused;

	void								buildScene();
	CommandQueue&                       getCommandQueue(); 

private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};
private:
	Game*								mGame;

	SceneNode*							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;

	XMFLOAT4							mWorldBounds;
	XMFLOAT2		    				mSpawnPosition;
	float								mScrollSpeed;
	Skybox*                             mSkybox;
	DebugShadowMap*                     mDebugMap;

	Aircraft*							mPlayerAircraft;
	SpriteNode*							mBackground;
	SpriteNode*							mBackground2;
	SpriteNode*                         mBackground3;
	int                                 mBackgroundIndex;
	int                                 Floorloopcounter; 
	CommandQueue						mCommandQueue;

};
