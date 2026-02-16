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
	};
	for (int i = 0; i < fileName_.size();i++)
	{
		hPicts_.push_back(Image::Load(fileName_[i]));
		assert(hPicts_[i] >= 0);
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

	for (int i = 0; i < hPicts_.size(); i++)
	{
		if (!(player->IsShoot()))
		{
			Image::SetTransform(hPicts_[i], tHitMeta);
			Image::Draw(hPicts_[i]);
		}
	}
}

void UI::Release()
{
}
