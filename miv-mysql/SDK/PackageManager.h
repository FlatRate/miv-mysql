#pragma once

#include "Package.h"

namespace SDK
{
	class PackageManager
	{
	public:
		virtual std::list<SDK::Package*>* I_GetList() = 0;
		virtual unsigned int              I_GetCount() = 0;
		virtual SDK::Package*             I_GetFromName(String strName) = 0;
		virtual SDK::Package*             I_GetFromScriptPointer(void* pScriptPointer) = 0;
		virtual void                      I_Rescan() = 0;
	};
}
