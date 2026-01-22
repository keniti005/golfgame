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
	std::vector<int> GetModelHandles() { return hModels_; }
private:
	std::vector<int> hModels_;
};