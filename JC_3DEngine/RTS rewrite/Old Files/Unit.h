#ifndef INCLUDED_UNIT_H
#define INCLUDED_UNIT_H

#include "RTS.h"
#include "NetworkingLibrary\Inc\Network.h"

class Unit
{
public:
	Unit();

	void Update(float deltaTime);
	void Draw();

	void Serialize(Network::StreamWriter& writer);
	void Deserialize(Network::StreamReader& reader);

	bool HasDestination() const;

	void SetPosition(const MathLibrary::Vector3& position) { mPosition = position; mDestination = position; }
	void SetDirection(const MathLibrary::Vector3& direction) { mDirection = direction; }
	void SetDestination(const MathLibrary::Vector3& destination) { mDestination = destination; }
	void SetSelected(bool selected) { mSelected = selected; }

	const MathLibrary::Vector3& GetPosition() const { return mPosition; }
	const MathLibrary::Vector3& GetDirection() const { return mDirection; }
	bool IsSelected() const { return mSelected; }
	
private:
	MathLibrary::Vector3 mPosition;
	MathLibrary::Vector3 mDirection;
	MathLibrary::Vector3 mDestination;
	bool mSelected;
};

#endif // #ifndef INCLUDED_UNIT_H