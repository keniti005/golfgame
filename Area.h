#pragma once
#include "Engine/GameObject.h"
#include <vector>

class Area :
	public GameObject
{
public:
	Area(GameObject* parent);
	~Area();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	std::vector<int> hModels_;
};