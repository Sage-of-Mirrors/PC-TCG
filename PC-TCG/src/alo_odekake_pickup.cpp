#include "../include/stdafx.h"

#include <SA2ModLoader.h>

#include "../include/al_ui.h"
#include "../include/al_gba_manager.h"
#include "../include/ninja_functions.h"
#include "../include/al_odekakemenu.h"
#include "../include/ChaoMain.h"
#include "../include/alo_odekake_pickup.h"

DataPointer(NJS_OBJECT, Egg, 0x125D334);
DataPointer(int, ChunkMatEnable, 0x01AED2CC);
DataPointer(int, ChunkMatFlag, 0x01A27594);
DataPointer(int, ChunkObjectColor, 0x01A275A4);

static const void* someUIProjectionCodePtr = (const void*)0x0055A060;
void someUIProjectionCode(NJS_VECTOR* a1, NJS_VECTOR* a2)
{
	__asm
	{
		mov edi, a1
		mov esi, a2
		call someUIProjectionCodePtr
	}
}
const int ChaoColoringPtr = 0x0056D470;
void ChaoColoring(int texture, int color, int shiny, int highlights, NJS_CNK_MODEL* model)
{
	__asm
	{
		mov edi, texture
		push model
		push highlights
		push shiny
		push color
		call ChaoColoringPtr
		add esp, 16
	}
}

void __cdecl OdekakePickUpMenuDraw(ObjectMaster* a1)
{
	OdekakePickUpMenuData* v1; // edi
	signed int hudIndex; // esi
	float a5; // ST20_4
	ChaoData* v9; // ebp
	bool v10; // eax
	int v11; // esi
	float v14; // ST18_4
	float v15; // ST14_4
	float v19; // eax
	unsigned __int8 v20; // al
	float v22; // ST48_4
	float a6; // [esp+34h] [ebp-20h]
	NJS_VECTOR vs; // [esp+3Ch] [ebp-18h]
	NJS_VECTOR v; // [esp+48h] [ebp-Ch]

	v1 = (OdekakePickUpMenuData*)a1->Data1.Undefined;
	a6 = v1->field_14 * 0.5;
	if (v1->mode)
	{
		if (v1->mode == 4)
		{
			hudIndex = 52;
		}
		else
		{
			if (v1->mode == 8)
			{
				return;
			}
			hudIndex = 57;
		}
		DrawChaoHudThingB(&stru_37C0BA8[hudIndex],     v1->positionX - a6, v1->positionY, -100.0, 1.0, 1.0,     0,  -1, -1);
		DrawChaoHudThingB(&stru_37C0BA8[hudIndex + 1], v1->positionX     , v1->positionY, -100.0, a6 + a6, 1.0, 0,  -1, -1);
		DrawChaoHudThingB(&stru_37C0BA8[hudIndex + 2], v1->positionX + a6, v1->positionY, -100.0, 1.0, 1.0,     0,  -1, -1);
		SetChaoHUDThingBColor(v1->alpha, 1.0, 1.0, 1.0);
		if (v1->alpha >= 1.0)
		{
			v9 = GBAManager_GetChaoDataHeld(v1->byte2);
			for(int i = 0; i < 11; i++)
			{
				v10 = v1->mode != 4;
				v11 = v10 + 61;
				DrawChaoHudThingB(&stru_37C0BA8[v11], i * 48 + v1->positionX - 226.0f, v1->positionY + 36.0f, -100.0, 1.0, 1.0, 0, 0, 0);
			}

			switch (sub_716B00(v1->byte2))
			{
			case 0:
				DrawChaoHudThingB(&stru_37C0BA8[51], v1->positionX - 226.0, v1->positionY + 28.0, -100.0, 1.0, 1.0, 0, 0, 0);
				break;
			case 1:
			case 3:
				DrawChaoHudThingB(&stru_37C0BA8[50], v1->positionX - 220.0, v1->positionY + 34.0, -100.0, 1.0, 1.0, 0, 0, 0);
				break;
			case 2:
				DrawChaoHudThingB(&stru_37C0BA8[50], v1->positionX - 220.0,       v1->positionY + 34.0, -100.0, 1.0, 1.0, 0, 0, 0);
				DrawChaoHudThingB(&stru_37C0BA8[49], v1->positionX - 220.0 - 2.0, v1->positionY + 38.0, -100.0, 1.0, 1.0, 0, 0, 0);
				break;
			default:
				break;
			}
			for(int i = 0; i < 11; i++)			
			{
				vs.y = v1->positionY + 36.0;
				vs.z = -30.0;
				vs.x = (48 * i) + v1->positionX - 226.0;
				someUIProjectionCode(&vs, &v);

				//selected item to pick up from GBA
				if (GBAManager_HasItem(v1->byte2, i))
					DrawChaoHudThingB(&stru_37C0BA8[63], vs.x, vs.y, -100.0, 1.0, 1.0, 0, 0, 0);
				
				if (v1->mode == 4 && AL_OdekakeMenuMaster_Data_ptr->horizontalSelect == i)
					DrawChaoHudThingB(&stru_37C0BA8[60], vs.x, vs.y, -100.0, 1.0, 1.0, 0, 0, 0);
				
				//item is inside GBA
				if (GBAManager_HasItemGBA(v1->byte2, i))
				{
					njPushMatrixEx();
					njTranslate(_nj_current_matrix_ptr_, v.x, v.y, v.z);
					if (i)
					{
						if (i == 1)
						{
							njScale(0.55, 0.55, 0.55);
							njTranslate(_nj_current_matrix_ptr_, 0.0, -3.0, 0.0);
							njSetTexture(&AL_BODY);
							v20 = v9->data.gap_0[1];
							if (v20)
							{
								if (v20 < SADXTexture_Pearl)
								{
									ChaoColoring(v20, 2, 0, 1, Egg.chunkmodel);
								}
							}
							njCnkDrawObject(&Egg);
							ChunkMatFlag = 0;
							ChunkMatEnable = 0;
						}
						else if (i == 2)
						{
							if (v1->ringRotation != 0)
							{
								njRotateY(_nj_current_matrix_ptr_, v1->ringRotation);
							}
							njSetTexture(&AL_OBJECT_TEXLIST);
							//njCnkDrawObject(&SomeRingModel);
						}
						else
						{
							DataArray(NJS_OBJECT*, ChaoFruitModels, 0x13340C8, 35);
							njSetTexture(&AL_OBJECT_TEXLIST);
							njCnkDrawObject(ChaoFruitModels[(v9->data.gap_0[i]) + 13]);
						}
					}
					njPopMatrixEx();
				}
			
			} 
		}
		float sizeX = 0.12;
		if (!v1->field_3)
		{
			sizeX = 0.079999998;
		}
		float sineCalc = njSin(v1->sine) * v1->field_1C * sizeX + 1.0;
		DrawChaoHudThingB(&stru_37C0BA8[35],			 v1->positionX - 284.0, v1->positionY - 16.0, -100.0, sineCalc, 2.0 - sineCalc, 0, -1, -1);
		DrawChaoHudThingB(&stru_37C0BA8[v1->byte2 + 36], v1->positionX - 216.0, v1->positionY - 16.0, -100.0, sineCalc, 2.0 - sineCalc, 0, -1, -1);
		SetChaoHUDThingBColor(1, 1, 1, 1);
	}
}
void __cdecl sub_76BD10(ObjectMaster* a1)
{
	OdekakePickUpMenuData* v1; // esi
	unsigned __int16 v2; // ax
	double v3; // st7
	double v4; // st7
	unsigned __int16 v5; // ax
	int v6; // ecx
	double v7; // st7
	double v8; // st7
	char v9; // cl
	double v11; // st7
	double v12; // st7
	ChaoData* v13; // edi
	ObjectMaster* v14; // eax
	char v15; // al
	unsigned __int8 v17; // of
	NJS_VECTOR vs; // [esp+Ch] [ebp-18h]
	Vector3 a5; // [esp+18h] [ebp-Ch]

	v1 = (OdekakePickUpMenuData*)a1->Data1.Undefined;
	if (AL_OdekakeMenuMaster_Data_ptr)
	{
		switch (v1->mode)
		{
		case 0:
			v2 = v1->field_6;
			v1->field_6 = v2 + 1;
			if ((signed int)v2 > v1->animationTimer)
			{
				v1->mode = 1;
				v1->field_6 = 0;
			}
			break;
		case 1:
			v3 = v1->field_14 + 20.0;
			v1->field_14 = v3;
			if (v3 > 544.0)
			{
				v1->field_14 = 544.0;
				v1->mode = 2;
				v1->field_6 = 0;
			}
			break;
		case 2:
			v4 = v1->alpha + 0.050000001;
			v1->alpha = v4;
			if (v4 > 1.0)
			{
				v1->alpha = 1.0;
				v1->mode = 3;
				v1->field_6 = 0;
			}
			break;
		case 3:
			if ((unsigned __int8)v1->byte2 - 1 == AL_OdekakeMenuMaster_Data_ptr->verticalSelect)
			{
				//dword_3CDC188 = 1;
				v1->mode = 4;
				v1->field_6 = 0;
			}
			break;
		case 4:
			if ((unsigned __int8)v1->byte2 - 1 != AL_OdekakeMenuMaster_Data_ptr->verticalSelect)
			{
				v1->mode = 3;
				v1->field_6 = 0;
			}
			break;
		case 5:
			v5 = v1->field_6;
			v6 = 80 - v1->animationTimer;
			v1->field_6 = v5 + 1;
			if (v5 > v6)
			{
				v1->mode = 6;
				v1->field_6 = 0;
			}
			break;
		case 6:
			v7 = v1->alpha - 0.079999998;
			v1->alpha = v7;
			if (v7 < 0.0)
			{
				if (v1->ChaoObject)
				{
					DeleteObject_(v1->ChaoObject);
					v1->ChaoObject = 0;
				}
				v1->alpha = 0.0;
				v1->mode = 7;
				v1->field_6 = 0;
			}
			break;
		case 7:
			v8 = v1->field_14 - 20.0;
			v1->field_14 = v8;
			if (v8 < 0.0)
			{
				v1->field_14 = 0.0;
				v1->mode = 8;
				v1->field_6 = 0;
			}
			break;
		case 8:
			DeleteObject_(a1);
			break;
		default:
			break;
		}
		v9 = v1->mode;
		v1->sine += 1792;
		if (v1->mode == 4 || v1->field_4)
		{
			v12 = v1->field_1C + 0.050000001;
			v1->field_1C = v12;
			if (v12 > 1.0)
			{
				v1->field_1C = 1.0;
			}
		}
		else
		{
			v11 = v1->field_1C - 0.050000001;
			v1->field_1C = v11;
			if (v11 < 0.0)
			{
				v1->field_1C = 0.0;
			}
		}
		if (v9 >= 2 && v9 < 5)
		{
			v13 = GBAManager_GetChaoDataHeld((unsigned __int8)v1->byte2);
			if (v1->ChaoObject)
			{
				if (v13->data.gap_0[0] == -1)
				{
					DeleteObject_(v1->ChaoObject);
					v1->ChaoObject = 0;
				}
			}
			else if (GBAManager_HasItemGBA((unsigned __int8)v1->byte2, 0))
			{
				if (v13->data.gap_0[0] != -1)
				{
					vs.x = v1->positionX - 228.0;
					vs.z = -30.0;
					vs.y = v1->positionY + 64.0;
					someUIProjectionCode(&vs, &a5);
					v14 = CreateChao(v13, 1, 0, &a5, 0);
					if (v14)
					{
						v14->Data1.Chao->Flags &= 0xFFFFFFF7;
						v14->Data1.Chao->Flags &= 0xFFFFFFFD;
						v14->Data1.Chao->Flags &= 0xFFFFFFEF;
						v1->ChaoObject = v14;
					}
				}
			}
		}
		if (v1->mode < 3 || v1->mode > 4 && v1->mode != 8)
		{
			sub_72DC40();
		}

		v1->ringRotation += 512;

		if (v1->mode < 5)
		{
			if (AL_OdekakeMenuMaster_Data_ptr->field_20)
			{
				v1->mode = 5;
				v1->field_6 = 0;
			}
		}
	}
	else
	{
		DeleteObject_(a1);
	}
}
void __cdecl sub_76C570(ObjectMaster* a1)
{
	OdekakePickUpMenuData* v1; // esi

	v1 = (OdekakePickUpMenuData*)a1->Data1.Undefined;
	if (v1->ChaoObject)
	{
		DeleteObject_(v1->ChaoObject);
		v1->ChaoObject = 0;
	}
}
void __cdecl LoadOdekakePickUpMenuDraw(char a1, float a2, float a3, unsigned __int16 a4)
{
	ObjectMaster* v4; // eax

	//v4 = LoadObject(LoadObj_Data1, 3, sub_76BD10);
	v4 = LoadObject(3, "OdekakePickUpMenuDrawExecutor", sub_76BD10, LoadObj_Data1);
	v4->field_1C = OdekakePickUpMenuDraw;
	v4->DeleteSub = (void(__cdecl*)(ObjectMaster*))sub_76C570;
	OdekakePickUpMenuData*  v5 = (OdekakePickUpMenuData*)v4->Data1.Undefined;
	v5->byte2 = a1;
	v5->animationTimer = a4;
	v5->positionX = a2;
	v5->positionY = a3;
}