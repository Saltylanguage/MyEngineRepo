#include "Unit.h"

Unit::Unit()
	: mPosition(Vector3::Zero())
	, mDirection(Vector3::ZAxis())
	, mSelected(false)
{
}

void Unit::Update(float deltaTime)
{
	if (HasDestination())
	{
		const float kMoveSpeed = 2.0f;
		mDirection = Vector3::Normalize(mDestination - mPosition);
		mPosition += mDirection * kMoveSpeed * deltaTime;
	}
}

void Unit::Draw()
{
	Vector3 center(mPosition.x, mPosition.y + 0.25f, mPosition.z);
	Vector3 extend(0.5f, 0.25f, 1.0f);
	const float angle = atan2(mDirection.z, mDirection.z);
	Quaternion orientation = Quaternion::QuaternionRotationAxis(Vector3::YAxis(), angle);
	OBB obb(center, extend, orientation);
	if (mTeamID == 0)
	{
		Graphics::SimpleDraw::AddOBB(obb, Vector4::Cyan());
	}
	if (mTeamID == 1)
	{
		Graphics::SimpleDraw::AddOBB(obb, Vector4::Red());
	}

	if (mSelected)
	{
		const float minX = mPosition.x - 1.0f;
		const float minY = mPosition.y;
		const float minZ = mPosition.z - 1.0f;
		const float maxX = mPosition.x + 1.0f;
		const float maxY = mPosition.y;
		const float maxZ = mPosition.z + 1.0f;
		Graphics::SimpleDraw::AddAABB(minX, minY, minZ, maxX, maxY, maxZ, Vector4::Green());

		if (HasDestination())
		{
			Graphics::SimpleDraw::AddSphere(mDestination, 0.5f, Vector4::Magenta(), 6, 2);
		}
	}
}

void Unit::Serialize(Network::StreamWriter& writer)
{
	writer.Write(mPosition.x);
	writer.Write(mPosition.z);
	writer.Write(mDirection.x);
	writer.Write(mDirection.z);
	writer.Write(mTeamID);
}

void Unit::Deserialize(Network::StreamReader& reader)
{
	reader.Read(mPosition.x);
	reader.Read(mPosition.z);
	reader.Read(mDirection.x);
	reader.Read(mDirection.z);
	reader.Read(mTeamID);
	// Make sure destination matches position for now
	mDestination = mPosition;
}

bool Unit::HasDestination() const
{
	const float checkDist = 0.5f;
	return Vector3::DistanceXZSqr(mPosition, mDestination) > Sqr(checkDist);
}