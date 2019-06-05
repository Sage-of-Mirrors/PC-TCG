#pragma once
#include "../include/stdafx.h"
#include "../../sa2-mod-loader/SA2ModLoader/include/SA2ModLoader.h"

FastcallFunctionPointer(double, njCos, (signed int a1), 0x042AC30);
FastcallFunctionPointer(double, njSin, (signed int a1), 0x0042AAB0);
FunctionPointer(int, __cdecl njCnkDrawModel, (NJS_CNK_MODEL* a1), 0x0056E1E0);
FunctionPointer(signed int, njPushMatrixEx, (), 0x00429710);
FunctionPointer(signed int, njPopMatrixEx, (), 0x00429000);
FunctionPointer(void, __cdecl sub_42E730, (NJS_OBJECT* a1), 0x42E730);
DataPointer(NJS_MATRIX, flt_25F02A0, 0x25F02A0);
DataPointer(NJS_ARGB, _nj_constant_material_, 0x025EFFD0);
DataPointer(int, njControl3D, 0x025F02D8);
DataPointer(int, njControl3DBackup, 0x01DEB6A4);
void  njCalcVector(NJS_VECTOR* a1, NJS_VECTOR* a2, NJS_MATRIX_PTR a3);
void  njSetTexture(NJS_TEXLIST* texlist);

const int njTranslateVPtr = 0x00428A30;
void  njTranslateV(NJS_VECTOR* a1);

const int njCnkDrawObjectPtr = 0x0056E210;
void njCnkDrawObject(NJS_OBJECT* a1);

void DrawCnkModel2(NJS_CNK_MODEL* a1);


void njSetTextureNum(int a1, int a2, int a3, int a4);
const int njScalePtr = 0x007802B0;
void njScale_(NJS_MATRIX_PTR a1, float a2, float a3, float a4);