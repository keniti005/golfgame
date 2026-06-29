#include "Stage.h"
#include "Engine/Model.h"
#include "Tree.h"
#include "LakeArea.h"
#include "sandArea.h"
#include "OutArea.h"
#include "Goal.h"
#include "Engine/CsvReader.h"
#include <string>

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), hModel_(-1)
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
	//	"tyutrialGround.fbx",
	//	"ground.fbx"
	//};
	//for (int i = 0; i < fileName.size(); i++)
	//{
	//	hStageModels_.push_back(Model::Load(fileName[i]));
	//	assert(hStageModels_[i] >= 0);
	//}
	//hStageModels_.push_back(Model::Load(fileName[0]));
	//assert(hStageModels_[0] >= 0);
	//hModel_ = Model::Load("ground.fbx");
	hModel_ = Model::Load("tyutrialGround.fbx");
	assert(hModel_ >= 0);
	CsvReader csv;
	csv.Load("Stage00.csv");
	//csv.Load("Stage01.csv");
	int w = csv.GetWidth();
	int h = csv.GetHeight();
	for (int cy = 0; cy < h; cy++)
	{
		for (int cx = 0; cx < w; cx++)
		{
			if (csv.GetValue(cx, cy) == 1)
			{
				Tree* tree = Instantiate<Tree>(this);
				Transform tpos;
				tpos.position_.x = (10.0f * cx + tree->GetScale().x);
				tpos.position_.y = 0.0f;
				tpos.position_.z = -(10.0f * cy + tree->GetScale().z);
				RayCastData data;
				float rayStart = 20.0f;
				data.start = tpos.position_;//レイの発射位置
				data.start.y = rayStart;
				data.dir = XMFLOAT3(0, -1, 0);//レイの方向
				Model::RayCast(hModel_, &data);//レイを発射

				//レイが当たったら
				if (data.hit)
				{
					//その分位置を下げる
					tpos.position_.y = -data.dist + data.start.y;
				}
				//tree->SetPosition(tposX, 0.0f, tposZ);
				tree->SetPosition(tpos.position_);
			}
			else if (csv.GetValue(cx, cy) == 10)
			{
				Goal* goal = Instantiate<Goal>(this);
				float gposX = (10.0f * cx + goal->GetScale().x);
				float gposZ = -(10.0f * cy + goal->GetScale().z);
				goal->SetPosition(gposX, 0.0f, gposZ);
			}
			else if (csv.GetValue(cx, cy) == 21)
			{
				LakeArea* lakeArea = Instantiate<LakeArea>(this);
				float aposX = (10.0f * cx + lakeArea->GetScale().x);
				float aposY = 0.3f;
				float aposZ = -(10.0f * cy + lakeArea->GetScale().z);
				lakeArea->SetPosition(aposX, aposY, aposZ);
			}
			else if (csv.GetValue(cx, cy) == 22)
			{
				SandArea* sandArea = Instantiate<SandArea>(this);
				float sposX = (10.0f * cx + sandArea->GetScale().x);
				float sposY = 0.3f;
				float sposZ = -(10.0f * cy + sandArea->GetScale().z);
				sandArea->SetPosition(sposX, sposY, sposZ);
			}
		}
	}
	OutArea* outArea = Instantiate<OutArea>(this);
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
}
