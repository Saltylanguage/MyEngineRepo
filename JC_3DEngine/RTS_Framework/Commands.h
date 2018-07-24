#ifndef INCLUDED_COMMANDS_H
#define INCLUDED_COMMANDS_H

#include <NetworkingLibrary\Inc\Network.h>
#include <Math\Inc\EngineMath.h>

using namespace Math;

enum class Command
{
	Spawn,
	Move,
	Attack
};

struct ICommand
{
	virtual void Serialize(Network::StreamWriter& writer) = 0;
	virtual void Deserialize(Network::StreamReader& reader) = 0;
	virtual Command GetType() const = 0;
};

typedef std::vector<ICommand*> CommandList;

class SpawnCommand : public ICommand
{
public:
	void Serialize(Network::StreamWriter& writer) override;
	void Deserialize(Network::StreamReader& reader) override;

	Command GetType() const override { return Command::Spawn; }

	Vector3 position;
	Vector3 direction;
	int teamID = -1;
};

class MoveCommand : public ICommand
{
public:
	void Serialize(Network::StreamWriter& writer) override;
	void Deserialize(Network::StreamReader& reader) override;

	Command GetType() const override { return Command::Move; }

	std::vector<int> networkIds;
	Vector3 position;
};

class AttackCommand : public ICommand
{
public:
	void Serialize(Network::StreamWriter& writer) override;
	void Deserialize(Network::StreamReader& reader) override;

	Command GetType() const override { return Command::Attack; }

	std::vector<int> networkIds;
	int targetId;
};

#endif // #ifndef INCLUDED_COMMANDS_H