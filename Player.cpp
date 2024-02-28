#include "Player.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Engine/SceneManager.h"
#include "Gauge.h"

void Player::Initialize()
{
	hModel_ = Model::Load("Model\\Player.fbx");
	assert(hModel_ >= 0);
	transform_.position_.x = 0.5;
	transform_.position_.z = 1.5;
	pStage_ = (Stage*)FindObject("Stage");
	SphereCollider* collision = new SphereCollider({ 0,0,0 }, 0.4f);
	AddCollider(collision);
}

void Player::Update()
{
	XMVECTOR vFront{ 0,0,1,0 }; //�ʒu���ǂ��ɂ�����p�̃x�N�g��
	XMVECTOR move{ 0,0,0,0 }; //�������ǂ��ɂ�����p�̃x�N�g��
	float gapx = 0.5f; //�߂肱�ݖh�~x
	float gapy = 0.5f; //�߂肱�ݖh�~y

	//�����ς���
#if 1
	//��͏�->0 ���v���
	int deg = -(degree_ % 360); //�p�x��0-360�ɂ���
	float ang = (XM_PI * float(deg)) / 180; //���W�A���ɒ���
	float moveSin_ = sinf(ang); //sin��
	float moveCos_ = cosf(ang); //cos��

	if (Input::IsKey(DIK_UP))
	{

		if (deg < DEFLEFT) //0-180
		{
			move = XMVECTOR{ moveCos_,0,moveSin_,0 };
			deg += 0.1;
		}
		else if (deg >= DEFLEFT) //180-360
		{
			move = XMVECTOR{ moveCos_,0,moveSin_,0 };
			deg -= 0.1;
		}
		gapx = -0.5f;
	}

	if (Input::IsKey(DIK_DOWN))
	{
		//0����Ȃ̂�deg�����������͂Ȃ�
		if (deg >= DEFRIGHT) //0-360
		{
			move = XMVECTOR{ moveCos_,0,moveSin_,0 };
			deg += 0.1;
		}
		gapx = +0.5f;
	}

	if (Input::IsKey(DIK_RIGHT))
	{
		if (deg < DEFUP) //0-90
		{
			move = XMVECTOR{ moveCos_,0,moveSin_,0 };
			deg += 0.1;
		}
		else if (deg >= DEFUP) //90-360 
		{
			move = XMVECTOR{ moveCos_,0,moveSin_,0 };
			deg -= 0.1;
		}
		//90�x�҂�����̎��͉������Ȃ�
		gapy = +0.5f;
	}

	if (Input::IsKey(DIK_LEFT))
	{
		if (deg < DEFDOWN) //0-270
		{
			move = XMVECTOR{ moveCos_,0,moveSin_,0 };
			deg += 0.1;
		}
		else if (deg >= DEFDOWN) //270-360
		{
			move = XMVECTOR{ moveCos_,0,moveSin_,0 };
			deg += 0.1;
		}
		gapy = -0.5f;
	}

	Debug::Log(moveCos_, true);
	Debug::Log("moveCos_", true);
	Debug::Log(moveSin_, true);
	Debug::Log("moveSin_", true);
#endif

#if 0
	if (Input::IsKey(DIK_UP))
	{
		move = XMVECTOR{ 0,0,1,0 };
		gapy = 0.5f;
	}
	if (Input::IsKey(DIK_DOWN))//270
	{
		move = XMVECTOR{ 0,0,-1,0 };
		gapy = -0.5f;
	}
	if (Input::IsKey(DIK_RIGHT))//0
	{
		move = XMVECTOR{ 1,0,0,0 };
		gapx = +0.5f;
	}
	if (Input::IsKey(DIK_LEFT))//180
	{
		move = XMVECTOR{ -1,0,0,0 };
		gapx = -0.5f;
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
		hpCrr_ = hpCrr_ - 2;
		if (hpCrr_ < 0)
		{
			hpCrr_ = 0;
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_OVER);
		}
	}

	//arctan��limx->0�Ł� atan2�Ŋp�x�o���ق�������(���Ƀ�>180),���̑���cos
	//�x�N�g����0����Ȃ�������
	if (!XMVector3Equal(move, XMVectorZero()))
	{
		XMStoreFloat3(&(transform_.position_), pos);//vector->float
	
	//acos
#if 1
		XMVECTOR vdot = XMVector3Dot(vFront, move);//����
		assert(XMVectorGetX(vdot) <= 1 && XMVectorGetX(vdot) >= -1);
		float angle = acos(XMVectorGetX(vdot));//acos[0,pi]
		//�O�ςŔ��f<=>y�����̒P�ʃx�N�g�����}1�ǂ���
		XMVECTOR vCross = XMVector3Cross(vFront, move);
		if (XMVectorGetY(vCross) < 0)
		{
			angle *= -1;
		}
#endif
	
	//atan
#if 0
			XMMATRIX rot = XMMatrixRotationY(XM_PIDIV2);
			XMVECTOR modifiedVec = XMVector3Transform(move, rot);
			float angle = atan2(XMVectorGetZ(modifiedVec), XMVectorGetX(modifiedVec));
#endif
	
		transform_.rotate_.y = XMConvertToDegrees(angle);//radian->degree
		}

	Gauge* pGauge = (Gauge*)FindObject("Gauge");
	pGauge->SetGaugeVal(hpMax_, hpCrr_);
	
	//�G�T�S���������N���A
	if (appCnt_ > AppleNum)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::OnCollision(GameObject* pTarget)
{
	Apple* pApple_ = (Apple*)FindObject("Apple");
	if (pTarget->GetObjectName() == "Apple")
	{
		appCnt_++;
		if (hpCrr_ < hpMax_-BOUNS)
		{
			hpCrr_ += BOUNS;
		}
	}
}