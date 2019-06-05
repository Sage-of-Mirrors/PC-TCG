#include "../include/stdafx.h"
#include "../../sa2-mod-loader/SA2ModLoader/include/SA2ModLoader.h"
#include "../include/al_odekakemenu.h"
extern "C"
{

	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{
		//hooks the menu loading function
		WriteJump(AL_OdekakeMenuMaster, AL_OdekakeMenuMaster_);
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}