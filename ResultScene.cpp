#include "ResultScene.h"
#include "Player.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include <string>

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene"), pText_(nullptr)
{
}

//初期化
void ResultScene::Initialize()
{
	pText_ = new Text();
	pText_->Initialize();
}

//更新
void ResultScene::Update()
{
	if (Input::IsKey(DIK_SPACE))
	{
		SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
		sceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

//描画
void ResultScene::Draw()
{
	Player* pPlayer = (Player*)FindObject("Player");
	std::string resultString = ("Push SPACE Title");
	std::string turnsStirng = ("turnsNum:");
	//std::string turnsStirng = ("turnsNum:" + std::to_string(pPlayer->Getturns()));
	pText_->Draw(64, 64, "ResultScene");
	pText_->Draw((1280 / 2.0f) - resultString.size() * 16 / 2.0f, (720 / 2.0f), resultString.c_str());
	pText_->Draw((1280 / 2.0f) - turnsStirng.size() * 16 / 2.0f, (720 / 2.0f)- 16 * 2, turnsStirng.c_str());
}

//開放
void ResultScene::Release()
{
}
