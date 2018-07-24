#include "RTS.h"
#include "Core\Inc\Core.h"
#include "Graphics\Inc\Graphics.h"

using namespace RTS;

namespace
{
	MathLibrary::Vector3 camPosition(0.0f, 30.0f, 0.0f);
	MathLibrary::Vector3 camDirection(0.0f, -1.0f, 0.1f);

	bool drag = false;
	MathLibrary::Vector3 dragStart;
}

void RTS::UpdateCamera(float deltaTime, Graphics::Camera camera)
{
	if (!drag)
	{
		const float kMoveSpeed = 20.0f;
		if (Input::InputSystem::Get()->IsMouseRightEdge())
		{
			camPosition.X += kMoveSpeed * deltaTime;	
		}
		else if (Input::InputSystem::Get()->IsMouseLeftEdge())
		{
			camPosition.X -= kMoveSpeed * deltaTime;
		}
		if (Input::InputSystem::Get()->IsMouseTopEdge())
		{
			camPosition.Z += kMoveSpeed * deltaTime;
		}
		else if (Input::InputSystem::Get()->IsMouseBottomEdge())
		{
			camPosition.Z -= kMoveSpeed * deltaTime;
		}
	}	
	camera.SetPosition(camPosition);
	camera.SetDirection(camDirection);
}

void RTS::DrawGround()
{
	for (int i = 0; i <= 100; ++i)
	{
		Graphics::SimpleDraw::AddLine(-50.0f + i, 0.0f, -50.0f, -50.0f + i, 0.0f, 50.0f, MathLibrary::Vector4::DarkGray());		
		Graphics::SimpleDraw::AddLine(-50.0f, 0.0f, -50.0f + i, 50.0f, 0.0f, -50.0f + i, MathLibrary::Vector4::DarkGray());
	}
}

void RTS::DrawCursor()
{
	const float aX = (float)Input::InputSystem::Get()->GetMouseScreenX();
	const float aY = (float)Input::InputSystem::Get()->GetMouseScreenY();
	const float bX = aX + 20.0f;
	const float bY = aY + 10.0f;
	const float cX = aX + 10.0f;
	const float cY = aY + 20.0f;
	Graphics::SimpleDraw::AddScreenLine(aX, aY, bX, bY, MathLibrary::Vector4::Green());
	Graphics::SimpleDraw::AddScreenLine(aX, aY, cX, cY, MathLibrary::Vector4::Green());
	Graphics::SimpleDraw::AddScreenLine(bX, bY, cX, cY, MathLibrary::Vector4::Green());

	if (drag)
	{
		const float l = dragStart.X;
		const float t = dragStart.Y;
		const float r = (float)Input::InputSystem::Get()->GetMouseScreenX();
		const float b = (float)Input::InputSystem::Get()->GetMouseScreenY();
		Graphics::SimpleDraw::AddScreenRect(l, t, r, b, MathLibrary::Vector4::Green());
	}
}

bool RTS::GetSelectionBox(float& minX, float& maxX, float& minZ, float& maxZ)
{
	if (!drag)
	{
		if (Input::InputSystem::Get()->IsMousePressed(Mouse::LBUTTON))
		{
			drag = true;
			dragStart.X = (float)Input::InputSystem::Get()->GetMouseScreenX();
			dragStart.Y = (float)Input::InputSystem::Get()->GetMouseScreenY();
		}
	}
	else
	{
		if (!Input::InputSystem::Get()->IsMouseDown(Mouse::LBUTTON))
		{
			drag = false;

			MathLibrary::Ray startRay = Input::InputSystem::Get()->GetScreenRay((int)dragStart.X, (int)dragStart.Y);
			MathLibrary::Ray endRay = Input::InputSystem::Get()->GetMouseRay();
			MathLibrary::Plane groundPlane;

			float startDist = 0.0f;
			float endDist = 0.0f;
			MathLibrary::Intersect(startRay, groundPlane, startDist);
			MathLibrary::Intersect(endRay, groundPlane, endDist);

			MathLibrary::Vector3 startPoint = MathLibrary::GetPoint(startRay, startDist);
			MathLibrary::Vector3 endPoint = MathLibrary::GetPoint(endRay, endDist);
			minX = MathLibrary::Min(startPoint.X, endPoint.X);
			maxX = MathLibrary::Max(startPoint.X, endPoint.X);
			minZ = MathLibrary::Min(startPoint.Z, endPoint.Z);
			maxZ = MathLibrary::Max(startPoint.Z, endPoint.Z);
			return true;
		}
	}
	return false;
}

MathLibrary::Vector3 RTS::GetGroundPosition(const MathLibrary::Ray& ray)
{
	MathLibrary::Plane groundPlane;

	// Check ground plane
	float distance = 0.0f;
	MathLibrary::Intersect(ray, groundPlane, distance);
	return MathLibrary::GetPoint(ray, distance);
}

MathLibrary::Vector3 RTS::GetSpiralPosition(const MathLibrary::Vector3& startPos, int n)
{
	MathLibrary::Vector3 pos = startPos;
	MathLibrary::Vector3 offset(0.0f, 0.0f, 1.0f);
	int nextDir = 1;
	int nextSign = 2;
	int nextStep = 1;
	for (int i = 1; i <= n; ++i)
	{
		pos += offset;

		if (i == nextSign)
		{
			offset *= -1.0f;
			nextStep += 1;
			nextSign += 2 * nextStep;
		}
		if (i == nextDir)
		{
			float temp = offset.X;
			offset.X = offset.Z;
			offset.Z = temp;
			nextDir += nextStep;
		}
	}

	return pos;
}