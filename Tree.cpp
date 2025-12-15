#include "Tree.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"

Tree::Tree(GameObject* parent)
	:GameObject(parent,"Tree")
{
}

Tree::~Tree()
{
}

void Tree::Initialize()
{
	transform_.scale_.x = 3.0f;
	transform_.scale_.y = 3.5f;
	transform_.scale_.z = 3.0f;
	hModel_ = Model::Load("tree.fbx");
	assert(hModel_ > 0);
}

void Tree::Update()
{
}

void Tree::Draw()
{
	CsvReader csv;
	csv.Load("Stage00.csv");
	int w = csv.GetWidth();
	int h = csv.GetHeight();
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (csv.GetValue(x, y) == 1)
			{
				transform_.position_.x =  (10.0f * x);
				transform_.position_.z = -(10.0f * y);
				Model::SetTransform(hModel_, transform_);
				Model::Draw(hModel_);
			}
		}
	}

}

void Tree::Release()
{
	Model::Release(hModel_);
}
