#pragma once
#include "Engine/GameObject.h"
#include <vector>
#include <string>
#include <algorithm>

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
};

