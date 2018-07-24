#include "Commands.h"

void MoveCommand::Serialize(Network::StreamWriter& writer)
{

	writer.Write(networkIds.size());
	for (auto id : networkIds)
	{
		writer.Write(id);
	}
	writer.Write(position.X);
	writer.Write(position.Y);
	writer.Write(position.Z);
}

void MoveCommand::Deserialize(Network::StreamReader& reader)
{
	size_t count = 0;
	reader.Read(count);

	networkIds.resize(count);

	for (auto& id : networkIds)
	{
		reader.Read(id);
	}

	reader.Read(position.X);
	reader.Read(position.Y);
	reader.Read(position.Z);
}

void AttackCommand::Serialize(Network::StreamWriter& writer)
{
	writer.Write(networkIds.size());
	for (auto id : networkIds)
	{
		writer.Write(id);
	}
	writer.Write(targetId);
}

void AttackCommand::Deserialize(Network::StreamReader& reader)
{
	size_t count = 0;
	reader.Read(count);

	networkIds.resize(count);

	for (auto& id : networkIds)
	{
		reader.Read(id);
	}
	reader.Read(targetId);
}

void SpawnCommand::Serialize(Network::StreamWriter & writer)
{
	

	writer.Write(position.X);
	writer.Write(position.Y);
	writer.Write(position.X);

	writer.Write(direction.X);
	writer.Write(direction.Y);
	writer.Write(direction.Z);
}

void SpawnCommand::Deserialize(Network::StreamReader & reader)
{

	reader.Read(position.X);
	reader.Read(position.Y);
	reader.Read(position.Z);

	reader.Read(direction.X);
	reader.Read(direction.Y);
	reader.Read(direction.Z);
}
