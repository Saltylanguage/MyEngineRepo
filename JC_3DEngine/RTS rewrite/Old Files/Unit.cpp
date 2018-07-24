#include "Unit.h"

Unit::Unit()
	: mPosition(MathLibrary::Vector3::Zero())
	, mDirection(MathLibrary::Vector3::ZAxis())
	, mSelected(false)
{
}

void Unit::Update(float deltaTime)
{
	if (HasDestination())
	{
		const float kMoveSpeed = 2.0f;
		mDirection = MathLibrary::Vector3::Normalize(mDestination - mPosition);
		mPosition += mDirection * kMoveSpeed * deltaTime;
	}
}

void Unit::Draw()
{
	MathLibrary::Vector3 center(mPosition.X, mPosition.Y + 0.25f, mPosition.Z);
	MathLibrary::Vector3 extend(0.5f, 0.25f, 1.0f);
	const float angle = atan2(mDirection.X, mDirection.Z);
	MathLibrary::Quaternion orientation = MathLibrary::Quaternion::QuaternionRotationAxis(MathLibrary::Vector3::YAxis(), angle);
	MathLibrary::OBB obb(center, extend, orientation);
	Graphics::SimpleDraw::AddOBB(obb, MathLibrary::Vector4::Cyan()); 

	if (mSelected)
	{
		const float minX = mPosition.X - 1.0f;
		const float minY = mPosition.Y;
		const float minZ = mPosition.Z - 1.0f;
		const float maxX = mPosition.X + 1.0f;
		const float maxY = mPosition.Y;
		const float maxZ = mPosition.Z + 1.0f;
		Graphics::SimpleDraw::AddAABB(minX, minY, minZ, maxX, maxY, maxZ, MathLibrary::Vector4::Green());

		if (HasDestination())
		{
			Graphics::SimpleDraw::AddSphere(mDestination, 0.5f, MathLibrary::Vector4::Magenta(), 6, 2);
		}
	}
}

void Unit::Serialize(Network::StreamWriter& writer)
{
	writer.Write(mPosition.X);
	writer.Write(mPosition.Z);
	writer.Write(mDirection.X);
	writer.Write(mDirection.Z);
}

void Unit::Deserialize(Network::StreamReader& reader)
{
	reader.Read(mPosition.X);
	reader.Read(mPosition.Z);
	reader.Read(mDirection.X);
	reader.Read(mDirection.Z);

	// Make sure destination matches position for now
	mDestination = mPosition;
}

bool Unit::HasDestination() const
{
	const float checkDist = 0.5f;
	return MathLibrary::Vector3::DistanceXZSqr(mPosition, mDestination) > MathLibrary::Sqr(checkDist);
}