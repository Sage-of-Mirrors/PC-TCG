#include "../include/stdafx.h"
#include "../../sa2-mod-loader/SA2ModLoader/include/SA2ModLoader.h"

int sub_716B00(int a1)
{
	if (AL_GBAManagerExecutor_ptr)
	{
		return AL_GBAManagerExecutor_ptr->field_18[a1].field_8;
	}
	return 0;
}
void sub_716AD0()
{
	if (AL_GBAManagerExecutor_ptr)
	{
		AL_GBAManagerExecutor_ptr->dword0 = 0;
	}
}
int GBAManager_HasItem(int a1, int a2)
{
	if (AL_GBAManagerExecutor_ptr)
	{
		return AL_GBAManagerExecutor_ptr->field_18[a1].hasItem[a2];
	}
	return 0;
}
int GBAManager_HasItemGBA(int a1, int a2)
{
	if (AL_GBAManagerExecutor_ptr)
	{
		return AL_GBAManagerExecutor_ptr->field_18[a1].hasItem___[a2];
	}
	return 0;
}
ChaoData* GBAManager_GetChaoDataHeld(int a1)
{
	if (AL_GBAManagerExecutor_ptr)
	{
		return &AL_GBAManagerExecutor_ptr->field_18[a1].chaoData1;
	}
	return 0;
}
void  sub_7165D0()
{
	if (AL_GBAManagerExecutor_ptr)
	{
		for(int i = 0; i < 4; i++)
		{
			memset(AL_GBAManagerExecutor_ptr->field_18[i].hasItem, 0, 0x2C);
		}
	}
}
void sub_716700(int a1, int a2)
{
	if (AL_GBAManagerExecutor_ptr)
	{
		if (GBAManager_HasItemGBA(a1, a2))
		{
			if (GBAManager_HasItem(a1, a2))
			{
				AL_GBAManagerExecutor_ptr->field_18[a1].hasItem[a2] = 0;
			}
			else
			{
				AL_GBAManagerExecutor_ptr->field_18[a1].hasItem[a2] = 1;
			}
		}
	}
}