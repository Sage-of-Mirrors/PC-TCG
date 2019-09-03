#include "../include/stdafx.h"

#include <math.h>

#include "../include/ninja_functions.h"

void  njCalcVector(NJS_VECTOR* a1, NJS_VECTOR* a2, NJS_MATRIX_PTR a3)
{
	Float v3; // ST00_4
	Float v4; // ST04_4

	v3 = a3[M10] * a1->x + a3[M11] * a1->y + a3[M12] * a1->z;
	v4 = a3[M20] * a1->x + a3[M21] * a1->y + a3[M22] * a1->z;
	a2->x = a3[M01] * a1->y + *a3 * a1->x + a3[M02] * a1->z;
	a2->y = v3;
	a2->z = v4;
}
struct NJS_CTX
{

	int gap0;
	int field_4;
	int field_8;
	float field_C;
	int field_10;
	int field_14;
	int field_18;
	int field_1C;
	NJS_TEXLIST* texlistPtr;
};
void njSetTexture(NJS_TEXLIST* texlist)
{
	NJS_CTX* ctx = (NJS_CTX*)Has_texlist_batadvPlayerChara_in_it;
	ctx->texlistPtr = texlist; //Has_texlist_ = NJS_CTX from billy hatcher, edit later.
}


void  njTranslateV(NJS_VECTOR* a1)
{
	__asm
	{
		mov eax, a1
		call njTranslateVPtr
	}
}

void njCnkDrawObject(NJS_OBJECT* a1)
{
	__asm
	{
		mov esi, a1
		call njCnkDrawObjectPtr
	}
}

const int DrawCnkModel2Ptr = 0x0042E6C0;
void DrawCnkModel2(NJS_CNK_MODEL* a1)
{
	__asm
	{
		mov eax, a1
		call DrawCnkModel2Ptr
	}
}
const int njSetTextureNumPtr = 0x0042D6D0;
void njSetTextureNum(int a1, int a2, int a3, int a4)
{
	__asm
	{
		mov eax, a1
		mov ecx, a2
		mov ebx, a3
		push a4
		call njSetTextureNumPtr
		add esp, 4
	}
}

void njScale_(NJS_MATRIX_PTR a1, float a2, float a3, float a4)
{
	__asm
	{
		push a4
		push a3
		push a2
		mov eax, a1
		call njScalePtr
		add esp, 12
	}
}
