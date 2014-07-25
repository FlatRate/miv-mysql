#pragma once

#pragma warning(disable:4250) // C4250: 'class1' : inherits 'class2::member' via dominance

#include "ScriptClass.h"
#include "EventHandler.h"

namespace SDK
{
	class ScriptInstance : public virtual SDK::EventHandler
	{
	public:
		virtual ScriptClass* GetClass() = 0;
		virtual bool         IsTypeOf(const char* szType) = 0;
		virtual void         SetUserPointer(void* pUserPointer) = 0;
		virtual void*        GetUserPointer() = 0;
		virtual void*        GetScriptPointer(void* pScriptPointer) = 0;
		virtual void         SetScriptPointer(void* pScriptPointer, void* pPointer) = 0;
		virtual void         RemoveScriptPointer(void* pScriptPointer) = 0;
	};
}
