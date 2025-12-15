#pragma once
#include "Engine/GameObject.h"

class Fbx;
class ChildOden;

class Player :
    public GameObject
{
public:
    Player(GameObject* parent);
    ~Player();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
private:
    Fbx* pFbx_;
    ChildOden* pRChildOden_;
    ChildOden* pLChildOden_;
    int hModel_;
};

