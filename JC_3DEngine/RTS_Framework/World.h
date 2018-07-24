#pragma once
#include "Commands.h"
#include "Unit.h"

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

	void ProcessCommands(const CommandList& commandList);
	
	CommandList GetCommands();
	Graphics::Camera& GetCamera() { return mCamera; }

	void SetTeam(int team) { mTeam = team; }


private:
	int GetNetworkId(Unit* unit);
	void SelectUnits();
	void CommandUnits();

	Network::LinkingContext mLinkingContext;
	CommandList mCommandList;

	std::vector<Unit*> mUnits;

	Graphics::Camera mCamera;

	int mTeam = -1;
};
