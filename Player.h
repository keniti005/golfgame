#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
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

enum CAMERA
{
    PLAYER,
    STAGESENTER,
    MAX_CAMERA
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

    bool IsShoot() const { return isShoot_; }
    int GetClub() const { return club_; }
    void SetRange(int range);
    CAMERA CameraMode() const { return camTargetNow_; }

    int Getturns() const { return turns_; }
    
private:
    void ChangeClub();
    void ChangeCamera();
    void HitRayCast(int hModel);

    int hModel_;
    std::vector<float> powerRate_;
    int rangeNum_;
    MyStruct csvSenterVal_;//ステージオブジェトの中央の値
    MyStruct velocity_;
	XMFLOAT3 respawnPos_;//リスポーン地点
    CLUB club_;
    int turns_;

    float mass_;//質量
    float force_;//力
    float friction_;//摩擦
    float gravity_;//重力
    float vy;//鉛直上向き

    bool isShoot_;//ボールを打ったかどうか
    bool isFly_;//ボールが上に飛んでいないか
    //bool isRool_;//ボールが転がっているかいないか
    bool isTreeHit_;
	bool isLakeAreaHit_;
    CAMERA camTargetNow_;
};

