#pragma once
#include "Engine/GameObject.h"

enum CLUB
{
	IRONCLUB = 0,
	WOODENCLUB,
	SMALLCLUB,
};

class GolfClub :
	public GameObject
{
public:
	GolfClub(GameObject* parent);
	~GolfClub();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	int GetClub() const { return club_; }
	int ChangeClub();

private:

	CLUB club_;
};