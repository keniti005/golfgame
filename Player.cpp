#include "Player.h"
#include "Engine/Fbx.h"
#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/CsvReader.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), mass_(0.5f), force_(0.0f), friction_(-0.6f), gravity_(-0.98f)
	, velocity{ 1.0f,1.0f,3.0f }, vy(0.0f), isRool_(false), isFly_(false)
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
	
	const float MAX_SPEED = 3.0f;
	//float v = 0.0f;

	if (!(isRool_))
	{
		if (Input::IsKeyDown(DIK_SPACE))
		{
			force_ = velocity.z * mass_;//運動方程式
			isRool_ = true;
		}
	}

	if (!(isFly_))
	{
		if (force_ > 0)
		{
			force_ += friction_ * dt;
		}
		else
		{
			force_ = 0.0f;
			isRool_ = false;
		}
	}

	if (force_ > MAX_SPEED)
	{
		force_ = MAX_SPEED;
	}

	if (!(isFly_))
	{
		if (Input::IsKeyDown(DIK_UP))
		{
			vy = 0.0f;
			vy = velocity.y * sinf(45.0f);//斜方投射
			isFly_ = true;
		}
	}

	if (vy >= 0.0f)
	{
		vy += gravity_ * dt;
	}

	pt = ct;


	XMVECTOR vMoveY = XMVectorSet(0, vy, 0, 0);
	XMVECTOR vMoveZ = XMVectorSet(0, 0, force_, 0);

	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	vMoveZ = XMVector3TransformCoord(vMoveZ,mRotate);
	OutputDebugStringA(("force_:" + std::to_string(force_) + "\n").c_str());
	OutputDebugStringA(("vy:" + std::to_string(vy) + "\n").c_str());
	OutputDebugStringA(("position_.y:" + std::to_string(transform_.position_.y) + "\n").c_str());


	vPos += vMoveY;
	vPos += vMoveZ;
	XMStoreFloat3(&transform_.position_, vPos);

	Stage* stage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
	int hStageModel = stage->GetModelHandle();    //モデル番号を取得

	RayCastData data;
	float rayStart = 10.0f;
	data.start = transform_.position_;   //レイの発射位置
	data.start.y = rayStart;

	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStageModel, &data); //レイを発射

	Transform t;
	//レイが当たったら
	if (data.hit)
	{
		//その分位置を下げる
		//transform_.position_.y = -data.dist + data.start.y;
		t.position_.y = -data.dist + data.start.y;
	}

	if (transform_.position_.y <= t.position_.y)
	{
		transform_.position_.y = t.position_.y;
		isFly_ = false;
	}

#else//デバッグ用
	XMVECTOR vMoveY = XMVectorSet(0, 0.2f, 0, 0);
	XMVECTOR vMoveZ = XMVectorSet(0, 0, 0.2f, 0);

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
}

void Player::Release()
{
	Model::Release(hModel_);
}
