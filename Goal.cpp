#include "Goal.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
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
	transform_.scale_.x = 5.0f;
	transform_.scale_.y = 5.0f;
	transform_.scale_.z = 5.0f;
	std::vector<std::string> fileName =
	{
		"goalFlag.fbx",
		"goalArea.fbx"
	};
	for (int i = 0;i < fileName.size();i++)
	{
		hModels_.push_back(Model::Load(fileName[i]));
		assert(hModels_[i] > 0);
	}
}

void Goal::Update()
{
}

void Goal::Draw()
{
	CsvReader csv;
	csv.Load("Stage00.csv");
	int w = csv.GetWidth();
	int h = csv.GetHeight();
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (csv.GetValue(x, y) == 10)
			{
				for (int i = 0;i < hModels_.size();i++)
				{
					transform_.position_.x =  (10.0f * x);
					transform_.position_.z = -(10.0f * y);
					Model::SetTransform(hModels_[i], transform_);
					Model::Draw(hModels_[i]);
				}
			}
		}
	}
}

void Goal::Release()
{
	for (int i = 0; i < hModels_.size(); i++)
	{
		Model::Release(hModels_[i]);
	}
}
