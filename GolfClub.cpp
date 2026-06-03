#include "GolfClub.h"
#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Global.h"
#include <string>

GolfClub::GolfClub(GameObject* parent)
	:GameObject(parent, "GolfClub"), club_(IRONCLUB), isAnimStart_(false), isAnimEnd_(false), deleteTimer_(0.0f)
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
	Model::SetAnimFrame(hModels_[IRONCLUB], 0, 0, 0);
	Model::SetAnimFrame(hModels_[WOODENCLUB], 0, 0, 0);
	Model::SetAnimFrame(hModels_[SMALLCLUB], 0, 0, 0);
}

void GolfClub::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
	float dt = deltaTime();
	int startFrame = 0;
	int endFrame = 300;
	int animSpeed = 2;
	transform_.rotate_ = pPlayer->GetRotate();
	if (!(pPlayer->IsShoot()))
	{
		transform_.position_ = pPlayer->GetPosition();
		transform_.position_.z += -0.4f;
		XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
		//XMVECTOR tmpVec = XMVectorSet(transform_.position_.x, transform_.position_.y, transform_.position_.z, 0);
		XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
		//vPos = XMVector3TransformCoord(vPos, mRotate);
		//tmpVec = XMVector3TransformCoord(tmpVec, mRotate);
		//vPos += tmpVec;
		XMStoreFloat3(&transform_.position_, vPos);

		deleteTimer_ = 0.0f;
	}

	if (isAnimStart_)
	{
		if (Model::GetAnimFrame(hModels_[club_]) <= startFrame)
		{
			Model::SetAnimFrame(hModels_[IRONCLUB], startFrame, endFrame, animSpeed);
			Model::SetAnimFrame(hModels_[WOODENCLUB], startFrame, endFrame, animSpeed);
			Model::SetAnimFrame(hModels_[SMALLCLUB], startFrame, endFrame, animSpeed + 2);
		}
	}

	if (Model::GetAnimFrame(hModels_[club_]) >= endFrame)
	{
		isAnimEnd_ = true;
		isAnimStart_ = false;
	}

	if (isAnimEnd_)
	{
		Model::SetAnimFrame(hModels_[IRONCLUB], 0, 0, 0);
		Model::SetAnimFrame(hModels_[WOODENCLUB], 0, 0, 0);
		Model::SetAnimFrame(hModels_[SMALLCLUB], 0, 0, 0);
	}


	if (deleteTimer_ >= 0.1f)
	{
		isAnimEnd_ = false;
	}
	deleteTimer_ += dt;
}

void GolfClub::Draw()
{
	Model::SetTransform(hModels_[club_], transform_);
	if (deleteTimer_ <= 1.0f)
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