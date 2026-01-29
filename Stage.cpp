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
	//std::vector<std::string> fileName =
	//{
	//	"ground.fbx",
	//	"outGround.fbx"
	//};
	//for (int i = 0; i < fileName.size(); i++)
	//{
	//	hModels_.push_back(Model::Load(fileName[i]));
	//	assert(hModels_[i] > 0);
	//}
	//transform_.position_.y = -2.0f;
	hModel_ = Model::Load("ground.fbx");
	assert(hModel_ > 0);
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
				Tree* tree = Instantiate<Tree>(this);
				int tposX = (10.0f * x + tree->GetScale().x);
				int tposZ = -(10.0f * y + tree->GetScale().z);
				tree->SetPosition(tposX, 0.0f, tposZ);
			}
		}
	}

	Instantiate<Area>(this);
	Instantiate<Goal>(this);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	//for(int i = 0; i < hModels_.size();i++)
	//{
	//	Model::SetTransform(hModels_[i], transform_);
	//	Model::Draw(hModels_[i]);
	//}
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Stage::Release()
{
	//for (int i = 0; i < hModels_.size();i++)
	//{
	//	Model::Release(hModels_[i]);
	//}
	Model::Release(hModel_);
}
