#pragma once
#include "Engine/GameObject.h"

class LakeArea :
	public GameObject
{
public:
	LakeArea(GameObject* parent);
	~LakeArea();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	int GetModelHandle() { return hModel_; }
private:
	int hModel_;
};