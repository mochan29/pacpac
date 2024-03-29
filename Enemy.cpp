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
	ranColor_ = rand() % 2;

	//壁で初期化を防ぐ
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
	XMVECTOR vFront{ 0,0,1,0 }; //向きをどうにかする用のベクトル
	float gapx =0.5f; //めりこみ防止x
	float gapy =0.5f; //めりこみ防止y
	XMFLOAT3 ptr = pPlayer_->GetPosition(); //プレイヤーの座標的なベクトル

	//始点:プレイヤー 終点:敵、moveにぶちこむ
	float epX = this->GetPosition().x-ptr.x; //x座標の差
	float epZ = this->GetPosition().z-ptr.z; //z座標の差
	
	XMVECTOR move{ 0,0,1,0 };
	int a = 0;

	//Debug::Log("epX=");
	//Debug::Log(epX, true);
	//Debug::Log("epZ=");
	//Debug::Log(epZ ,true);

	//敵さんのAI(うざめ)
	//xの差の方が大きければ、とりあえず横にぎゅいんする
	if (epX >= 0 && epZ >= 0)//プレイヤーより右上に敵
	{
		a = 0;
		if (fabs(epX) > fabs(epZ))//左に送る
		{
			move ={ -1,0,0,0 };
			gapx = -0.5f;
		}
		else //下に送る
		{
			move ={ 0,0,-1,0 };
			gapy = -0.5f;
		}
	}
	else if (epX < 0 && epZ >= 0)//プレイヤーより左上に敵
	{
		a = 1;
		if (fabs(epX) > fabs(epZ))//右に送る
		{
			move ={ 1,0,0,0 };
			gapx = 0.5f;
		}
		else //下に送る
		{
			move ={ 0,0,-1,0 };
			gapy = -0.5f;
		}
	}
	else if (epX >= 0 && epZ < 0)//プレイヤーより右下に敵
	{
		a = 2;
		if (fabs(epX) > fabs(epZ))//左に送る
		{
			move ={ -1,0,0,0 };
			gapx = -0.5f;
		}
		else //上に送る
		{
			move ={ 0,0,+1,0 };
			gapy = 0.5f;
		}
	}
	else if (epX < 0 && epZ < 0)//プレイヤーより左下に敵
	{
		a = 3;
		if (fabs(epX) > fabs(epZ))//右に送る
		{
			move = { 1,0,0,0 };
			gapx = 0.5f;
		}
		else //上に送る
		{
			move ={ 0,0,+1,0 };
			gapy = 0.5f;
		}
	}

	//Debug::Log(a, true);

	//横のみ謎追尾 没
#if 0
	if (transform_.position_.x < ptr.x) //プレイヤーが右
	{
		move = XMVECTOR{ 1,0,0,0 };
		gapx = +0.5f;
	}
	else if (transform_.position_.x>ptr.x) //プレイヤーが左
	{
		move = XMVECTOR{ -1,0,0,0 };
		gapx = -0.5f;
	}
	if (transform_.position_.y < ptr.y) //プレイヤーが上
	{
		move = XMVECTOR{ 0,0,1,0 };
		gapy = +0.5f;
	}
	else if (transform_.position_.y > ptr.y) //プレイヤーが下
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

void Enemy::Draw()
{
	if (ranColor_ == 0)
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