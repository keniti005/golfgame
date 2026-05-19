#include "GolfClub.h"
#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Global.h"
#include <string>

GolfClub::GolfClub(GameObject* parent)
	:GameObject(parent, "GolfClub"), club_(IRONCLUB)
{
}

GolfClub::~GolfClub()
{
}

void GolfClub::Initialize()
{
	transform_.scale_.x = 1.0f;
	transform_.scale_.y = 1.0f;
	transform_.scale_.z = 1.0f;
	Player* pPlayer = (Player*)FindObject("Player");
	transform_.position_ = pPlayer->GetPosition();
	std::vector<std::string> fileName =
	{
		"ironClub.fbx",
		"woodenClub.fbx",
		"smallClub.fbx"
	};
	for (int i = 0; i < fileName.size(); i++)
	{
		hModels_.push_back(Model::Load(fileName[i]));
		assert(hModels_[i] >= 0);
	}
	int startFrame = 0;
	int endFrame = 300;
	//Model::SetAnimFrame(hModels_[IRONCLUB], startFrame, endFrame, 2);
	//Model::SetAnimFrame(hModels_[WOODENCLUB], startFrame, endFrame, 2);
	//Model::SetAnimFrame(hModels_[SMALLCLUB], startFrame, endFrame, 4);
}

void GolfClub::Update()
{
}

void GolfClub::Draw()
{
	Model::SetTransform(hModels_[club_], transform_);
	Model::Draw(hModels_[club_]);
}

void GolfClub::Release()
{
}

int GolfClub::ChangeClub()
{
	if (Input::IsKeyDown(DIK_UP))
	{
		switch (club_)
		{
		case IRONCLUB:
			club_ = WOODENCLUB;
			break;
		case WOODENCLUB:
			club_ = SMALLCLUB;
			break;
		case SMALLCLUB:
			club_ = IRONCLUB;
			break;
		default:
			club_ = IRONCLUB;
			break;
		}
	}
	if (Input::IsKeyDown(DIK_DOWN))
	{
		switch (club_)
		{
		case IRONCLUB:
			club_ = SMALLCLUB;
			break;
		case WOODENCLUB:
			club_ = IRONCLUB;
			break;
		case SMALLCLUB:
			club_ = WOODENCLUB;
			break;
		default:
			club_ = IRONCLUB;
			break;
		}
	}
	return club_;
}