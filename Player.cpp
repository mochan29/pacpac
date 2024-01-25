#include "Player.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

void Player::Initialize()
{
	hModel_ = Model::Load("Model\\Player.fbx");
	assert(hModel_ >= 0);

	SphereCollider* collision = new SphereCollider({ 0,0,0 }, 0.6f);
	AddCollider(collision);
	transform_.position_ = { 0,0,0 };
}

void Player::Update()
{
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::OnCollision(GameObject* pTarget)
{
	//if (pTarget->GetObjectName() == "Stage")
	//{
	//	this->KillMe();
	//	pTarget->KillMe();
	//}
}