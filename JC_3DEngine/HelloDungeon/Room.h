#pragma once
#include <Math\Inc\EngineMath.h>
#include <Graphics\Inc\Graphics.h>


class Room
{
public:

	Room();
	Room(float left, float top, float right, float bottom);

public:

	Math::Rect mBounds;
	Math::Vector2 mCenterPoint;

	Graphics::Mesh* mWestWallMesh;
	Graphics::Mesh* mEastWallMesh;
	Graphics::Mesh* mNorthWallMesh;
	Graphics::Mesh* mSouthWallMesh;
	Graphics::Mesh* mRoofMesh;
	Graphics::Mesh* mFloorMesh;


};