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
	Player* pPlayer_ = (Player*)FindObject("Player");
	pStage_ = (Stage*)FindObject("Stage");
	transform_.position_.x =6.5;
	transform_.position_.z =3.0;
}

void Apple::Update()
{
	
}

void Apple::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

