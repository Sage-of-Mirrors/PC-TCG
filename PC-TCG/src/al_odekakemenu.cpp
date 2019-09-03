#include "../include/stdafx.h"

#include "../include/ninja_functions.h"
#include "../include/al_odekakemenu.h"
#include "../include/alo_odekake_pickup.h"
#include "../include/al_gba_manager.h"
#include "../include/al_msg_warn.h"

//placeholder function, its what SADX's "stub" function is called, this shall be gone one day when i have all the original calls back
bool ObjectSelectedDebug(int a1)
{

	return 1;
}

int sub_72DBF0()
{
	if (AL_OdekakeMenuMaster_Data_ptr)
	{
		return  AL_OdekakeMenuMaster_Data_ptr->field_20;
	}
	return 0;
}
AL_OdekakeMenuMasterData1* __cdecl sub_72DC00()
{
	AL_OdekakeMenuMasterData1* result; // eax

	result = AL_OdekakeMenuMaster_Data_ptr;
	if (AL_OdekakeMenuMaster_Data_ptr)
	{
		AL_OdekakeMenuMaster_Data_ptr->field_20 = 1;
	}
	return result;
}
signed int __cdecl sub_72DC20()
{
	signed int result; // eax

	if (AL_OdekakeMenuMaster_Data_ptr)
	{
		result = AL_OdekakeMenuMaster_Data_ptr->field_1C;
	}
	else
	{
		result = -1;
	}
	return result;
}
void sub_72DC40()
{
	if (AL_OdekakeMenuMaster_Data_ptr)
	{
		AL_OdekakeMenuMaster_Data_ptr->field_1C = 1;
	}
}
FastcallFunctionPointer(void, __fastcall Odekake_SetMenuStatus, (AL_OdekakeMenuMasterData1* a1, int a2), 0x0057E6D0);
FastcallFunctionPointer(void, sub_5A6F50, (AL_OdekakeMenuMasterData1* a1), 0x5A6F50);
ThiscallFunctionPointer(void, sub_5A6C20, (AL_OdekakeMenuMasterData1* a1), 0x5A6C20);
FunctionPointer(void, __cdecl LargeTitleBarExecutor_Load, (char a1, float a2, float a3), 0x005ABD30);
FunctionPointer(void, LoadNextChaoLevel, (int a1), 0x0052B5B0);
FunctionPointer(signed int, sub_57E710, (), 0x57E710);
void Odekake_PickUpMenu(AL_OdekakeMenuMasterData1* a1)
{
	if (AL_OdekakeMenuMaster_Data_ptr)
	{
		switch (AL_OdekakeMenuMaster_Data_ptr->Status)
		{
		case 0:
			LargeTitleBarExecutor_Load(2, 650.0, 66.0);
			LoadOdekakePickUpMenuDraw(1, 320.0, 140.0, 30u);
			LoadOdekakePickUpMenuDraw(2, 320.0, 224.0, 38u);
			LoadOdekakePickUpMenuDraw(3, 320.0, 308.0, 46u);
			Odekake_SetMenuStatus(a1, 1);
			if (!sub_72DC20())
			{
				Odekake_SetMenuStatus(a1, 3);
			}
			break;
		case 1:
			if (!sub_72DC20())
			{
				Odekake_SetMenuStatus(a1, 3);
			}
			break;
		case 2:
		case 6:
			break;
		case 3:
			if (MenuButtons_Pressed[0] & Buttons_Up)
			{
				--a1->verticalSelect;
				//PlaySound(0x8000, 0, 0, 0);
			}
			if (MenuButtons_Pressed[0] & Buttons_Down)
			{
				++a1->verticalSelect;
				//PlaySound(1, 0, 0, 0);
			}
			if (MenuButtons_Pressed[0] & Buttons_Left)
			{
				--a1->horizontalSelect;
				if (a1->verticalSelect == 3)
				{
					a1->horizontalSelect = 3;
				}
				//PlaySound(1, 0, 0, 0);
			}
			if (MenuButtons_Pressed[0] & Buttons_Right)
			{
				++a1->horizontalSelect;
				if (a1->verticalSelect == 3)
				{
					a1->horizontalSelect = 6;
				}
				//PlaySound(1, 0, 0, 0);
			}
			if (a1->verticalSelect < 0)
			{
				a1->verticalSelect = 0;
			}
			if (a1->verticalSelect > 3)
			{
				a1->verticalSelect = 3;
			}
			if (a1->verticalSelect != 3)
			{
				if (a1->horizontalSelect < 0)
				{
					a1->horizontalSelect = 0;
				}
				if (a1->horizontalSelect > 10)
				{
					a1->horizontalSelect = 10;
				}
			}
			if (MenuButtons_Pressed[0] & Buttons_A)
			{
				//exit/pickup button selected
				if (a1->verticalSelect == 3)
				{
					if (a1->horizontalSelect <= 4)
					{
						sub_72DC00();
						Odekake_SetMenuStatus(a1, 15);
						//PlaySound(610, 0, 0, 0);
						return;
					}
					//sub_716C50();                       // had to kill to decomp
					//ObjectSelectedDebug = function that SADX uses for stubbed out functions
					//possibly GBAManager_Reset
					//ObjectSelectedDebug((ObjectMaster*)1);
					//ObjectSelectedDebug((ObjectMaster*)2);
					//ObjectSelectedDebug((ObjectMaster*)3);
					sub_716AD0();
					Odekake_SetMenuStatus(a1, 10);

					//PlaySound(614, 0, 0, 0);
				}
				else
				{
					int v7 = sub_716B00(a1->verticalSelect + 1);
					if (v7)
					{
						v7 = 3;
						if (v7 == 3 && GBAManager_HasItemGBA(a1->verticalSelect + 1, a1->horizontalSelect))
						{
							if (GBAManager_HasItem(a1->verticalSelect + 1, a1->horizontalSelect))
							{
							LABEL_44:
								Odekake_SetMenuStatus(a1, 9);
							}
							else
							{
								switch (a1->horizontalSelect)
								{
								case 0:
									//LOBYTE(v8) = GetLastChaoStage();
									//v9 = GetChaoCount(v8);
									//if (sub_716C00() + v9 >= 8 || (v10 = sub_716C00(), sub_715E00() + v10 >= 24))
									//{
									//	if (!ObjectSelectedDebug((ObjectMaster*)(a2->verticalSelect + 1)))
									//	{
									//		goto LABEL_49;
									//	}
									//}
									goto LABEL_41;
								case 1:
									//LOBYTE(v12) = GetLastChaoStage();
									//v13 = GetChaoCount(v12);
									//if (sub_716C00() + v13 >= 8)
									//{
									//	goto LABEL_49;
									//}
									//v14 = sub_716C00();
									//v15 = sub_715E00() + v14;
									//v17 = __OFSUB__(v15, 24);
									//v16 = v15 - 24 < 0;
									//goto LABEL_48;
								case 3:
								case 4:
								case 5:
								case 6:
								case 7:
								case 8:
								case 9:
								case 0xA:
										//v18 = sub_717540(3);
										//v19 = sub_74C620() + v18;
										//v17 = __OFSUB__(v19, 40);
										//v16 = v19 - 40 < 0;
								//LABEL_48:
								//	if ((unsigned __int8)v16 ^ v17)
								//	{
										goto LABEL_41;
								//	}
								LABEL_49:
									AL_MSGWarnKinderMessage_Init(80.0, 120.0, 480.0, 196.0);
									sub_543800();
									sub_52DC90(26);
									sub_52DC90(27);
									sub_52FB80();
									Odekake_SetMenuStatus(a1, 13);
									return;
								default:
								LABEL_41:
									if (!a1->horizontalSelect)
									{
										Odekake_SetMenuStatus(a1, 4);
										return;
									}
									if (a1->horizontalSelect > 0 && a1->horizontalSelect <= 10)
									{
										goto LABEL_44;
									}
									break;
								}
							}
						}
					}
				}
			}
			else if (MenuButtons_Pressed[0] & Buttons_B)
			{
				if (a1->verticalSelect == 3)
				{
					if (a1->horizontalSelect <= 4)
					{
						sub_72DC00();
						Odekake_SetMenuStatus(a1,15);
						//PlaySound(610, 0, 0, 0);
						return;
					}
				}
				else
				{
					a1->verticalSelect = 3;
				}
				a1->horizontalSelect = 3;
			//	PlaySound(1, 0, 0, 0);
			}
			break;
		case 4:
			//function that sets the item slots
			if (!ObjectSelectedDebug(a1->verticalSelect + 1))
			{
				Odekake_SetMenuStatus(a1, 9);
				break;
			}
			Odekake_SetMenuStatus(a1, 5);
			break;
		case 5:
			AL_MSGWarnKinderMessage_Init(80.0, 60.0, 480.0, 196.0);
			sub_543800();
			sub_52DC90(23);
			sub_543860();
			sub_52DC90(24);
			sub_543860();
			sub_52DC90(25);
			Odekake_SetMenuStatus(a1, 7);
			break;

		case 7:
			//temporary
			if(AL_MSGWarnKinderMessageArray[0].pkindercomessagething14[0].wordsLeftMaybe < 0)
			{
				sub_57EE80(80.0, 300.0, 120.0);
				AL_MSGWarnDataArray[0].field_3 = 1;
				Odekake_SetMenuStatus(a1, 8);
			}
			
			break;
		case 8:
			if (!AL_MSGWarnDataArray[0].field_0)
			{
				if(AL_MSGWarnDataArray[0].field_3)
				{
					sub_5437B0();
					Odekake_SetMenuStatus(a1, 3);
				}
				else
				{
					sub_5437B0();
					Odekake_SetMenuStatus(a1, 9);
				}
				if(AL_MSGWarnDataArray[0].field_4 > 0)
				{
					MessageFontThing* v2 = AL_MSGWarnDataArray[0].field_14;
					for (int i = 0; i < AL_MSGWarnDataArray[0].field_4; i++)
					{
						//TODO: freememory v2 here  IMPORTANT 
						v2++;
					}
				}
				AL_MSGWarnDataArray[0].field_0 = 0;
			}
			break;
		case 9:
			sub_716700(a1->verticalSelect + 1, a1->horizontalSelect);
			Odekake_SetMenuStatus(a1, 3);
			break;
		case 10:
			if (!dword_19F6444)
			{
				Odekake_SetMenuStatus(a1,12);
				return;
			}
			al_confirmsave_load_zero();
			Odekake_SetMenuStatus(a1,11);
			return;
		case 11:
			if (!sub_57E710())
			{
			LABEL_72:
				Odekake_SetMenuStatus(a1,12);
			}
			return;
		case 12:
			a1->field_10++;
			if (a1->field_10 > 90)
			{
				Odekake_SetMenuStatus(a1,18);
			}
			return;
		case 13:
			
			if (AL_MSGWarnKinderMessageArray[0].pkindercomessagething14[0].wordsLeftMaybe < 0)
			{
				sub_5437B0();
				Odekake_SetMenuStatus(a1, 3);
			}
			return;
		case 14:
			a1->field_10++;
			if (a1->field_10 > 60)
			{
				Odekake_SetMenuStatus(a1,15);
			}
			return;
		case 15:
			a1->field_10 ++;
			if (a1->field_10 > 30)
			{
				Odekake_SetMenuStatus(a1, 16);
			}
			return;
		case 16:
			if (!sub_72DC20())
			{
				Odekake_SetMenuStatus(a1, 17);
			}
			return;
		case 17:
			
			AL_OdekakeMenuMaster_Data_ptr->field_8 = 0; //Odekake_SetMenu(0);
			
			sub_57E680(); 
			sub_7165D0();
			break;
		case 18:
			//if (sub_478790(255, 0xFFu, 0xFFu, 0xFFu))
			//{
			LoadNextChaoLevel(LastChaoArea);
			//}
				
			break;
		}
	}
}

void __cdecl AL_OdekakeMenuMaster_(ObjectMaster* a1)
{
	switch (AL_OdekakeMenuMaster_Data_ptr->menuID)
	{
	case 0:
		sub_5A6C20(AL_OdekakeMenuMaster_Data_ptr);
		break;
		//TODO: move goodbye down, have 1 as dropoff, 2 as pickup, like in original, the equivalent of this function in SADX is sub_72DA30
	case 1:
		//sub_5A6F50(AL_OdekakeMenuMaster_Data_ptr);
		//goodbye menu overwritten with pickup proto test
		Odekake_PickUpMenu(AL_OdekakeMenuMaster_Data_ptr);
		break;
	case 2:
		Odekake_PickUpMenu(AL_OdekakeMenuMaster_Data_ptr);
		break;
	}
	AL_OdekakeMenuMaster_Data_ptr->field_1C = 0;
}