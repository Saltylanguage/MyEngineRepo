//====================================================================================================
// Filename:	RTS.h
// Created by:	Peter Chan
//====================================================================================================
#include <Input\Inc\Input.h>

namespace RTS {

void UpdateCamera(float deltaTime, Graphics::Camera& camera);

void DrawGround();
void DrawCursor();

bool GetSelectionBox(float& minX, float& maxX, float& minZ, float& maxZ, Graphics::Camera& camera);

Vector3 GetGroundPosition(const Ray& ray);
Vector3 GetSpiralPosition(const Vector3& startPos, int n);

} // namespace RTS