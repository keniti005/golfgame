#pragma once
#include "Engine/GameObject.h"

//struct obj
//{
//	std::vector<std::vector<int>> pos;
//
//};

class Tree :
	public GameObject
{
public:
	Tree(GameObject* parent);
	~Tree();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void OnCollision(GameObject* pTarget) override;
	int GetModelHandle() { return hModel_; }
private:
	int hModel_;
	int csvValue_[256][256];
};