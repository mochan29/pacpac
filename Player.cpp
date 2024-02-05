#include "Player.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

void Player::Initialize()
{
	hModel_ = Model::Load("Model\\Player.fbx");
	assert(hModel_ >= 0);

	//(0.5,1.5)を原点として考える
	transform_.position_.x = 0.5;
	transform_.position_.z = 1.5;
	pStage_ = (Stage *)FindObject("Stage");
}

void Player::Update()
{
	XMVECTOR vFront{ 0,0,1,0 }; //向きをどうにかする用のベクトル
	XMVECTOR move{ 0,0,0,0 }; //位置をどうにかする用のベクトル

	//向き変える
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
	XMVECTOR postmp = XMVectorZero();
	postmp = pos + speed_ * move;
	int tx, ty;
	tx = (int)(XMVectorGetX(postmp)+1.0f);
	ty = pStage_->GetStageHeight() - (int)(XMVectorGetZ(postmp)+1.0f);
	if (!(pStage_->isWall(tx,ty)))
	{
		pos = postmp;
	}
#if 0
	Debug::Log("(x,z)=");
	Debug::Log(XMVectorGetX(pos));
	Debug::Log(",");
	Debug::Log(XMVectorGetZ(pos),true);

	Debug::Log("(ix,iy)=");
	Debug::Log(tx);
	Debug::Log(",");
	Debug::Log(ty);
#endif

	//ベクトルが0じゃなかったら
	if (!XMVector3Equal(move, XMVectorZero()))
	{
		XMStoreFloat3(&(transform_.position_), pos);//vector->float ここpostmpでは？？まあいいか
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