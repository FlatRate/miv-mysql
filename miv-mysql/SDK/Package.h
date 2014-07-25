#pragma once

#include <list>
#include <string>
#include "Definitions.h"
#include "ScriptInstance.h"

namespace SDK
{
	class Package : public virtual ScriptInstance
	{
	public:
		virtual const std::string&        I_GetName() = 0;
		virtual const std::string&        I_GetPath() = 0;
		virtual const std::string&        I_GetLanguage() = 0;
		virtual std::list<SPackageFile*>* I_GetFileList() = 0;
		virtual void                      I_SetScriptPointer(void* pScriptPointer) = 0;
		virtual void*                     I_GetScriptPointer() = 0;
		virtual bool                      I_Start() = 0;
		virtual bool                      I_Stop() = 0;
		virtual bool                      I_Restart() = 0;
		virtual unsigned int              I_GetState() = 0;

	};
}
