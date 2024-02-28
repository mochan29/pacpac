#include "Apple.h"
#include "Engine/Model.h"
#include "Player.h"
#include "Stage.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"

void Apple::Initialize()
{
	hModel_ = Model::Load("Model\\Apple.fbx");
	assert(hModel_ >= 0);
	SphereCollider* collision = new SphereCollider({ 0,0,0 }, 0.4f);
	AddCollider(collision);
	pStage_ = (Stage*)FindObject("Stage");


	//•Ç‚Å‰Šú‰»‚ð–h‚®
	int x, z;
	do
	{
		x = (rand() % 13) + 1;
		z = (rand() % 13) + 1;
	} while (!(pStage_->isWall(x, z)));

	//Debug::Log("X=");
	//Debug::Log(x, true);
	//Debug::Log("Z=");
	//Debug::Log(z ,true);

	transform_.position_.x = float(x) + 0.5f;
	transform_.position_.z = float(z);
}

void Apple::Update()
{
	
}

void Apple::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Apple::OnCollision(GameObject* pTarget)
{
	Player* pPlayer = (Player*)FindObject("Player");
	if (pTarget->GetObjectName() == "Player")
	{
		this->KillMe();
	}
}

