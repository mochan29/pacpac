#include "Player.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/Input.h"

void Player::Initialize()
{
	hModel_ = Model::Load("Model\\Player.fbx");
	assert(hModel_ >= 0);

	transform_.position_.x = 0.5;
	transform_.position_.y = 0.0;
	transform_.position_.z = 1.5;

	SphereCollider* collision = new SphereCollider({ 0,0,0 }, 0.6f);
	AddCollider(collision);
}

void Player::Update()
{
	XMVECTOR vFront{ 0,0,1,0 };
	XMVECTOR move{ 0,0,1,0 };
	if (Input::IsKey(DIK_UP))
	{
		move = XMVECTOR{ 0,0,1,0 };
	}
	if (Input::IsKey(DIK_DOWN))
	{
		move = XMVECTOR{ 0,0,-1,0 };
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		move = XMVECTOR{ 1,0,0,0 };
	}
	if (Input::IsKey(DIK_LEFT))
	{
		move = XMVECTOR{ -1,0,0,0 };
	}

	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));//float->vector
	pos = pos + speed_ * move;
	XMStoreFloat3(&(transform_.position_), pos);//vector->float
	XMVECTOR vdot=XMVector3Dot(vFront, move);//“àÏ
	float angle = acos(XMVectorGetX(vdot));//acos
	transform_.rotate_.y = XMConvertToDegrees(angle);//radian->degree
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