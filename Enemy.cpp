#include "Enemy.h"
#include "Engine/Model.h"
#include "Player.h"
#include "Stage.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Debug.h" 

void Enemy::Initialize()
{
	hModel_ = Model::Load("Model\\enemy1.fbx");
	hModel2_ = Model::Load("Model\\enemy2.fbx");
	assert(hModel_ >= 0);
	assert(hModel2_ >= 0);
	SphereCollider* collision = new SphereCollider({ 0,0,0 }, 0.3f);
	AddCollider(collision);
	pPlayer_ = (Player*)FindObject("Player");
	pStage_ = (Stage*)FindObject("Stage");
	a = rand() % 2;
	

	//�ǂŏ�������h��
	int x, z;
	do
	{
		x = (rand() % 13)+1;
		z = (rand() % 13)+1;
	} while (!(pStage_->isWall(x,z)));

	//Debug::Log("X=");
	//Debug::Log(x, true);
	//Debug::Log("Z=");
	//Debug::Log(z ,true);

	transform_.position_.x = float(x)+0.5f;
	transform_.position_.z =float(z);
}

void Enemy::Update()
{
	XMVECTOR vFront{ 0,0,1,0 }; //�������ǂ��ɂ�����p�̃x�N�g��
	float gapx =0.5f; //�߂肱�ݖh�~x
	float gapy =0.5f; //�߂肱�ݖh�~y
	XMFLOAT3 ptr = pPlayer_->GetPosition(); //�v���C���[�̍��W�I�ȃx�N�g��

	//�n�_:�v���C���[ �I�_:�G�Amove�ɂԂ�����
	float epX = this->GetPosition().x-ptr.x; //x���W�̍�
	float epZ = this->GetPosition().z-ptr.z; //z���W�̍�
	
	XMVECTOR move{ 0,0,1,0 };
	int a = 0;
	//Debug::Log("epX=");
	//Debug::Log(epX, true);
	//Debug::Log("epZ=");
	//Debug::Log(epZ ,true);

	//�G�����AI(������)
	//x�̍��̕����傫����΁A�Ƃ肠�������ɂ��ア�񂷂�
	if (epX >= 0 && epZ >= 0)//�v���C���[���E��ɓG
	{
		a = 0;
		if (fabs(epX) > fabs(epZ))//���ɑ���
		{
			move ={ -1,0,0,0 };
			gapx = -0.5f;
		}
		else //���ɑ���
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

	//Debug::Log(a, true);

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
	else
	{
		move *= -1;
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
	
	if (a == 0)
	{
		Model::SetTransform(hModel_, transform_);
		Model::Draw(hModel_);
	}
	else
	{
		Model::SetTransform(hModel2_, transform_);
		Model::Draw(hModel2_);
	}
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_OVER);
	}
}