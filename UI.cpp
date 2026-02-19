#include "UI.h"
#include "Player.h"
#include "Goal.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

UI::UI(GameObject* parent)
	:GameObject(parent, "UI"),clearText_("GameClear"),pText_(nullptr),hArowPict_(-1),powerTimer_(0.0f)
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
	hArowPict_ = (Image::Load("Arow.png"));
	assert(hArowPict_ >= 0);

	hClubPict_.push_back(Image::Load("ironClubUI.png"));
	hClubPict_.push_back(Image::Load("woodenClubUI.png"));
	hClubPict_.push_back(Image::Load("smallClubUI.png"));
	for (int i = 0; i < hMetaPict_.size();i++)
	{
		assert(hClubPict_[i] >= 0);
	}
	//メータの位置
	tHitMeta.position_.x = 0.2f;
	tHitMeta.position_.y = 0.2f;
	tHitMeta.position_.z = 0.0f;
	//メータの矢印の位置
	tArow.position_.x = tHitMeta.position_.x + 0.11f;
	tArow.position_.y = tHitMeta.position_.y - 0.3f;
	tArow.position_.z = 0.0f;
	//クラブUIの位置
	tClub.position_.x = 0.85f;
	tClub.position_.y = 0.9f;
	tClub.position_.z = 0.0f;
}

void UI::Update()
{
	//移動範囲-0.1～0.5(0.6の差)
	static float pt = timeGetTime();
	float ct = timeGetTime();
	float dt = (ct - pt) / 1000.0f;
	if (powerTimer_ >= 2.0f)
	{
		powerTimer_ = 0.0f;
		tArow.position_.y = tHitMeta.position_.y - 0.3f;
	}
	else
	{
		powerTimer_ += dt;
		tArow.position_.y += powerTimer_ / 200.0f;
	}
	//OutputDebugStringA(("Timer:" + std::to_string(powerTimer_) + "\n").c_str());
	//OutputDebugStringA(("position:" + std::to_string(tArow.position_.y) + "\n").c_str());
	pt = ct;
}

void UI::Draw()
{
	Player* pPlayer = (Player*)FindObject("Player");
	Goal* pGoal = (Goal*)FindObject("Goal");
	int currentClub = pPlayer->GetClub();

	for (int i = 0; i < hMetaPict_.size(); i++)
	{
		if (!(pPlayer->IsShoot()))
		{
			Image::SetTransform(hMetaPict_[i], tHitMeta);
			Image::Draw(hMetaPict_[i]);
			Image::SetTransform(hArowPict_, tArow);
			Image::Draw(hArowPict_);
		}
	}
	
	Image::SetTransform(hClubPict_[currentClub], tClub);
	Image::Draw(hClubPict_[currentClub]);

	if (pPlayer->IsShoot())
	{
		tArow.position_.y = tArow.position_.y = tHitMeta.position_.y - 0.3f;
	}
	if (pGoal->IsGoal())
	{
		pText_->Draw(600, 50, "GameClear");
	}
}

void UI::Release()
{
}
