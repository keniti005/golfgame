#include "PlayScene.h"
#include "Player.h"
#include "Stage.h"
#include "Goal.h"
#include "UI.h"
#include "Engine/SceneManager.h"

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
}

void PlayScene::Update()
{
	static float pt = timeGetTime();
	float ct = timeGetTime();
	float dt = (ct - pt) / 1000.0f;
	static float goalTimer = 0;

	Goal* pGoal = (Goal*)FindObject("Goal");
	if (pGoal->IsGoal())
	{
		//タイマーが5秒経過したらシーン遷移
		goalTimer += dt;
		if (goalTimer >= 5.0f)
		{
			goalTimer = 0.0f;
			SceneManager* scene = (SceneManager*)FindObject("SceneManager");
			scene->ChangeScene(SCENE_ID_TEST);
		}
	}
	pt = ct;
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
