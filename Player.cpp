#include "Player.h"
#include "Stage.h"
#include "Goal.h"
#include "GolfClub.h"
#include "OutArea.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/CsvReader.h"
#include "Engine/SphereCollider.h"
#include "Engine/Global.h"
#include <fstream>

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),hModel_(-1), mass_(0.5f), force_(0.0f), friction_(-1.1f), gravity_(-5.8f)
	, velocity_{ 0.0f,0.0f,0.0f }, vy(0.0f), rangeNum_(0), csvSenterVal_{ 0.0f,0.0f,0.0f }
	, camTargetNow_(PLAYER), turns_(0), respawnPos_(0.0f, 0.0f, 0.0f), isShoot_(false), isFly_(false)
	, isTreeHit_(false), isLakeAreaHit_(false), isSandAreaHit_(false), isOutAreaHit_(false)
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

	//コリジョン判定を設定
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
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y += 1.2f;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y -= 1.2f;
	}

	if (Input::IsKey(DIK_1))
	{
		Save();
	}

	float dt = deltaTime();
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
#if true
	GolfClub* pGolfClub = (GolfClub*)FindObject("GolfClub");
	const float MAX_SPEED = 3.0f;
	static bool pushKeyRock = false;

	switch (pGolfClub->ChangeClub())
	{
	case IRONCLUB:
		velocity_.y = 2.0f;
		velocity_.z = 3.0f;
		break;
	case WOODENCLUB:
		velocity_.y = 3.5f;
		velocity_.z = 1.5f;
		break;
	case SMALLCLUB:
		velocity_.y = 0.0f;
		velocity_.z = 2.7f;
		break;
	default:
		break;
	}

#if false
	if (!(isShoot_))
	{
		if (Input::IsKeyDown(DIK_SPACE) && camTargetNow_ == PLAYER && !(pushKeyRock))
		{
			pushKeyRock = true;
			pGolfClub->IsAnimStart(true);
			turns_++;//ターン数加算
		}
		if (pGolfClub->GetAnimEnd())//アニメーションが終わったら打つ
		{
			respawnPos_ = transform_.position_;//リスポーン地点の設定
			force_ = (velocity_.z * powerRate_[rangeNum_]) * mass_;//運動方程式
			vy = velocity_.y * sinf(45.0f) + gravity_ * dt;//斜方投射
			isFly_ = true;
			isShoot_ = true;
		}
	}
#else
	if (!(isShoot_))
	{
		if (Input::IsKeyDown(DIK_SPACE) && camTargetNow_ == PLAYER)
		{
			respawnPos_ = transform_.position_;//スポーン地点の設定
			force_ = (velocity_.z * powerRate_[rangeNum_]) * mass_;
			vy = velocity_.y * sinf(45.0f) + gravity_ * dt;//斜方投射
			isShoot_ = true;
			isFly_ = true;
			turns_++;//ターン数加算
		}
	}
#endif
	if (!(isFly_))
	{
		if (force_ > 0)
		{
			force_ += friction_ * dt;//減速
		}
		else if (!(isLakeAreaHit_))
		{
			//プレイヤーの値やフラグを初期化
			force_ = 0.0f;
			vy = 0.0f;
			isShoot_ = false;
			isTreeHit_ = false;
			pushKeyRock = false;
		}
	}
	vy += gravity_ * dt;//落下

	//最高スピード
	if (force_ > MAX_SPEED)
	{
		force_ = MAX_SPEED;
	}
	
	XMVECTOR vMoveY = XMVectorSet(0, vy, 0, 0);
	XMVECTOR vMoveZ = XMVectorSet(0, 0, force_, 0);

	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	vMoveZ = XMVector3TransformCoord(vMoveZ, mRotate);
	//OutputDebugStringA(("force_:" + std::to_string(force_) + "\n").c_str());
	//OutputDebugStringA(("vy:" + std::to_string(vy) + "\n").c_str());
	//OutputDebugStringA(("position_.y:" + std::to_string(transform_.position_.y) + "\n").c_str());
	//OutputDebugStringA(("Timer:" + std::to_string(dt) + "\n").c_str());
	//OutputDebugStringA(("range:" + std::to_string(rangeNum_) + "\n").c_str());
	//OutputDebugStringA(("AreaHit:" + std::to_string(isLakeAreaHit_) + "\n").c_str());

	vPos += vMoveY;
	if (isTreeHit_)
	{
		//反発の計算
		XMVECTOR normal = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		float res = 0.5f;//反発率
		XMVector3Normalize(normal);
		vMoveZ = vMoveZ - (1.0f + res) * XMVector3Dot(vMoveZ, normal) * normal;
	}

	vPos += vMoveZ;
	XMStoreFloat3(&transform_.position_, vPos);

	//エリア外のレイキャスト
	OutArea* pOutArea = (OutArea*)FindObject("OutArea");    //ステージオブジェクトを探す
	int hOutAreaModel = pOutArea->GetModelHandle();    //モデル番号を取得
	RayCast(hOutAreaModel);

	//ステージ上のレイキャスト
	Stage* pStage = (Stage*)FindObject("Stage");//ステージオブジェクトを探す
	int hStageModel = pStage->GetModelHandle();//モデル番号を取得
	RayCast(hStageModel);

	//ゴール地点のレイキャスト
	Goal* pGoal = (Goal*)FindObject("Goal");    //ステージオブジェクトを探す
	int hGoalModel = pGoal->GetModelHandle();    //モデル番号を取得
	RayCast(hGoalModel);

	isOutAreaHit_ = HitAreaRayCast(hOutAreaModel);

	if (isLakeAreaHit_)
	{
		force_ = 0.0f;
		vy = 0.0f;
		static float timer = 0.0f;
		timer += dt;
		if (timer > 3.0f)
		{
			//打った地点に移動
			transform_.position_ = respawnPos_;
			timer = 0.0f;
		}
	}

	if (isSandAreaHit_)
	{
		force_ *= 0.8f;
	}

	if (force_ <= 0.0f && isShoot_)
	{
		if (isOutAreaHit_)
		{
			transform_.position_ = respawnPos_;
		}
	}

	//エリア判定リセット
	{
		isLakeAreaHit_ = false;
		isSandAreaHit_ = false;
		isOutAreaHit_ = false;
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

	//ステージ上のレイキャスト
	Stage* pStage = (Stage*)FindObject("Stage");//ステージオブジェクトを探す
	int hStageModel = pStage->GetModelHandle();//モデル番号を取得

	//RayCastData data;
	//Transform tModel;
	//tModel = transform_;
	//float rayStart = 0.0f;
	//data.start = transform_.position_;
	//data.start.z = 0.0f;
	//data.dir = XMFLOAT3(0, 0, -1);
	//Model::RayCast(hStageModel, &data);
	//if (data.hit)
	//{
	//	transform_.position_.z = -data.dist; //+ data.start.y;
	//	//isFly_ = false;
	//}

	RayCastData data;
	Transform tModel;
	tModel = transform_;
	float rayStart = 0.0f;
	data.start = transform_.position_;
	data.start.z = 0.0f;
	data.dir = XMFLOAT3(0, 0, 1);
	Model::RayCast(hStageModel, &data);
	if (data.hit)
	{
		transform_.position_.z = -data.dist; //+ data.start.y;
		//isFly_ = false;
	}

	
	HitRayCast(hStageModel);

#endif

	XMVECTOR vCam;
	XMFLOAT3 camPos;
	XMFLOAT3 CamTarget;
	float camPosY;
	vPos = XMLoadFloat3(&transform_.position_);
	
	switch (camTargetNow_)
	{
	case PLAYER://プレイヤーを中心に見た視点
		vCam = { 0,4.0f,-11.0f,0 };
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
	if (!(isLakeAreaHit_))
	{
		Model::Draw(hModel_);
	}
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
	if (pTarget->GetObjectName() == "LakeArea")
	{
		isLakeAreaHit_ = true;
	}
	if (pTarget->GetObjectName() == "SandArea")
	{
		isSandAreaHit_ = true;
	}
}

void Player::SetRange(int range)
{
	//配列の範囲内に設定するため-1
	rangeNum_ = range - 1;
}

void Player::RayCast(int hModel)
{
	RayCastData data;
	Transform tModel;
	float rayStartHeight = 20.0f;
	data.start = transform_.position_;
	data.start.y = rayStartHeight;
	data.dir = XMFLOAT3(0, -1, 0);
	Model::RayCast(hModel, &data);
	if (data.hit)
	{
		tModel.position_.y = -data.dist + data.start.y;
		if (transform_.position_.y <= tModel.position_.y)
		{
			transform_.position_.y = tModel.position_.y;
			isFly_ = false;
		}
	}
}

bool Player::HitAreaRayCast(int hModel)
{
	RayCastData data;
	Transform tModel;
	float rayStartHeight = 20.0f;
	data.start = transform_.position_;
	data.start.y = rayStartHeight;
	data.dir = XMFLOAT3(0, -1, 0);
	Model::RayCast(hModel, &data);
	if (data.hit)
	{
		tModel.position_.y = -data.dist + data.start.y;
		if (transform_.position_.y <= tModel.position_.y)
		{
			return true;
		}
	}
	return false;
}

void Player::Save()
{
	std::ofstream ofs("saveData.txt");
	if (ofs.is_open())
	{
		ofs << "テストだよ" << std::endl;
	}
	else
	{
		OutputDebugStringA("ファイルが開けません");
	}
	ofs.close();
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
		break;
	default:
		camTargetNow_ = PLAYER;
		break;
	}
}
