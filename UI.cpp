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
	Player* pPlayer = (Player*)FindObject("Player");
	float speed = 50.0f;
	/*パワー範囲
	赤	    0.44～0.5 4段階
	黄色    0.28～0.44 3段階
	緑	    0.1～0.28 2段階
	青	   -0.1～0.1 1段階
	*/
	//移動範囲-0.1～0.5(0.6の差)
	if (!(pPlayer->IsShoot()))
	{
		if (tArow.position_.y < 0.5f)
		{
			tArow.position_.y += 0.6f / speed;
		}
		else
		{
			tArow.position_.y = tHitMeta.position_.y - 0.3f;
		}
		float powerRange = tArow.position_.y;
		if (powerRange >= 0.44f)
		{
			pPlayer->SetRange(4);
		}
		else if (powerRange >= 0.28f && powerRange < 0.44f)
		{
			pPlayer->SetRange(3);
		}
		else if (powerRange >= 0.1f && powerRange < 0.28f)
		{
			pPlayer->SetRange(2);
		}
		else if (powerRange < 0.1f)
		{
			pPlayer->SetRange(1);
		}
	}
	//OutputDebugStringA(("position:" + std::to_string(powerRange) + "\n").c_str());
}

void UI::Draw()
{
	Player* pPlayer = (Player*)FindObject("Player");
	Goal* pGoal = (Goal*)FindObject("Goal");
	int currentClub = pPlayer->GetClub();

	if (pGoal->IsGoal())
	{
		pText_->Draw(600, 50, clearText_.c_str());
	}
	else if(!(pGoal->IsGoal()) && pPlayer->CameraMode() == PLAYER)
	{
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
	}
	if (pPlayer->IsShoot())//矢印の位置を初期化
	{
		tArow.position_.y = tHitMeta.position_.y - 0.3f;
	}
}

void UI::Release()
{
}
