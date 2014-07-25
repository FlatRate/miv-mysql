#pragma once

#include "Definitions.h"
#include "ScriptInstance.h"

namespace SDK
{
	class Entity : public virtual ScriptInstance
	{
	public:
		virtual eEntityType     I_GetEntityType() = 0;
		virtual const char*     I_GetEntityTypeString() = 0;

		virtual NetworkEntityId I_GetNetworkId() = 0;
		virtual const char*     I_GetName() = 0;
	};
}
