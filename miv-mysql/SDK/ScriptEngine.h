#pragma once

#include "ScriptClass.h"
#include "ScriptInstance.h"
#include "Package.h"

namespace SDK
{
	class ScriptEngine
	{
	public:
		virtual const char* GetName() = 0;

		virtual void LoadPackage(SDK::Package* package) = 0;
		virtual void UnloadPackage(SDK::Package* package) = 0;

		virtual SDK::ScriptArgument* ExecuteCallback(SDK::Package* package, void* data, SDK::ScriptArguments& arguments) = 0;
		virtual void DefineFunction(SDK::Package* package, ScriptFunction* pFunction) = 0;
		virtual void DefineClass(SDK::Package* package, SDK::ScriptClass* classDefinition) = 0;

		virtual SDK::ScriptArgument* ExecuteString(SDK::Package* package, const char* string) = 0;
		virtual SDK::ScriptArgument* ExecuteFile(SDK::Package* package, const char* filename) = 0;

		virtual void CreateInstance(SDK::Package* package, SDK::ScriptInstance* instance, bool bConstruct = false) = 0;
		virtual void DestroyInstance(SDK::Package* package, SDK::ScriptInstance* instance) = 0;

	};
}
