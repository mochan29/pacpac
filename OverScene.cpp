#include "OverScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

void OverScene::Initialize()
{
	hImage_ = Image::Load("Image\\over.png");
	assert(hImage_ >= 0);
}

void OverScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void OverScene::Draw()
{
	Image::Draw(hImage_);
}