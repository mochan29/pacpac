#include "Enemy.h"
#include "Engine/Model.h"
#include "Player.h"
#include "Stage.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"

void Enemy::Initialize()
{
	hModel_ = Model::Load("Model\\Enemy1.fbx");
	assert(hModel_ >= 0);
	SphereCollider* collision = new SphereCollider({ 0,0,0 }, 0.6f);
	AddCollider(collision);
	pPlayer_ = (Player*)FindObject("Player");
	pStage_ = (Stage*)FindObject("Stage");
	transform_.position_.x = 3.0; //player�Ɠ���
	transform_.position_.z = 6.0; //player�Ɠ���
}

void Enemy::Update()
{
	//player�̐^���ɂ���Ƃ����񂶂�Ȃ����낤���@�ǂɂ͂Ԃ����łق�������
	//�G��x���W��player������������ΉE+�A�傫����΍�-�A
	//�G��y���W��player������������Ή�+�A�傫����Ώ�-
	XMVECTOR vFront{ 0,0,1,0 }; //�������ǂ��ɂ�����p�̃x�N�g��
	XMVECTOR move{ 0,0,0,0 }; //�ʒu���ǂ��ɂ�����p�̃x�N�g��
	float gapx = 0.5f; //�߂肱�ݖh�~x
	float gapy = 0.5f; //�߂肱�ݖh�~y
	XMFLOAT3 ptr = pPlayer_->GetPosition();

	if (transform_.position_.x < ptr.x) //�E
	{
		move = XMVECTOR{ 1,0,0,0 };
		gapx = +0.5f;
	}
	if (transform_.position_.x>=ptr.x) //��
	{
		move = XMVECTOR{ -1,0,0,0 };
		gapx = -0.5f;
	}

	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));//float->vector
	XMVECTOR postmp = XMVectorZero();
	postmp = pos + speed_ * move;
	int tx, ty;
	tx = (int)(XMVectorGetX(postmp) + 1.0f + gapx);
	ty = pStage_->GetStageHeight() - (int)(XMVectorGetZ(postmp) + 1.0f + gapy);
	if (!(pStage_->isWall(tx, ty)))
	{
		pos = postmp;
	}
	if (!XMVector3Equal(move, XMVectorZero()))
	{
		XMStoreFloat3(&(transform_.position_), pos);//vector->float

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

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_OVER);
	}
}