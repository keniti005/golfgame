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
#include "Engine/SceneManager.h"


Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),hModel_(-1), mass_(0.5f), force_(0.0f), friction_(-1.1f), gravity_(-5.8f)
	, velocity{ 0.0f,0.0f,0.0f }, vy(0.0f), isShoot_(false), isFly_(false), isGoal_(false), club_(IRONCLUB)
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
				transform_.position_.x =  (10.0f * x);
				transform_.position_.z = -(10.0f * y);
			}
		}
	}

	SphereCollider* collicion = new SphereCollider(XMFLOAT3(0.0f,transform_.scale_.y / 2.0f,0.0f),0.7f);
	AddCollider(collicion);
}

void Player::Update()
{
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
	static float Timer = 0;
	const float MAX_SPEED = 3.0f;
	ChangeClub();
	
	if (isGoal_)
	{
		//タイマーが１０秒経過したらシーン遷移
		Timer += dt;
		if (Timer >= 10.0f)
		{
			SceneManager* scene = (SceneManager*)FindObject("SceneManager");
			scene->ChangeScene(SCENE_ID_TEST);
		}
	}

	switch (club_)
	{
	case IRONCLUB:
		velocity.y = 2.0f;
		velocity.z = 3.0f;
		if (!(isShoot_))
		{
			if (Input::IsKeyDown(DIK_SPACE))
			{
				force_ = velocity.z * mass_;//運動方程式
				vy = velocity.y * sinf(45.0f) + gravity_ * dt;//斜方投射
				isFly_ = true;
				isShoot_ = true;
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
				}
			}

			if (force_ > MAX_SPEED)
			{
				force_ = MAX_SPEED;
			}
		}
		break;
	case WOODENCLUB:
		velocity.y = 3.5f;
		velocity.z = 1.5f;
		if (!(isShoot_))
		{
			if (Input::IsKeyDown(DIK_SPACE))
			{
				force_ = velocity.z * mass_;//運動方程式
				vy = velocity.y * sinf(45.0f) + gravity_ * dt;//斜方投射
				isFly_ = true;
				isShoot_ = true;
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
				}
			}

			if (force_ > MAX_SPEED)
			{
				force_ = MAX_SPEED;
			}
		}
		break;
	case SMALLCLUB:
		velocity.y = 0.0f;
		velocity.z = 3.5f;
		if (!(isShoot_))
		{
			if (Input::IsKeyDown(DIK_SPACE))
			{
				force_ = velocity.z * mass_;//運動方程式
				vy = velocity.y * sinf(45.0f) + gravity_ * dt;//斜方投射
				isFly_ = true;
				isShoot_ = true;
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
				}
			}

			if (force_ > MAX_SPEED)
			{
				force_ = MAX_SPEED;
			}
		}

		break;
	default:
		break;
	}
	pt = ct;


	XMVECTOR vMoveY = XMVectorSet(0, vy, 0, 0);
	XMVECTOR vMoveZ = XMVectorSet(0, 0, force_, 0);

	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	vMoveZ = XMVector3TransformCoord(vMoveZ,mRotate);
	//OutputDebugStringA(("force_:" + std::to_string(force_) + "\n").c_str());
	//OutputDebugStringA(("vy:" + std::to_string(vy) + "\n").c_str());
	//OutputDebugStringA(("position_.y:" + std::to_string(transform_.position_.y) + "\n").c_str());
	OutputDebugStringA(("Timer:" + std::to_string(Timer) + "\n").c_str());


	vPos += vMoveY;
	vPos += vMoveZ;
	XMStoreFloat3(&transform_.position_, vPos);


	RayCastData data;
	float rayStart = 10.0f;
	data.start = transform_.position_;   //レイの発射位置
	data.start.y = rayStart;

	//ステージ上のレイキャスト
	Stage* stage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
	int hStageModel = stage->GetModelHandle();    //モデル番号を取得

	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStageModel, &data); //レイを発射

	Transform s;
	//レイが当たったら
	if (data.hit)
	{
		//その分位置を下げる
		//transform_.position_.y = -data.dist + data.start.y;
		s.position_.y = -data.dist + data.start.y;
	}
	if (transform_.position_.y <= s.position_.y)
	{
		vy = 0.0f;
		transform_.position_.y = s.position_.y;
		isFly_ = false;
	}
	else
	{
		vy += gravity_ * dt;
	}

	//ゴール地点のレイキャスト
	Goal* goal = (Goal*)FindObject("Goal");    //ステージオブジェクトを探す
	int hGoalModel = goal->GetModelHandle();    //モデル番号を取得
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hGoalModel, &data); //レイを発射

	Transform g;
	//レイが当たったら
	if (data.hit)
	{
		//その分位置を下げる
		//transform_.position_.y = -data.dist + data.start.y;
		g.position_.y = -data.dist + data.start.y;
		if (transform_.position_.y <= g.position_.y)
		{
			vy = 0.0f;
			transform_.position_.y = g.position_.y;
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

	XMVECTOR vCam = { 0,2.0f,-7.0f,0 };
	XMFLOAT3 camPos;
	vCam = XMVector3TransformCoord(vCam, mRotate);
	XMStoreFloat3(&camPos,vPos + vCam);
	Camera::SetPosition(camPos);

	XMFLOAT3 CamTarget = transform_.position_; 
	Camera::SetTarget(CamTarget);
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	CollisionDraw();
}

void Player::Release()
{
	Model::Release(hModel_);
}

void Player::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Tree")
	{
		int i = 0;
		i++;
	}
	if (pTarget->GetObjectName() == "Goal")
	{
		isGoal_ = true;
		force_ = 0.0f;
	}
}

void Player::ChangeClub()
{
	if (Input::IsKeyUp(DIK_UP))
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
