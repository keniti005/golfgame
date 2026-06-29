#include "OutArea.h"
#include "Engine/Model.h"

OutArea::OutArea(GameObject* parent)
	:GameObject(parent, "OutArea"), hModel_(-1)
{
}

OutArea::~OutArea()
{
}

void OutArea::Initialize()
{
	transform_.scale_.x = 1.0f;
	transform_.scale_.y = 1.0f;
	transform_.scale_.z = 1.0f;

	//hModel_ = Model::Load("outGround.fbx");
	hModel_ = Model::Load("tyutrialOutGround.fbx");
	assert(hModel_ >= 0);
}

void OutArea::Update()
{
}

void OutArea::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void OutArea::Release()
{
}
