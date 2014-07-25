#pragma once

#include "Entity.h"

namespace SDK
{
	class EntityManager
	{
	public:
		virtual std::list<SDK::Entity*>* I_GetList(eEntityType entityType) = 0;
		virtual unsigned int             I_GetCount(eEntityType entityType) = 0;
		virtual SDK::Entity*             I_GetFromNetworkId(eEntityType entityType, NetworkEntityId networkId) = 0;
		virtual SDK::Entity*             I_GetFromNetworkId(NetworkEntityId networkId) = 0;
		virtual SDK::Entity*             I_GetFromName(eEntityType entityType, String strName) = 0;
	};
}
