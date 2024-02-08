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
}

void Enemy::Update()
{
	//player��ǂ������Ăق���
	//����񂪂�
	//player�̐^���ɂ���Ƃ����񂶂�Ȃ����낤���@�ǂɂ͂Ԃ����łق�������

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