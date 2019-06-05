#include "../../sa2-mod-loader/SA2ModLoader/include/SA2ModLoader.h"


struct ChaoHudThingB
{
	int field_0;
	float field_4;
	float field_8;
	float field_C;
	float field_10;
	float field_14;
	float field_18;
	NJS_TEXLIST* texlist;
	Uint32 num;
};


FunctionPointer(void, __cdecl SetChaoHUDThingBColor, (float a1, float a2, float a3, float a4), 0x00559FA0);
void DrawChaoHudThingB(ChaoHudThingB* a1, float a2, float a3, float a4, float a5, float a6, int a7, int a8, int a9);
//#define DrawChaoHudThingB(a1,  a2,  a3,  a4,  a5,  a6,  a7,  a8,  a9) DrawChaoHudThingB_(a1, a2, a3, a4, a5, a6, a8, a9);

extern ChaoHudThingB stru_37C0BA8[67];