#include "Room.h"

using namespace Math;

Room::Room()
{
	mWestWallMesh = nullptr;
	mEastWallMesh = nullptr;
	mNorthWallMesh = nullptr;
	mSouthWallMesh = nullptr;
	mRoofMesh = nullptr;
	mFloorMesh = nullptr;
}

Room::Room(float left, float top, float right, float bottom) : mBounds(left,top,right, bottom)
{
	mWestWallMesh= new Graphics::Mesh();
	Graphics::MeshBuilder::buildCube(*mWestWallMesh);
	
	mEastWallMesh = nullptr;
	mNorthWallMesh = nullptr;
	mSouthWallMesh = nullptr;
	mRoofMesh = nullptr;
	mFloorMesh = nullptr;

}


