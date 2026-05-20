#include "GolfClub.h"
#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Global.h"
#include <string>

GolfClub::GolfClub(GameObject* parent)
	:GameObject(parent, "GolfClub"), club_(IRONCLUB), isAnimStart_(false), isAnimEnd_(false)
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
}

void GolfClub::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
	int startFrame = 0;
	int endFrame = 300;
	int animSpeed = 2;
	if (!(pPlayer->IsShoot()))
	{
		deleteTimer_ = 0.0f;
		isAnimStart_ = false;
		isAnimEnd_ = false;

		transform_.position_ = pPlayer->GetPosition();
		transform_.position_.z -= 0.4f;
		XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(pPlayer->GetRotate().y));
		XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
		XMVECTOR Move = { 0.0f,0.0f,0.0f,0.0f };
		//vPos = XMVector3TransformCoord(vPos, mRotate);
		Move = XMVector3TransformCoord(Move, mRotate);
		vPos += Move;
		XMStoreFloat3(&transform_.position_, vPos);
	}
	if (isAnimStart_)
	{
		Model::SetAnimFrame(hModels_[IRONCLUB], startFrame, endFrame, animSpeed);
		Model::SetAnimFrame(hModels_[WOODENCLUB], startFrame, endFrame, animSpeed);
		Model::SetAnimFrame(hModels_[SMALLCLUB], startFrame, endFrame, animSpeed + 2);
		if (Model::GetAnimFrame(hModels_[club_]) >= endFrame)
		{
			isAnimEnd_ = true;
			deleteTimer_ += deltaTime();
		}
	}
}

void GolfClub::Draw()
{
	Model::SetTransform(hModels_[club_], transform_);
	if (deleteTimer_ > 2.0f)
	{
		Model::Draw(hModels_[club_]);
	}
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