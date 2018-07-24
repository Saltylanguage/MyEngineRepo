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

	MathLibrary::Vector3 minimum(-25.0f, 0.0f, -25.0f);
	MathLibrary::Vector3 maximum(+25.0f, 0.0f, +25.0f);

	MathLibrary::Vector3 position = RandomVector3(minimum, maximum);
	unit->SetPosition(position);

	float x = MathLibrary::RandomFloat(-1.0f, 1.0f);
	float z = MathLibrary::RandomFloat(-1.0f, 1.0f);
	unit->SetDirection(MathLibrary::Vector3::Normalize(MathLibrary::Vector3(x, 0.0f, z)));

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

CommandList World::GetCommands()
{
	return std::move(mCommandList);
}

void World::ProcessCommands(const CommandList & commandList)
{
	for (auto command : commandList)
	{
		switch (command->GetType())
		{
		case CommandType::Spawn:
		{
			SpawnCommand* spawnCommand = static_cast<SpawnCommand*>(command);

			Unit* unit = new Unit();
			mLinkingContext.Register(unit, spawnCommand->networkId);

			unit->SetPosition(spawnCommand->position);
			unit->SetDirection(spawnCommand->direction);
			mUnits.push_back(unit);
			break;
		}
		case CommandType::Move:
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
		case CommandType::Attack:
			//ignore for now
			break;
		}
	}
}

int World::GetNetworkId(Unit * unit)
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
	if (RTS::GetSelectionBox(minX, maxX, minZ, maxZ))
	{
		for (auto unit : mUnits)
		{
			bool selected =
				unit->GetPosition().X > minX &&
				unit->GetPosition().X < maxX &&
				unit->GetPosition().Z > minZ &&
				unit->GetPosition().Z < maxZ;
			unit->SetSelected(selected);
		}
	}
}

void World::CommandUnits()
{
	if (inputSystem->IsKeyPressed(Keys::SPACE))
	{
		SpawnCommand* spawnCommand = new SpawnCommand();
		MathLibrary::Vector3 minVec(-25.0f, 0.0f, -25.0f);
		MathLibrary::Vector3 maxVec(25.0f, 0.0f, 25.0f);

		spawnCommand->position = MathLibrary::RandomVector3(minVec, maxVec);

		float x = MathLibrary::RandomFloat(-1.0f, 1.0f);
		float z = MathLibrary::RandomFloat(-1.0f, 1.0f);

		spawnCommand->direction = MathLibrary::Vector3::Normalize(MathLibrary::Vector3(x, 0.0f, z));
		mCommandList.push_back(spawnCommand);
	}

		MoveCommand* moveCommand = new MoveCommand();
		moveCommand->position - groundPosition;
		Unit* unit = new Unit();

		

		World::Get()->SpawnUnitRandom();
	}
	if (inputSystem->IsMousePressed(Mouse::RBUTTON))
	{
		MathLibrary::Ray ray = inputSystem->GetMouseRay();
		MathLibrary::Vector3 groundPosition = RTS::GetGroundPosition(ray);

		MoveCommand* moveCommand = new MoveCommand();
		moveCommand->position = groundPosition;

		int counter = 0;
		for (auto unit : mUnits)
		{
			if (unit->IsSelected())
			{
				moveCommand->networkIds.push_back(GetNetworkId(unit));
				unit->SetDestination(RTS::GetSpiralPosition(groundPosition, counter++));
			}
		}
		mCommandList.push_back(moveCommand);
	}
}