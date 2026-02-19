#include "UI.h"
#include "Player.h"
#include "Goal.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

UI::UI(GameObject* parent)
	:GameObject(parent, "UI"),clearText_("GameClear"),pText_(nullptr)
{
}

UI::~UI()
{
}

void UI::Initialize()
{
	pText_ = new Text();
	pText_->Initialize();
	hMetaPict_.push_back(Image::Load("hitMeta.png"));
	hMetaPict_.push_back(Image::Load("hitMetaFrame.png"));
	for (int i = 0; i < hMetaPict_.size(); i++)
	{
		assert(hMetaPict_[i] >= 0);
	}
	hClubPict_.push_back(Image::Load("ironClubUI.png"));
	hClubPict_.push_back(Image::Load("woodenClubUI.png"));
	hClubPict_.push_back(Image::Load("smallClubUI.png"));
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
	Player* pPlayer = (Player*)FindObject("Player");
	Goal* pGoal = (Goal*)FindObject("Goal");
	int currentClub = pPlayer->GetClub();
	Transform tHitMeta;
	tHitMeta.position_.x = 0.2f;
	tHitMeta.position_.y = 0.2f;
	tHitMeta.position_.z = 0.0f;
	
	Transform tClub;
	tClub.position_.x = 0.85f;
	tClub.position_.y = 0.9f;
	tClub.position_.z = 0.0f;
	
	for (int i = 0; i < hMetaPict_.size(); i++)
	{
		if (!(pPlayer->IsShoot()))
		{
			Image::SetTransform(hMetaPict_[i], tHitMeta);
			Image::Draw(hMetaPict_[i]);
		}
	}
	
	Image::SetTransform(hClubPict_[currentClub], tClub);
	Image::Draw(hClubPict_[currentClub]);

	if (pGoal->IsGoal())
	{
		pText_->Draw(600, 50, "GameClear");
	}
}

void UI::Release()
{
}
