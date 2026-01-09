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
private:
    int hModel_;
    MyStruct velocity;
    float mass_;//¿—Ê
    float force_;//—Í
    float friction_;//–€C
    float gravity_;//d—Í
    float vy;
    bool isRool_;//ƒ{[ƒ‹‚ª“]‚ª‚Á‚Ä‚¢‚é‚©‚¢‚È‚¢‚©
};

