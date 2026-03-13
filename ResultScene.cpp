#include "ResultScene.h"
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
	std::string resultString = ("Push SPACE Title");
	pText_->Draw(64, 64, "ResultScene");
	pText_->Draw((1280 / 2.0f) - resultString.size() * 16 / 2.0f, (720 / 2.0f), resultString.c_str());
}

//開放
void ResultScene::Release()
{
}
