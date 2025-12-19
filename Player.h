#pragma once
#include "Engine/GameObject.h"

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
    int hModel_;
    float mass_;
    float force_;
    float friction_;
};

