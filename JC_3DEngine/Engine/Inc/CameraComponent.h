#pragma once
#include "Graphics\Inc\Camera.h"
#include "Component.h"

class CameraComponent :Component
{
public:

	META_CLASS_DECLARE;

	CameraComponent();
	~CameraComponent() override;

	Graphics::Camera& GetCamera() { return mCamera; }

private:

	Graphics::Camera mCamera;

};