#ifndef INCLUDED_WORLD_H
#define INCLUDED_WORLD_H

#include "RTS.h"
#include "Unit.h"
#include "Input\Inc\Input.h"
#include "NetworkingLibrary\Inc\Network.h"
#include "Commands.h"


class World
{
public:
	static void Initialize();
	static void Terminate();
	static World* Get();

public:
	World();
	~World();

	void Update(float deltaTime);
	void Draw();

	void SpawnUnitRandom();

	void WriteSnapshot(Network::StreamWriter& writer);
	void ApplySnapshot(Network::StreamReader& reader);

	CommandList GetCommands();

	void ProcessCommands(const CommandList& commandList);

private:
	int GetNetworkId(Unit* unit);
	void SelectUnits();
	void CommandUnits();

	Network::LinkingContext mLinkingContext;

	CommandList mCommandList;	

	std::vector<Unit*> mUnits;

	Input::InputSystem* inputSystem = Input::InputSystem::Get();
	
};

#endif // #ifndef INCLUDED_WORLD_H