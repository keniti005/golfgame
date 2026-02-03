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
    int GetModelHandle();
private:
    std::vector<int> hModels_;
    std::vector<std::string> fileName_;
};

