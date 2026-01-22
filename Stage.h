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
    int GetModelHandle() { return hModel_; }
    int GetCsvValue(int x, int y) { return x, y; }
private:
    //std::vector<int> hModels_;
    int hModel_;
};

