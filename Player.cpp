#include "Player.h"
#include "Stage.h"
#include "Area.h"
#include "Goal.h"
#include "Tree.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/CsvReader.h"
#include "Engine/SphereCollider.h"


Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),hModel_(-1), mass_(0.5f), force_(0.0f), friction_(-1.1f), gravity_(-5.8f)
	, velocity{ 0.0f,0.0f,0.0f }, vy(0.0f), isShoot_(false), isFly_(false), isTreeHit_(false), club_(IRONCLUB)
	, rangeNum_(0), csvSenterVal_{ 0.0f,0.0f,0.0f }, camTargetNow_(PLAYER),turns_(0)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	transform_.scale_.x = 1.0f;
	transform_.scale_.y = 1.0f;
	transform_.scale_.z = 1.0f;
	//hModel_ = Model::Load("ironClub.fbx");
	//hModel_ = Model::Load("woodenClub.fbx");
	//hModel_ = Model::Load("smallClub.fbx");
	hModel_ = Model::Load("bollPlayer.fbx");
	assert(hModel_ >= 0);
	CsvReader csv;
	csv.Load("Stage00.csv");
	int w = csv.GetWidth();
	int h = csv.GetHeight();
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (csv.GetValue(x, y) == 11)
			{
				transform_.position_.x = (10.0f * x);
				transform_.position_.z = -(10.0f * y);
			}
		}
	}
	csvSenterVal_.x = w / 2.0f;
	csvSenterVal_.z = h / 2.0f;

	SphereCollider* collicion = new SphereCollider(XMFLOAT3(0.0f,transform_.scale_.y / 2.0f,0.0f),0.5f);
	AddCollider(collicion);

	powerRate_.push_back(0.5f);
	powerRate_.push_back(0.7f);
	powerRate_.push_back(0.95f);
	powerRate_.push_back(1.15f);
}

void Player::Update()
{
	if (Input::IsKeyDown(DIK_M))
	{
		ChangeCamera();
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 1.2f;
	}
	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 1.2f;
	}

	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
#if true
	static float pt = timeGetTime();
	float ct = timeGetTime();
	float dt = (ct - pt) / 1000.0f;
	const float MAX_SPEED = 3.0f;
	ChangeClub();

	switch (club_)
	{
	case IRONCLUB:
		velocity.y = 2.0f;
		velocity.z = 3.0f;
		break;
	case WOODENCLUB:
		velocity.y = 3.5f;
		velocity.z = 1.5f;
		break;
	case SMALLCLUB:
		velocity.y = 0.0f;
		velocity.z = 2.7f;
		break;
	default:
		break;
	}

	if (!(isShoot_))
	{
		if (Input::IsKeyDown(DIK_SPACE) && camTargetNow_ == PLAYER)
		{
			force_ = (velocity.z * powerRate_[rangeNum_]) * mass_;//運動方程式
			vy = velocity.y * sinf(45.0f) + gravity_ * dt;//斜方投射
			isFly_ = true;
			isShoot_ = true;
			turns_++;//ターン数加算
		}
	}
	else
	{
		if (!(isFly_))
		{
			if (force_ > 0)
			{
				force_ += friction_ * dt;
			}
			else
			{
				force_ = 0.0f;
				isShoot_ = false;
				isTreeHit_ = false;
			}
		}

		if (force_ > MAX_SPEED)
		{
			force_ = MAX_SPEED;
		}
	}

	pt = ct;


	XMVECTOR vMoveY = XMVectorSet(0, vy, 0, 0);
	XMVECTOR vMoveZ = XMVectorSet(0, 0, force_, 0);

	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	vMoveZ = XMVector3TransformCoord(vMoveZ, mRotate);
	//OutputDebugStringA(("force_:" + std::to_string(force_) + "\n").c_str());
	//OutputDebugStringA(("vy:" + std::to_string(vy) + "\n").c_str());
	//OutputDebugStringA(("position_.y:" + std::to_string(transform_.position_.y) + "\n").c_str());
	//OutputDebugStringA(("Timer:" + std::to_string(goalTimer) + "\n").c_str());
	//OutputDebugStringA(("range:" + std::to_string(rangeNum_) + "\n").c_str());

	vPos += vMoveY;
	if (isTreeHit_)
	{
		//反発の計算
		XMVECTOR normal = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		XMVector3Normalize(normal);
		vMoveZ = vMoveZ - 1.5f * XMVector3Dot(vMoveZ, normal) * normal;
		vPos += vMoveZ;
	}
	else
	{
		vPos += vMoveZ;
	}
	XMStoreFloat3(&transform_.position_, vPos);


	RayCastData data;
	float rayStart = 20.0f;
	data.start = transform_.position_;   //レイの発射位置
	data.start.y = rayStart;

	//ステージ上のレイキャスト
	Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
	int hStageModel = pStage->GetModelHandle();    //モデル番号を取得

	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStageModel, &data); //レイを発射

	Transform tStage;
	//レイが当たったら
	if (data.hit)
	{
		//その分位置を下げる
		//transform_.position_.y = -data.dist + data.start.y;
		tStage.position_.y = -data.dist + data.start.y;
	}
	if (transform_.position_.y <= tStage.position_.y)
	{
		vy = 0.0f;
		transform_.position_.y = tStage.position_.y;
		isFly_ = false;
	}
	else
	{
		vy += gravity_ * dt;
	}

	//ゴール地点のレイキャスト
	Goal* pGoal = (Goal*)FindObject("Goal");    //ステージオブジェクトを探す
	int hGoalModel = pGoal->GetModelHandle();    //モデル番号を取得
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hGoalModel, &data); //レイを発射

	Transform tGoal;
	//レイが当たったら
	if (data.hit)
	{
		//その分位置を下げる
		//transform_.position_.y = -data.dist + data.start.y;
		tGoal.position_.y = -data.dist + data.start.y;
		if (transform_.position_.y <= tGoal.position_.y)
		{
			vy = 0.0f;
			transform_.position_.y = tGoal.position_.y;
			isFly_ = false;
		}
	}

#else//デバッグ用
	XMVECTOR vMoveY = XMVectorSet(0, 0.4f, 0, 0);
	XMVECTOR vMoveZ = XMVectorSet(0, 0, 0.4f, 0);

	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	vMoveZ = XMVector3TransformCoord(vMoveZ, mRotate);

	XMStoreFloat3(&transform_.position_, vPos);
	if (Input::IsKey(DIK_UP))
	{
		vPos += vMoveY;
		XMStoreFloat3(&transform_.position_, vPos);
	}
	if (Input::IsKey(DIK_DOWN))
	{
		vPos -= vMoveY;
		XMStoreFloat3(&transform_.position_, vPos);
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 1.2f;
	}
	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 1.2f;
	}
	if (Input::IsKey(DIK_W))
	{
		vPos += vMoveZ;
		XMStoreFloat3(&transform_.position_, vPos);
	}
	if (Input::IsKey(DIK_S))
	{
		vPos -= vMoveZ;
		XMStoreFloat3(&transform_.position_, vPos);
	}
# endif

	XMVECTOR vCam;
	XMFLOAT3 camPos;
	XMFLOAT3 CamTarget;
	float camPosY;

	switch (camTargetNow_)
	{
	case PLAYER://プレイヤーを中心に見た視点
		vCam = { 0,2.0f,-9.0f,0 };
		vCam = XMVector3TransformCoord(vCam, mRotate);
		XMStoreFloat3(&camPos, vPos + vCam);
		Camera::SetPosition(camPos);
		CamTarget = transform_.position_;
		Camera::SetTarget(CamTarget);
		break;
	case STAGESENTER://ステージを上から見た視点
		camPosY = 300.0f;
		vCam = { 10.0f * csvSenterVal_.x,camPosY,-10.0f * csvSenterVal_.z,0.0f };
		XMStoreFloat3(&camPos, vCam);
		Camera::SetPosition(camPos);
		CamTarget = XMFLOAT3(10.0f * csvSenterVal_.x, 0.0f, (-10.0f + 1.0f) * csvSenterVal_.z);
		Camera::SetTarget(CamTarget);
		break;
	default:
		break;
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	CollisionDraw();
}

void Player::Release()
{
}

void Player::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Tree")
	{
		isTreeHit_ = true;
	}
	if (pTarget->GetObjectName() == "Goal")
	{
		force_ = 0.0f;
	}
}

void Player::SetRange(int range)
{
	//配列の範囲内に設定するため-1
	rangeNum_ = range - 1;
}

void Player::ChangeClub()
{
	if (Input::IsKeyDown(DIK_UP))
	{
		switch (club_)
		{
		case IRONCLUB:
			club_ = WOODENCLUB;
			break;
		case WOODENCLUB:
			club_ = SMALLCLUB;
			break;
		case SMALLCLUB:
			club_ = IRONCLUB;
			break;
		default:
			club_ = IRONCLUB;
			break;
		}
	}
	if (Input::IsKeyDown(DIK_DOWN))
	{
		switch (club_)
		{
		case IRONCLUB:
			club_ = SMALLCLUB;
			break;
		case WOODENCLUB:
			club_ = IRONCLUB;
			break;
		case SMALLCLUB:
			club_ = WOODENCLUB;
			break;
		default:
			club_ = IRONCLUB;
			break;
		}
	}
}

void Player::ChangeCamera()
{
	switch (camTargetNow_)
	{
	case PLAYER:
		camTargetNow_ = STAGESENTER;
		break;
	case STAGESENTER:
		camTargetNow_ = PLAYER;
	default:
		camTargetNow_ = PLAYER;
		break;
	}
}
