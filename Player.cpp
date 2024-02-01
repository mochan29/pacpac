#include "Player.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

void Player::Initialize()
{
	hModel_ = Model::Load("Model\\Player.fbx");
	assert(hModel_ >= 0);

	transform_.position_.x = 0.5;
	transform_.position_.z = 1.5;
	//map[y][x]=map[13][1]が初期位置になるように
	//mapが1(壁)の時はどうにかこうにか
	//y(たて) 13->1.5 12->0.5 たぶん-1していくんだろうなあ？
	//x(よこ) x-0.5
}

void Player::Update()
{
	XMVECTOR vFront{ 0,0,1,0 }; //向きをどうにかする用のベクトル
	XMVECTOR move{ 0,0,0,0 }; //位置をどうにかする用のベクトル

	//向き変える
	if (Input::IsKeyDown(DIK_UP))
	{
		move = XMVECTOR{ 0,0,1,0 };
	}
	if (Input::IsKeyDown(DIK_DOWN))
	{
		move = XMVECTOR{ 0,0,-1,0 };
	}
	if (Input::IsKeyDown(DIK_RIGHT))
	{
		move = XMVECTOR{ 1,0,0,0 };
	}
	if (Input::IsKeyDown(DIK_LEFT))
	{
		move = XMVECTOR{ -1,0,0,0 };
	}

	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));//float->vector
	pos = pos + speed_ * move;

#if 0

	Debug::Log("(x,z)=");
	Debug::Log(XMVectorGetX(pos));
	Debug::Log(",");
	Debug::Log(XMVectorGetZ(pos));
#endif

	//ベクトルが0じゃなかったら
	if (!XMVector3Equal(move, XMVectorZero()))
	{
		XMStoreFloat3(&(transform_.position_), pos);//vector->float
		XMVECTOR vdot = XMVector3Dot(vFront, move);//内積
		assert(XMVectorGetX(vdot) <= 1 && XMVectorGetX(vdot) >= -1);
		float angle = acos(XMVectorGetX(vdot));//acos[0,pi]
		//外積で判断<=>y方向の単位ベクトルが±1どっち
		XMVECTOR vCross = XMVector3Cross(vFront, move);
		if (XMVectorGetY(vCross) < 0)
		{
			angle *= -1;
		}
		transform_.rotate_.y = XMConvertToDegrees(angle);//radian->degree
	}

}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}