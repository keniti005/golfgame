#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"),pText_(nullptr)
{
}

//初期化
void TestScene::Initialize()
{
	pText_ = new Text();
	pText_->Initialize();
}

//更新
void TestScene::Update()
{
	if (Input::IsKey(DIK_SPACE))
	{
		SceneManager* sceneManager = (SceneManager*)FindObject("SceneManager");
		sceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//描画
void TestScene::Draw()
{
	pText_->Draw(64, 64, "TitleScene");
}

//開放
void TestScene::Release()
{
}
