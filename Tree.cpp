#include "Tree.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "Engine/BoxCollider.h"

Tree::Tree(GameObject* parent)
	:GameObject(parent,"Tree")
{
}

Tree::~Tree()
{
}

void Tree::Initialize()
{
	transform_.scale_.x = 3.0f;
	transform_.scale_.y = 3.5f;
	transform_.scale_.z = 3.0f;
	hModel_ = Model::Load("tree.fbx");
	assert(hModel_ > 0);
	BoxCollider* collicion = new BoxCollider(XMFLOAT3(transform_.position_.x, transform_.position_.y + (transform_.scale_.y + 2.5) / 2.0f, transform_.position_.z),
		XMFLOAT3(transform_.scale_.x / 2.0f, transform_.scale_.y + 2.5, transform_.scale_.z / 2.0f));
	AddCollider(collicion);
}

void Tree::Update()
{
}

void Tree::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	CollisionDraw();
}

void Tree::Release()
{
	Model::Release(hModel_);
}

void Tree::OnCollision(GameObject* pTarget)
{
}
