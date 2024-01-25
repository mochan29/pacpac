#include "ClearScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

void ClearScene::Initialize()
{
	hImage_ = Image::Load("Image\\retry.png");
	assert(hImage_ >= 0);
}

void ClearScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void ClearScene::Draw()
{
	Image::Draw(hImage_);
}