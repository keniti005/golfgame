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


	BoxCollider* collicion = new BoxCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f));
	AddCollider(collicion);
}

void Tree::Update()
{
}

void Tree::Draw()
{
	for (int y = 0;)
	{
		for (int x = 0;)
		{
			transform_.position_.x = (10.0f * x);
			transform_.position_.z = -(10.0f * y);
			Model::SetTransform(hModel_, transform_);
			Model::Draw(hModel_);
			CollisionDraw();
		}
	}
}

void Tree::Release()
{
	Model::Release(hModel_);
}

void Tree::OnCollision(GameObject* pTarget)
{
}
