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
	fileName_ =
	{
		"hitMeta.png",
		"hitMetaFrame.png"
		//"ironClubUI.png",
		//"smallClubUI.png",
		//"woodenClubUI.png"
	};
	for (int i = 0; i < fileName_.size();i++)
	{
		hMetaPict_.push_back(Image::Load(fileName_[i]));
		assert(hMetaPict_[i] >= 0);
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

	}
}

void UI::Release()
{
}
