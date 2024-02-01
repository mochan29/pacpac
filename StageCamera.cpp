#include "StageCamera.h"
#include "Engine/Camera.h"

void StageCamera::Initialize()
{
	Camera::SetPosition({ 6.5, 10, -3 });
	Camera::SetTarget({ 6.5, 0, 5.5 });
}
