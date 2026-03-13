#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include <string>

//コンストラクタ
TitleScene::TitleScene(GameObject * parent)
	: GameObject(parent, "TitleScene"),pText_(nullptr)
{
}

//初期化
void TitleScene::Initialize()
{
	pText_ = new Text();
	pText_->Initialize();
}

//更新
void TitleScene::Update()
{
	if (Input::IsKey(DIK_SPACE))
	{
		SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
		sceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//描画
void TitleScene::Draw()
{
	std::string startString = ("Push SPACE Start");
	pText_->Draw(64, 64, "TitleScene");
	pText_->Draw((1280 / 2.0f) - startString.size() * 16 / 2.0f, (720 / 2.0f), startString.c_str());
}

//開放
void TitleScene::Release()
{
}
