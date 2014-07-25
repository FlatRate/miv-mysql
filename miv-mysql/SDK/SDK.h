#pragma once

#include "ModuleData.h"
#include "Platform.h"

#define SDK_VERSION 1

EXPORT bool InitializeModule(SDK::ModuleData* data);
EXPORT unsigned int GetSDKVersion();
