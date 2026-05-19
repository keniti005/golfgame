#include "PlayScene.h"
#include "Player.h"
#include "Stage.h"
#include "Goal.h"
#include "UI.h"
#include "GolfClub.h"
#include "Engine/SceneManager.h"
#include "Engine/Global.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	Instantiate<Player>(this);
	Instantiate<Stage>(this);
	Instantiate<UI>(this);
	Instantiate<GolfClub>(this);
}

void PlayScene::Update()
{
	static float goalTimer = 0.0f;
	float dt = deltaTime();

	Goal* pGoal = (Goal*)FindObject("Goal");
	if (pGoal->IsGoal())
	{
		//タイマーが5秒経過したらシーン遷移
		goalTimer += dt;
		if (goalTimer >= 5.0f)
		{
			goalTimer = 0.0f;
			SceneManager* scene = (SceneManager*)FindObject("SceneManager");
			scene->ChangeScene(SCENE_ID_RESULT);
		}
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
