#pragma once

namespace Network
{
	class LinkingContext
	{
	public:

		static const int sInvalidId = -1;

		LinkingContext();

		int GetNetworkId(void* instance) const;
		void* GetInstance(int networkId) const;

		int Register(void* instance);
		void Register(void* instance, int networkId);

		void Unregister(void* instance);

	private:
		std::unordered_map<int, void*> mNetworkIdToInstanceMap;
		std::unordered_map<void*, int> mInstanceToNetworkIdMap;
		int mNextNetworkId;
	};
}