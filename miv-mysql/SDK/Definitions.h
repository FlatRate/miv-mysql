#pragma once

#include <string>

enum eEntityType
{
	CENTITYPLAYER,
	CENTITYVEHICLE,
	CENTITYOBJECT,
	CENTITYPICKUP,
	CENTITYUNKNOWN,
	CENTITYMAX
};

typedef unsigned short NetworkEntityId;
#define INVALID_NETWORK_ENTITY_ID (NetworkEntityId)0xFFFF

enum ePackageFile
{
	PACKAGE_FILE_SCRIPT,
	PACKAGE_FILE_CLIENT_SCRIPT,
	PACKAGE_FILE_CLIENT_ASSET,
	PACKAGE_FILE_COUNT
};

struct SPackageFile
{
	ePackageFile fileType;
	std::string  strPath;

	SPackageFile(ePackageFile _fileType, std::string _strPath)
	{
		fileType = _fileType;
		strPath = _strPath;
	}
};
