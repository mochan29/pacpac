#include "Enemy.h"
#include "Engine/Model.h"
#include "Player.h"
#include "Stage.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Debug.h" 

 void Enemy::Initialize()
{
	hModel_ = Model::Load("Model\\Enemy1.fbx");
	assert(hModel_ >= 0);
	SphereCollider* collision = new SphereCollider({ 0,0,0 }, 0.6f);
	AddCollider(collision);
	pPlayer_ = (Player*)FindObject("Player");
	pStage_ = (Stage*)FindObject("Stage");
	transform_.position_.x = 5.0; //player�Ɠ���
	transform_.position_.z = 10.0; //player�Ɠ���
}

void Enemy::Update()
{
	XMVECTOR vFront{ 0,0,1,0 }; //�������ǂ��ɂ�����p�̃x�N�g��
	float gapx =0.5f; //�߂肱�ݖh�~x
	float gapy =0.5f; //�߂肱�ݖh�~y
	XMFLOAT3 ptr = pPlayer_->GetPosition(); //�v���C���[�̍��W�I�ȃx�N�g��

	//�n�_:�v���C���[ �I�_:�G�A���K���Amove�ɂԂ�����
	float epX = this->GetPosition().x-ptr.x; //x���W�̍�
	float epZ = this->GetPosition().z-ptr.z; //z���W�̍�
	//float epNormalize = sqrt((epX * epX) + (epY * epY));
	//epX /= epNormalize;
	//epY /= epNormalize;
	
	XMVECTOR move{ 0,0,0,0 };
	int a = 0;
	Debug::Log("epX=");
	Debug::Log(epX, true);
	Debug::Log("epZ=");
	Debug::Log(epZ ,true);
	//x�̍��̕����傫����΁A�Ƃ肠�������ɂ��ア�񂷂�
	if (epX >= 0 && epZ >= 0)//�v���C���[���E��ɓG
	{
		a = 0;
		if (fabs(epX) > fabs(epZ))//���ɑ���
		{
			move ={ -1,0,0,0 };
			gapx = -0.5f;
		}
		else //���ɑ���=z����+
		{
			move ={ 0,0,-1,0 };
			gapy = -0.5f;
		}
	}
	else if (epX < 0 && epZ >= 0)//�v���C���[��荶��ɓG
	{
		a = 1;
		if (fabs(epX) > fabs(epZ))//�E�ɑ���
		{
			move ={ 1,0,0,0 };
			gapx = 0.5f;
		}
		else //���ɑ���
		{
			move ={ 0,0,-1,0 };
			gapy = -0.5f;
		}
	}
	else if (epX >= 0 && epZ < 0)//�v���C���[���E���ɓG
	{
		a = 2;
		if (fabs(epX) > fabs(epZ))//���ɑ���
		{
			move ={ -1,0,0,0 };
			gapx = -0.5f;
		}
		else //��ɑ���
		{
			move ={ 0,0,+1,0 };
			gapy = 0.5f;
		}
	}
	else if (epX < 0 && epZ < 0)//�v���C���[��荶���ɓG
	{
		a = 3;
		if (fabs(epX) > fabs(epZ))//�E�ɑ���
		{
			move = { 1,0,0,0 };
			gapx = 0.5f;
		}
		else //��ɑ���
		{
			move ={ 0,0,+1,0 };
			gapy = 0.5f;
		}
	}

	//Debug::Log("epX=");
	//Debug::Log(epX, true);
	//Debug::Log("epY=");
	//Debug::Log(epY,true);
	Debug::Log(a, true);
		//���̂ݓ�ǔ� �v
#if 0
	if (transform_.position_.x < ptr.x) //�v���C���[���E
	{
		move = XMVECTOR{ 1,0,0,0 };
		gapx = +0.5f;
	}
	else if (transform_.position_.x>ptr.x) //�v���C���[����
	{
		move = XMVECTOR{ -1,0,0,0 };
		gapx = -0.5f;
	}
	if (transform_.position_.y < ptr.y) //�v���C���[����
	{
		move = XMVECTOR{ 0,0,1,0 };
		gapy = +0.5f;
	}
	else if (transform_.position_.y > ptr.y) //�v���C���[����
	{
		move = XMVECTOR{ 0,0,-1,0 };
		gapy = -0.5f;
	}
#endif

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