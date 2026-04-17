#include "LakeArea.h"
#include "Engine/Model.h"

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
}

void LakeArea::Update()
{
}

void LakeArea::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void LakeArea::Release()
{
}
