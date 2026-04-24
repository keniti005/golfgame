#pragma once
#include "Engine/GameObject.h"

class SandArea :
	public GameObject
{
public:
	SandArea(GameObject* parent);
	~SandArea();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	int GetModelHandle() { return hModel_; }
private:
	int hModel_;
};