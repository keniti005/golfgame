#pragma once
#include "Engine/GameObject.h"
#include <vector>

class Goal :
    public GameObject
{
public:
    Goal(GameObject* parent);
    ~Goal();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;
    int GetModelHandle();
    bool IsGoal() { return isGoal_; }
private:
    std::vector<int> hModels_;
    std::vector<std::string> fileName_;
    bool isGoal_;//ÉSÅ[ÉãÇµÇΩÇ©
};

