#pragma once
#include "Engine/GameObject.h"

class OutArea :
	public GameObject
{
public:
	OutArea(GameObject* parent);
	~OutArea();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	int GetModelHandle() const { return hModel_; }
private:
	int hModel_;
};
