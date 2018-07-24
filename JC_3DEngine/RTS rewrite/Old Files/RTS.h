//====================================================================================================
// Filename:	RTS.h
// Created by:	Peter Chan
//====================================================================================================

#include "Input\Inc\Input.h"



namespace RTS {

void UpdateCamera(float deltaTime, Graphics::Camera camera);




void DrawGround();
void DrawCursor();

bool GetSelectionBox(float& minX, float& maxX, float& minZ, float& maxZ);

MathLibrary::Vector3 GetGroundPosition(const MathLibrary::Ray& ray);
MathLibrary::Vector3 GetSpiralPosition(const MathLibrary::Vector3& startPos, int n);

//Input::InputSystem* inputSystem = Input::InputSystem::Get();


} // namespace RTS