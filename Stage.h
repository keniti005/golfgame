#pragma once
#include "Engine/GameObject.h"
#include <vector>

class Stage :
    public GameObject
{
public:
    Stage(GameObject* parent);
    ~Stage();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    int GetModelHandle() const { return hModel_; }
private:
    std::vector<int> hModels_;
    int hModel_;
};

