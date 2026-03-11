#include "Stage.h"
#include "Engine/Model.h"
#include "Tree.h"
#include "Area.h"
#include "Goal.h"
#include "Engine/CsvReader.h"
#include <string>

Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage"),hModel_(-1)
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
		if (fileName[i] == "ground.fbx")
		{
			hModel_ = hModels_[i];
		}
	}
	//transform_.position_.y = -2.0f;
	//hModel_ = Model::Load("ground.fbx");
	//assert(hModel_ >= 0);
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
				int tposY = 0.0f;
				int tposZ = -(10.0f * y + tree->GetScale().z);
				Transform tpos;
				tpos.position_ = XMFLOAT3(tposX, tposY, tposZ);
				RayCastData data;
				float rayStart = 20.0f;
				data.start = tpos.position_;   //レイの発射位置
				data.start.y = rayStart;
				data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
				Model::RayCast(hModel_, &data); //レイを発射

				//レイが当たったら
				if (data.hit)
				{
					//その分位置を下げる
					//transform_.position_.y = -data.dist + data.start.y;
					tpos.position_.y = -data.dist + data.start.y;
				}
				//tree->SetPosition(tposX, 0.0f, tposZ);
				tree->SetPosition(tpos.position_);
			}
			else if (csv.GetValue(x, y) == 10)
			{
				Goal* goal = Instantiate<Goal>(this);
				int gposX = (10.0f * x + goal->GetScale().x);
				int gposZ = -(10.0f * y + goal->GetScale().z);
				goal->SetPosition(gposX, 0.0f, gposZ);
			}
		}
	}

	Instantiate<Area>(this);
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
	//Model::SetTransform(hModel_, transform_);
	//Model::Draw(hModel_);
}

void Stage::Release()
{
}
