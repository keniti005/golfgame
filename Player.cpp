#include "Player.h"
#include "Engine/Fbx.h"
#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/CsvReader.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),pFbx_(nullptr)
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
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	XMVECTOR vMoveY = XMVectorSet(0, 0.2f, 0, 0);
	XMVECTOR vMoveZ = XMVectorSet(0, 0, 0.2f, 0);

	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	vMoveZ = XMVector3TransformCoord(vMoveZ,mRotate);

#if true //デバッグ用
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
	//if (transform_.rotate_.y >= 720.0f)
	//{
	//	KillMe();
	//}

	Stage* stage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
	int hStageModel = stage->GetModelHandle();    //モデル番号を取得

	RayCastData data;
	float rayStart = 10.0f;
	data.start = transform_.position_;   //レイの発射位置
	data.start.y = rayStart;

	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStageModel, &data); //レイを発射

	//レイが当たったら
	if (data.hit)
	{
		//その分位置を下げる
		transform_.position_.y = -data.dist + data.start.y;
	}

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
