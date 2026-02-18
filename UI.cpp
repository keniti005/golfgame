#include "UI.h"
#include "Player.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

UI::UI(GameObject* parent)
	:GameObject(parent, "UI")
{
}

UI::~UI()
{
}

void UI::Initialize()
{
	hMetaPict_.push_back(Image::Load("hitMeta.png"));
	hMetaPict_.push_back(Image::Load("hitMetaFrame.png"));
	for (int i = 0; i < hMetaPict_.size(); i++)
	{
		assert(hMetaPict_[i] >= 0);
	}
	hClubPict_.push_back(Image::Load("ironClubUI.png"));
	hClubPict_.push_back(Image::Load("smallClubUI.png"));
	hClubPict_.push_back(Image::Load("woodenClubUI.png"));
	for (int i = 0; i < hMetaPict_.size();i++)
	{
		assert(hClubPict_[i] >= 0);
	}
}

void UI::Update()
{
}

void UI::Draw()
{
	Player* player = (Player*)FindObject("Player");
	Transform tHitMeta;
	tHitMeta.position_.x = 0.2f;
	tHitMeta.position_.y = 0.2f;
	tHitMeta.position_.z = 0.0f;

	Transform tClub;
	tClub.position_.x = 0.7f;
	tClub.position_.y = 0.7f;
	tClub.position_.z = 0.0f;

	for (int i = 0; i < hMetaPict_.size(); i++)
	{
		if (!(player->IsShoot()))
		{
			Image::SetTransform(hMetaPict_[i], tHitMeta);
			Image::Draw(hMetaPict_[i]);
		}
		Image::SetTransform(hClubPict_[i], tClub);
		Image::Draw(hClubPict_[i]);
	}
}

void UI::Release()
{
}
