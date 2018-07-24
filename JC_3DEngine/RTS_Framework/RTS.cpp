#include "RTS.h"


using namespace RTS;

namespace
{
	Vector3 camPosition(0.0f, 30.0f, 0.0f);
	Vector3 camDirection(0.0f, -1.0f, 0.01f);

	bool drag = false;
	Vector3 dragStart;
}

void RTS::UpdateCamera(float deltaTime, Graphics::Camera& camera)
{

	if (!drag)
	{
		const float kMoveSpeed = 20.0f;
		if ( Input::InputSystem::Get()->IsMouseRightEdge())
		{
			camPosition.x += kMoveSpeed * deltaTime;
		}
		else if ( Input::InputSystem::Get()->IsMouseLeftEdge())
		{
			camPosition.x -= kMoveSpeed * deltaTime;
		}
		if ( Input::InputSystem::Get()->IsMouseTopEdge())
		{
			camPosition.z += kMoveSpeed * deltaTime;
		}
		else if ( Input::InputSystem::Get()->IsMouseBottomEdge())
		{
			camPosition.z -= kMoveSpeed * deltaTime;
		}
	}

	camera.SetPosition(camPosition);
	camera.SetDirection(camDirection);
}

void RTS::DrawGround()
{
	for (int i = 0; i <= 100; ++i)
	{
		Graphics::SimpleDraw::AddLine(-50.0f + i, 0.0f, -50.0f, -50.0f + i, 0.0f, 50.0f, Vector4::DarkGray());
		Graphics::SimpleDraw::AddLine(-50.0f, 0.0f, -50.0f + i, 50.0f, 0.0f, -50.0f + i, Vector4::DarkGray());
	}
}

void RTS::DrawCursor()
{
	const float aX = (float) Input::InputSystem::Get()->GetMouseScreenX();
	const float aY = (float) Input::InputSystem::Get()->GetMouseScreenY();
	const float bX = aX + 20.0f;
	const float bY = aY + 10.0f;
	const float cX = aX + 10.0f;
	const float cY = aY + 20.0f;
	Graphics::SimpleDraw::AddScreenLine(aX, aY, bX, bY, Vector4::Green());
	Graphics::SimpleDraw::AddScreenLine(aX, aY, cX, cY, Vector4::Green());
	Graphics::SimpleDraw::AddScreenLine(bX, bY, cX, cY, Vector4::Green());

	if (drag)
	{
		const float l = dragStart.x;
		const float t = dragStart.y;
		const float r = (float) Input::InputSystem::Get()->GetMouseScreenX();
		const float b = (float) Input::InputSystem::Get()->GetMouseScreenY();
		Graphics::SimpleDraw::AddScreenRect(l, t, r, b, Vector4::Green());
	}
}

bool RTS::GetSelectionBox(float& minX, float& maxX, float& minZ, float& maxZ, Graphics::Camera& camera)
{
	if (!drag)
	{
		if ( Input::InputSystem::Get()->IsMousePressed(Mouse::LBUTTON))
		{
			drag = true;
			dragStart.x = (float) Input::InputSystem::Get()->GetMouseScreenX();
			dragStart.y = (float) Input::InputSystem::Get()->GetMouseScreenY();			
		}
	}
	else
	{
		if (! Input::InputSystem::Get()->IsMouseDown(Mouse::LBUTTON))
		{
			drag = false;

			Ray startRay =  Input::InputSystem::Get()->GetScreenRay((int)dragStart.x, (int)dragStart.y, camera );
			Ray endRay =  Input::InputSystem::Get()->GetMouseRay(camera);
			Plane groundPlane(0,-1,0,0);

			float startDist = 0.0f;
			float endDist = 0.0f;           
			Intersect(startRay, groundPlane, startDist);
			Intersect(endRay, groundPlane, endDist);

			Vector3 startPoint = GetPoint(startRay, startDist);
			Vector3 endPoint = GetPoint(endRay, endDist);
			minX = Min(startPoint.x, endPoint.x);
			maxX = Max(startPoint.x, endPoint.x);
			minZ = Min(startPoint.z, endPoint.z);
			maxZ = Max(startPoint.z, endPoint.z);
			return true;
		}
	}
	return false;
}

Vector3 RTS::GetGroundPosition(const Ray& ray)
{
	Plane groundPlane;

	// Check ground plane
	float distance = 0.0f;
	Intersect(ray, groundPlane, distance);
	return GetPoint(ray, distance);
}

Vector3 RTS::GetSpiralPosition(const Vector3& startPos, int n)
{
	Vector3 pos = startPos;
	Vector3 offset(0.0f, 0.0f, 1.0f);
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
			float temp = offset.x;
			offset.x = offset.z;
			offset.z = temp;
			nextDir += nextStep;
		}
	}

	return pos;
}