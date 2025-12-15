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
private:
    std::vector<int> hModels_;
};

