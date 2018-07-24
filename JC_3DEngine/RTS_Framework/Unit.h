#ifndef INCLUDED_UNIT_H
#define INCLUDED_UNIT_H

#include <NetworkingLibrary\Inc\Network.h>
#include "RTS.h"

class Unit
{
public:
	Unit();

	void Update(float deltaTime);
	void Draw();

	void Serialize(Network::StreamWriter& writer);
	void Deserialize(Network::StreamReader& reader);

	bool HasDestination() const;

	void SetPosition(const Vector3& position) { mPosition = position; mDestination = position; }
	void SetDirection(const Vector3& direction) { mDirection = direction; }
	void SetDestination(const Vector3& destination) { mDestination = destination; }
	void SetTeam(const int team) { mTeamID = team; }
	int GetTeam() { return mTeamID; }

	void SetSelected(bool selected) { mSelected = selected; }

	const Vector3& GetPosition() const { return mPosition; }
	const Vector3& GetDirection() const { return mDirection; }
	bool IsSelected() const { return mSelected; }
	
private:
	Vector3 mPosition;
	Vector3 mDirection;
	Vector3 mDestination;
	bool mSelected;
	int mTeamID = -1;
};

#endif // #ifndef INCLUDED_UNIT_H