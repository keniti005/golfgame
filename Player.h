#pragma once
#include "Engine/GameObject.h"

struct MyStruct
{
    float x;
    float y;
    float z;
};

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
    void OnCollision(GameObject* pTarget) override;
private:
    int hModel_;
    MyStruct velocity;
    float mass_;//質量
    float force_;//力
    float friction_;//摩擦
    float gravity_;//重力
    float vy;//仮の変数
    bool isShoot_;//ボールを打ったかどうか
    bool isFly_;//ボールが上に飛んでいないか
    //bool isRool_;//ボールが転がっているかいないか
};

