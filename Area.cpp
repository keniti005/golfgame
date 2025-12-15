#include "Area.h"
#include <string>
#include "Engine/Model.h"

Area::Area(GameObject* parent)
	:GameObject(parent,"Area")
{
}

Area::~Area()
{
}

void Area::Initialize()
{
	transform_.scale_.x = 1.0f;
	transform_.scale_.y = 1.0f;
	transform_.scale_.z = 1.0f;
	transform_.position_.y += 0.2f;
	std::vector<std::string> fileName =
	{
		"lakeArea.fbx"
	};
	for (int i = 0; i < fileName.size(); i++)
	{
		hModels_.push_back(Model::Load(fileName[i]));
		assert(hModels_[i] > 0);
	}
}

void Area::Update()
{
}

void Area::Draw()
{
	for (int i = 0; i < hModels_.size(); i++)
	{
		Model::SetTransform(hModels_[i], transform_);
		Model::Draw(hModels_[i]);
	}
}

void Area::Release()
{
	Model::Release(hModels_.size());
}
