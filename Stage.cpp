#include "Stage.h"
#include "Engine/Model.h"
#include "Tree.h"
#include "Area.h"
#include "Goal.h"
#include "Engine/CsvReader.h"
#include <string>

Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage")
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	transform_.scale_.x = 1.0f;
	transform_.scale_.y = 1.0f;
	transform_.scale_.z = 1.0f;
	std::vector<std::string> fileName =
	{
		"ground.fbx",
		"outGround.fbx"
	};
	for (int i = 0; i < fileName.size(); i++)
	{
		hModels_.push_back(Model::Load(fileName[i]));
		assert(hModels_[i] > 0);
	}
	transform_.position_.y = -2.0f;
	Instantiate<Tree>(this);
	Instantiate<Area>(this);
	Instantiate<Goal>(this);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	for(int i = 0; i < hModels_.size();i++)
	{
		Model::SetTransform(hModels_[i], transform_);
		Model::Draw(hModels_[i]);
	}
}

void Stage::Release()
{
	Model::Release(hModels_.size());
}
