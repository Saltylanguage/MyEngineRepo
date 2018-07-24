#pragma once
#include <NetworkingLibrary\Inc\Network.h>


enum CommandType
{
	Spawn,
	Move, 
	Attack
};

struct ICommand
{	
	virtual void Serialize(Network::StreamWriter& writer) = 0;
	virtual void Deserialize(Network::StreamReader& reader) = 0;
	virtual CommandType GetType() const = 0;
};

typedef std::vector<ICommand*> CommandList;

struct SpawnCommand : ICommand
{
public:
	SpawnCommand();

	virtual void Serialize(Network::StreamWriter& writer) override;
	virtual void Deserialize(Network::StreamReader& reader) override;

	CommandType GetType() const override { return Spawn; }

	int networkId;
	MathLibrary::Vector3 position;
	MathLibrary::Vector3 direction;
};

struct MoveCommand : public ICommand
{
	virtual void Serialize(Network::StreamWriter& writer) override;
	virtual void Deserialize(Network::StreamReader& reader) override;	

	CommandType GetType() const override { return Move; }

	std::vector<int> networkIds;
	MathLibrary::Vector3 position;
};

struct AttackCommand : ICommand
{
public:
	AttackCommand();

	virtual void Serialize(Network::StreamWriter& writer) override;
	virtual void Deserialize(Network::StreamReader& reader) override;
	
	CommandType GetType() const override { return Attack; }

	std::vector<int> networkIds;
	int targetId;
};