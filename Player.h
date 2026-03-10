#pragma once
#include "Engine/GameObject.h"
#include <vector>

struct MyStruct
{
    float x;
    float y;
    float z;
};

enum CLUB
{
    IRONCLUB = 0,
    WOODENCLUB,
    SMALLCLUB,
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
    bool IsShoot() { return isShoot_; }
    int GetClub() { return club_; }
    void SetRange(int range);
    
private:
    void ChangeClub();

    int hModel_;
    std::vector<float> powerRate_;
    int rangeNum_;
    MyStruct velocity;
    CLUB club_;

    float mass_;//質量
    float force_;//力
    float friction_;//摩擦
    float gravity_;//重力
    float vy;//鉛直上向き

    bool isShoot_;//ボールを打ったかどうか
    bool isFly_;//ボールが上に飛んでいないか
    //bool isRool_;//ボールが転がっているかいないか
    bool isTreeHit_;
};

