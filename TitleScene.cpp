#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"

void TitleScene::Initialize()
{
	hImage_ = Image::Load("Image\\start.png");
	assert(hImage_ >= 0);
}

void TitleScene::Update()
{
	if (Input::IsKey(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}
void TitleScene::Draw()
{
	Image::Draw(hImage_);
}
