#pragma once
#include "Engine/GameObject.h"

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
private:
	int hModel_;
};