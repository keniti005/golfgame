#pragma once
#include "Engine/GameObject.h"
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
	std::vector<int> hPicts_;
	std::vector<std::string> fileName_;
};

