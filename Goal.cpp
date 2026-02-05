#include "Goal.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "Engine/BoxCollider.h"
#include <string>

Goal::Goal(GameObject* parent)
	:GameObject(parent,"Goal")
{
}

Goal::~Goal()
{
}

void Goal::Initialize()
{
	transform_.scale_.x = 1.0f;
	transform_.scale_.y = 1.0f;
	transform_.scale_.z = 1.0f;
	fileName_ =
	{
		"goalFlag.fbx",
		"goalArea.fbx"
	};
	for (int i = 0;i < fileName_.size();i++)
	{
		hModels_.push_back(Model::Load(fileName_[i]));
		assert(hModels_[i] > 0);
		if (fileName_[i] == "goalArea.fbx")
		{
			BoxCollider* collider = new BoxCollider(transform_.position_, XMFLOAT3(2.0f,0.5f,2.0f));
			AddCollider(collider);
		}
	}
}

void Goal::Update()
{
}

void Goal::Draw()
{
	for (int i = 0;i < hModels_.size(); i++)
	{
		Model::SetTransform(hModels_[i], transform_);
		Model::Draw(hModels_[i]);
		CollisionDraw();
	}
}

void Goal::Release()
{
	for (int i = 0; i < hModels_.size(); i++)
	{
		Model::Release(hModels_[i]);
	}
}

int Goal::GetModelHandle()
{
	for (int i = 0; i < fileName_.size(); i++)
	{
		if (fileName_[i] == "goalArea.fbx")
		{
			return hModels_[i];
		}
	}
}
