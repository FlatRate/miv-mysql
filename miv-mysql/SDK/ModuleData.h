#pragma once

#include "ScriptEngine.h"

typedef void(*printfunc_t)(const char*, ...);

namespace SDK
{
	class ModuleData
	{
	public:
		virtual void RegisterScriptEngine(ScriptEngine* scriptEngine) = 0;

		// creates an entirely new class in the scripting context.
		// throws an exception if a class by the same name already exists.
		virtual ScriptClass* CreateClass(const char* name, ScriptClass* parent = nullptr) = 0;

		printfunc_t printFunction;
	};
}
