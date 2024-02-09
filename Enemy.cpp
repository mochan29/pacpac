#include "Enemy.h"
#include "Engine/Model.h"
#include "Player.h"
#include "Stage.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"

void Enemy::Initialize()
{
	hModel_ = Model::Load("Model\\Enemy.fbx");
	assert(hModel_ >= 0);
	SphereCollider* collision = new SphereCollider({ 0,0,0 }, 0.6f);
	AddCollider(collision);
	pPlayer_ = (Player*)FindObject("Player");
	pStage_ = (Stage*)FindObject("Stage");
	transform_.position_.x = 0.5; //playerと同じ
	transform_.position_.z = 1.5; //playerと同じ
}

void Enemy::Update()
{
	//playerを追っかけてほしい
	//しらんがな
	//playerの真後ろにいるといいんじゃないだろうか　壁にはぶつからんでほしいけど

}

void Enemy::Draw()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{

	if (pTarget->GetObjectName() == "Player")
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_OVER);
	}
}