#include "Player.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

void Player::Initialize()
{
	hModel_ = Model::Load("Model\\Player.fbx");
	assert(hModel_ >= 0);

	//(0.5,1.5)�����_�Ƃ��čl����
	transform_.position_.x = 0.5;
	transform_.position_.z = 1.5;
	pStage_ = (Stage *)FindObject("Stage");
}

void Player::Update()
{
	XMVECTOR vFront{ 0,0,1,0 }; //�������ǂ��ɂ�����p�̃x�N�g��
	XMVECTOR move{ 0,0,0,0 }; //�ʒu���ǂ��ɂ�����p�̃x�N�g��

	//�����ς���
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

	//�x�N�g����0����Ȃ�������
	if (!XMVector3Equal(move, XMVectorZero()))
	{
		XMStoreFloat3(&(transform_.position_), pos);//vector->float ����postmp�ł́H�H�܂�������
		XMVECTOR vdot = XMVector3Dot(vFront, move);//����
		assert(XMVectorGetX(vdot) <= 1 && XMVectorGetX(vdot) >= -1);
		float angle = acos(XMVectorGetX(vdot));//acos[0,pi]
		//�O�ςŔ��f<=>y�����̒P�ʃx�N�g�����}1�ǂ���
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