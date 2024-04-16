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
	void								MoveRaptorSideToSide(const GameTimer& gt);
	void								LoopBackGround(const GameTimer& gt);
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

	Skybox*                                  mSkybox;// add
	DebugShadowMap*                          mDebugMap;// add


	Aircraft*							mPlayerAircraft;
	SpriteNode*							mBackground;
	SpriteNode*							mBackground2;
	SpriteNode*                         mBackground3;
	SpriteNode*                         mBackgroundArray[3];
	int                                 mBackgroundIndex;
	Aircraft*							mRaptor1;
	Aircraft*							mRaptor2;
	int                              Floorloopcounter; // add  to know how many times it's been loop
	bool                             IsRaptorOneLimitX, IsRaptorTwoLimitX; // use control the enemie planes
	float                            Raptor1_X , Raptor2_X;// used store the x value ememy air planes
	std::ofstream                         myfile; // used as text console / debug
	CommandQueue						    mCommandQueue;// add it for input

};
