#include "LakeArea.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

LakeArea::LakeArea(GameObject* parent)
	:GameObject(parent,"LakeArea")
{
}

LakeArea::~LakeArea()
{
}

void LakeArea::Initialize()
{
	transform_.scale_.x = 1.0f;
	transform_.scale_.y = 1.0f;
	transform_.scale_.z = 1.0f;
	hModel_ = Model::Load("lakeArea.fbx");
	assert(hModel_ > 0);
	BoxCollider* collicion = new BoxCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(9.0f, 0.1f, 9.0f));
	BoxCollider* collicionX = new BoxCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(11.0f, 0.1f, 4.0f));
	BoxCollider* collicionZ = new BoxCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(4.0f, 0.1f, 11.0f));
	AddCollider(collicion);
	AddCollider(collicionX);
	AddCollider(collicionZ);
}

void LakeArea::Update()
{
}

void LakeArea::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	CollisionDraw();
}

void LakeArea::Release()
{
}
