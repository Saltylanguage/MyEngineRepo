#include "World.h"

namespace
{
	World* singleton = nullptr;
}

void World::Initialize()
{
	ASSERT(singleton == nullptr, "[World] Singleton already exists!");
	singleton = new World();
	
}

void World::Terminate()
{
	SafeDelete(singleton);
}

World* World::Get()
{
	ASSERT(singleton != nullptr, "[World] Singleton not initialized!");
	return singleton;
}

World::World()
{
}

World::~World()
{
	for (auto unit : mUnits)
	{
		SafeDelete(unit);
	}
	mUnits.clear();
}

void World::Update(float deltaTime)
{
	SelectUnits();
	CommandUnits();

	for (auto unit : mUnits)
	{
		unit->Update(deltaTime);
	}
}

void World::Draw()
{
	for (auto unit : mUnits)
	{
		unit->Draw();
	}
}

void World::SpawnUnitRandom()
{
	Unit* unit = new Unit();

	Vector3 minVec(-25.0f, 0.0f, -25.0f);
	Vector3 maxVec(+25.0f, 0.0f, +25.0f);
	Vector3 position = RandomVector3(minVec, maxVec);
	unit->SetPosition(position);

	float x = RandomFloat(-1.0f, 1.0f);
	float z = RandomFloat(-1.0f, 1.0f);
	unit->SetDirection(Vector3::Normalize(Vector3(x, 0.0f, z)));

	mUnits.push_back(unit);
}

void World::WriteSnapshot(Network::StreamWriter& writer)
{
	for (auto unit : mUnits)
	{
		// Write network id
		writer.Write(GetNetworkId(unit));

		// Write unit data
		unit->Serialize(writer);
	}
}

void World::ApplySnapshot(Network::StreamReader& reader)
{
	std::vector<Unit*> replicatedUnits;

	while (reader.GetRemainingDataSize() > 0)
	{
		int networkId = Network::LinkingContext::sInvalidId;
		reader.Read(networkId);
		
		Unit* unit = (Unit*)mLinkingContext.GetInstance(networkId);
		if (unit == nullptr)
		{
			unit = new Unit();
			mLinkingContext.Register(unit, networkId);
		}

		unit->Deserialize(reader);
		replicatedUnits.push_back(unit);
	}

	for (auto unit : mUnits)
	{
		auto it = std::find(replicatedUnits.begin(), replicatedUnits.end(), unit);
		if (it == replicatedUnits.end())
		{
			mLinkingContext.Unregister(unit);
			SafeDelete(unit);
		}
	}

	mUnits = replicatedUnits;
}

void World::ProcessCommands(const CommandList& commandList)
{
	for (auto command : commandList)
	{
		switch (command->GetType())
		{
			case Command::Spawn:
			{
				SpawnCommand* spawnCommand = static_cast<SpawnCommand*>(command);

				Unit* unit = new Unit();
				mLinkingContext.Register(unit);
	
				unit->SetTeam(spawnCommand->teamID);
				unit->SetPosition(spawnCommand->position);
				unit->SetDirection(spawnCommand->direction);
				mUnits.push_back(unit);

				break;
			}
			case Command::Move:
			{
				MoveCommand* moveCommand = static_cast<MoveCommand*>(command);

				int counter = 0;
				for (auto id : moveCommand->networkIds)
				{
					Unit* unit = (Unit*)mLinkingContext.GetInstance(id);
					if (unit != nullptr)
					{
						unit->SetDestination(RTS::GetSpiralPosition(moveCommand->position, counter++));
					}
				}
				break;
			}
			case Command::Attack:
			{
				// Unexpected, ignore for now
				break;
			}
		}
	}
}

CommandList World::GetCommands()
{
	return std::move(mCommandList);
}

int World::GetNetworkId(Unit* unit)
{
	int networkId = mLinkingContext.GetNetworkId(unit);
	if (networkId == Network::LinkingContext::sInvalidId)
	{
		networkId = mLinkingContext.Register(unit);
	}
	return networkId;
}

void World::SelectUnits()
{
	float minX, maxX, minZ, maxZ;
	if (RTS::GetSelectionBox(minX, maxX, minZ, maxZ, mCamera))
	{
		for (auto unit : mUnits)
		{
			if (unit->GetTeam() == mTeam)
			{
			bool selected =
				unit->GetPosition().x > minX &&
				unit->GetPosition().x < maxX &&
				unit->GetPosition().z > minZ &&
				unit->GetPosition().z < maxZ;
			unit->SetSelected(selected);
			}
		}
	}
}

void World::CommandUnits()
{
	if (Input::InputSystem::Get()->IsKeyPressed(Keys::SPACE))
	{
		SpawnCommand* spawnCommand = new SpawnCommand();

		Vector3 minVec(-25.0f, 0.0f, -25.0f);
		Vector3 maxVec(+25.0f, 0.0f, +25.0f);	
		spawnCommand->position = RandomVector3(minVec, maxVec);

		float x = RandomFloat(-1.0f, 1.0f);
		float z = RandomFloat(-1.0f, 1.0f);
		spawnCommand->direction = Vector3::Normalize(Vector3(x, 0.0f, z));
		spawnCommand->teamID = mTeam;
		mCommandList.push_back(spawnCommand);
	}
	if (Input::InputSystem::Get()->IsMousePressed(Mouse::RBUTTON))
	{
		Ray ray = Input::InputSystem::Get()->GetMouseRay(mCamera);
		Vector3 groundPosition = RTS::GetGroundPosition(ray);

		MoveCommand* moveCommand = new MoveCommand();
		moveCommand->position = groundPosition; //TODO error here



		for (auto unit : mUnits)
		{
			if (unit->IsSelected())
			{
				moveCommand->networkIds.push_back(GetNetworkId(unit));
			}
		}

		mCommandList.push_back(moveCommand);
	}
}