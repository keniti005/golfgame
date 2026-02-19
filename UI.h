#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include <vector>
#include <string>

class UI :
    public GameObject
{
public:
    UI(GameObject* parent);
    ~UI();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	std::vector<int> hMetaPict_;
	std::vector<int> hClubPict_;
	Transform tHitMeta;
	Transform tArow;
	Transform tClub;
	int hArowPict_;
	float powerTimer_;
	std::string clearText_;
	Text* pText_;
};

