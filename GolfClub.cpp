#include "GolfClub.h"
#include "Engine/Input.h"

GolfClub::GolfClub(GameObject* parent)
	:GameObject(parent, "GolfClub"), club_(IRONCLUB)
{
}

GolfClub::~GolfClub()
{
}

void GolfClub::Initialize()
{
	//hModel_ = Model::Load("ironClub.fbx");
	//hModel_ = Model::Load("woodenClub.fbx");
	//hModel_ = Model::Load("smallClub.fbx");
}

void GolfClub::Update()
{
}

void GolfClub::Draw()
{
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