#define PICKUP_MENU_INIT 0
#define PICKUP_MENU_WAIT_FOR_INIT 1
#define PICKUP_MENU_MAIN 3
//...
#define PICKUP_MENU_PICKUP_CHAO_WARNING 5
#define PICKUP_MENU_PLAYER_CHOICE_YESNO 7
#define PICKUP_MENU_CHECK_PLAYER_CHOICE 8
#define PICKUP_MENU_SELECT_ITEM_FOR_PICKUP 9
#define PICKUP_MENU_SAVE_DATA 10
#define PICKUP_MENU_WAIT_FOR_MENU_EXIT 12
#define PICKUP_MENU_WAIT_FOR_TEXT_DRAW 13
#define PICKUP_MENU_WAIT_FOR_BACKTRACK_60 14
#define PICKUP_MENU_WAIT_FOR_BACKTRACK_30 15
//...
#define PICKUP_MENU_BACKTRACK 17
#define PICKUP_MENU_EXIT 18

#define MAX_NUM_ROWS 3
#define MAX_NUM_COLS 11

#define SLOT_CHAO 0
#define SLOT_EGG  1
#define SLOT_RINGS 2
#define SLOT_ITEM_A 3
#define SLOT_ITEM_B 4
#define SLOT_ITEM_C 5
#define SLOT_ITEM_D 6
#define SLOT_ITEM_E 7
#define SLOT_ITEM_F 8
#define SLOT_ITEM_G 9
#define SLOT_ITEM_H 10

#include "../include/ninja_functions.h"
#include "../include/al_odekakemenu.h"
#include "../include/alo_odekake_pickup.h"
#include "../include/al_gba_manager.h"
#include "../include/al_msg_warn.h"

FastcallFunctionPointer(void, __fastcall Odekake_SetMenuStatus, (AL_OdekakeMenuMasterData1* a1, int a2), 0x0057E6D0);
FastcallFunctionPointer(void, sub_5A6F50, (AL_OdekakeMenuMasterData1* a1), 0x5A6F50);
ThiscallFunctionPointer(void, sub_5A6C20, (AL_OdekakeMenuMasterData1* a1), 0x5A6C20);
FunctionPointer(void, __cdecl LargeTitleBarExecutor_Load, (char a1, float a2, float a3), 0x005ABD30);
FunctionPointer(void, LoadNextChaoLevel, (int a1), 0x0052B5B0);
FunctionPointer(signed int, sub_57E710, (), 0x57E710);

/* Kicks off initialization of the UI. */
void Odekake_PickUpMenu_Init(AL_OdekakeMenuMasterData1* menu_data)
{
	LargeTitleBarExecutor_Load(2, 650.0, 66.0);
	
	LoadOdekakePickUpMenuDraw(1, 320.0, 140.0, 30u);
	LoadOdekakePickUpMenuDraw(2, 320.0, 224.0, 38u);
	LoadOdekakePickUpMenuDraw(3, 320.0, 308.0, 46u);
	
	Odekake_SetMenuStatus(menu_data, PICKUP_MENU_WAIT_FOR_INIT);
	Odekake_PickUpMenu_Wait_For_Init(menu_data);
}

/* Waits for the UI to finish initializing before moving to the main loop. */
void Odekake_PickUpMenu_Wait_For_Init(AL_OdekakeMenuMasterData1* menu_data)
{
	if (!AL_OdekakeMenuMaster_Data_ptr->field_1C)
	{
		Odekake_SetMenuStatus(menu_data, PICKUP_MENU_MAIN);
	}
}

/* Kicks off a return to the main Chao Transporter menu. */
void Odekake_PickupMenu_BeginBacktrack(AL_OdekakeMenuMasterData1* menu_data)
{
	menu_data->field_20 = 1;
	Odekake_SetMenuStatus(menu_data, PICKUP_MENU_WAIT_FOR_BACKTRACK_30);
	//PlaySound(610, 0, 0, 0);
}

/* Triggers the currently selected items to be transferred from the GBA to the garden. */
void Odekake_PickUpMenu_BeginPickup(AL_OdekakeMenuMasterData1* menu_data)
{
	// sub_716C50();
	// ObjectSelectedDebug((ObjectMaster *)1);
	// ObjectSelectedDebug((ObjectMaster *)2);
	// ObjectSelectedDebug((ObjectMaster *)3);
	AL_GBAManagerExecutor_ptr->dword0 = 0;
	Odekake_SetMenuStatus(menu_data, PICKUP_MENU_SAVE_DATA);
}

int sub_717540(int a1)
{
	int result = 0;
	static char * chao_save_address = GetChaoSavePointer();
	
	if (a1 == 3)
	{
		char * chao_field_a8 = chao_save_address + 0xA8;
		
		for (int i = 4; i > 0; i--)
		{
			if (*(chao_field_a8 - 10) != -1)
			{
				result++;
			}
			
			if (*chao_field_a8 != -1)
			{
				result++;
			}
			
			chao_field_a8 += 100;
		}
	}
	if (a1 != 9)
	{
		return result;
	}
}

int sub_74C620()
{
	int result = 0;
	
	for (int i = 1; i < 4; i++)
	{
		for (int j = 3; j < 11; j++)
		{
			result += (GBAManager_HasItem(i, j) != 0);
		}
	}
	
	return result;
}

/* TODO: Performs a check on whether the garden the player came from has an open Chao slot. */
bool Odekake_PickUpMenu_Garden_Chao_Slot_Available()
{
	return false;
}

/* TODO: Performs a check on whether there is an open slot in the 24 slots */
/* reserved for Chao in the Chao Garden save file. */
bool Odekake_PickUpMenu_Chao_Save_Slot_Available()
{
	return false;
}

/* TODO: Performs a check on whether there is an open item slot in the garden */
/* the player came from. */
bool Odekake_PickUpMenu_Garden_Item_Slot_Available()
{
	return false;
}

/* Displays an error message to the player stating that Chao or eggs*/
/* cannot be picked up from TCG because the garden is full. */
void Odekake_PickUpMenu_Garden_Full_Error_Message(AL_OdekakeMenuMasterData1* menu_data)
{
	AL_MSGWarnKinderMessage_Init(80.0, 120.0, 480.0, 196.0);
    /*
    sub_72D880(0);
    v20 = AL_MSGWarn_GetMessage(26); // "Your garden is full."
    sub_72D8D0(0, (int)v20);
    v21 = AL_MSGWarn_GetMessage(27); // "Unable to pick up anything."
    sub_72D8D0(0, (int)v21);
    sub_72D930(0);
    */
	Odekake_SetMenuStatus(menu_data, PICKUP_MENU_WAIT_FOR_TEXT_DRAW);
}

/* Switches the menu state for selecting items based on the currently selected slot. */
void Odekake_Pickup_Menu_Prepare_Item_Select(AL_OdekakeMenuMasterData1* menu_data)
{
	if (menu_data->horizontalSelect == SLOT_CHAO)
	{
		Odekake_SetMenuStatus(menu_data, 4);
		return;
	}
	else if (menu_data->horizontalSelect > 0 && menu_data->horizontalSelect <= 10)
	{
		Odekake_SetMenuStatus(menu_data, PICKUP_MENU_SELECT_ITEM_FOR_PICKUP);
	}
}

/* Main loop of the pickup menu. */
void Odekake_PickupMenu_Main(AL_OdekakeMenuMasterData1* menu_data)
{
	int row_offset = 0, col_offset = 0;
	
	// Get an offset value to move the cursor up or down the menu rows
	if (MenuButtons_Pressed[0] & Buttons_Up)
	{
		row_offset = -1;
	}
	else if (MenuButtons_Pressed[0] & Buttons_Down)
	{
		row_offset = 1;
	}
	
	// Get an offset value to move left or right in the menu columns
	if (MenuButtons_Pressed[0] & Buttons_Left)
	{
		col_offset = -1;
	}
	else if (MenuButtons_Pressed[0] & Buttons_Right)
	{
		col_offset = 1;
	}
	
	// Calculate the new selected row index. Allows selection to wrap - moving up from 0 moves to 3, and vice versa
	menu_data->verticalSelect = (menu_data->verticalSelect + row_offset) % MAX_NUM_ROWS;
	
	// The 4th row contains two buttons, "Back" and "Pick up." They're at columns 3 and 6, so we'll restrict selection
	// to one or the other if the 4th row is selected.
	if (menu_data->verticalSelect == 3)
	{
		if (col_offset = -1)
		{
			menu_data->horizontalSelect = 3;
		}
		else if (col_offset = 1)
		{
			menu_data->horizontalSelect = 6;
		}
	}
	else
	{
		// Calculate the new selected column index. Allows selection to wrap - moving left from 0 moves to 10, and vice versa
		menu_data->horizontalSelect = (menu_data->horizontalSelect + col_offset) % MAX_NUM_COLS;
	}
	
	// If we moved, play a sound
	if (row_offset != 0 || col_offset != 0)
	{
		//PlaySound(0x8000, 0, 0, 0);
	}
	
	// The player wants to cancel!
	if (MenuButtons_Pressed[0] & Buttons_B)
	{
		// We're already at the Back button (row 4, column 3), so pressing B will just initiate an exit
		if (menu_data->verticalSelect == 3 && menu_data->horizontalSelect == 3)
		{
			Odekake_PickupMenu_BeginBacktrack(menu_data);
		}
		// We're not at the Back button yet, so place the cursor at it.
		else
		{
			menu_data->verticalSelect = 3;
			menu_data->horizontalSelect = 3;
		}
		
		//PlaySound(1, 0, 0, 0);
	}
	
	// The player selected something!
	else if (MenuButtons_Pressed[0] & Buttons_A)
	{
		if (menu_data->verticalSelect == 3)
		{
			// We're at the Back button, so pressing A initiates a menu exit.
			if (menu_data->horizontalSelect == 3)
			{
				Odekake_PickupMenu_BeginBacktrack(menu_data);
				return;	
			}
			// We're at the Pick up button, so pressing A will transfer all our selected items to the GC game.
			else if (menu_data->horizontalSelect == 6)
			{
				Odekake_PickUpMenu_BeginPickup(menu_data);
				return;
			}
		}
		
		// This probably ensures that there's a GBA actively connected.
		if (int gba_value_8 = AL_GBAManagerExecutor_ptr->field_18[menu_data->verticalSelect + 1].field_8)
		{
			// Check if there's an item in this slot on the GBA side.
			if (gba_value_8 == 3 && GBAManager_HasItemGBA(menu_data->verticalSelect + 1, menu_data->horizontalSelect))
			{
				// If the player has already selected the slot before, we will toggle the selection, removing it.
				if (GBAManager_HasItem(menu_data->verticalSelect + 1, menu_data->horizontalSelect))
				{
					Odekake_SetMenuStatus(menu_data, PICKUP_MENU_SELECT_ITEM_FOR_PICKUP);
				}
				// The player has not previously selected this slot (or has already deselected it),
				// so we'll go into selection logic.
				else
				{
					switch (menu_data->horizontalSelect)
					{
						case SLOT_CHAO:
							// The SADX code checks the save file here to make sure that there are less than 24
							// Chao in the save file. Is there a hard limit on the amount of Chao the save file
							// can have?
							if (!Odekake_PickUpMenu_Garden_Chao_Slot_Available() || !Odekake_PickUpMenu_Chao_Save_Slot_Available())
							{
								// The if statement here is stubbed out, need to figure out what it was.
								// Probably a GBA call? To make sure the GBA is still connected?
								if (true)
								{
									Odekake_PickUpMenu_Garden_Full_Error_Message(menu_data);
								}
							}
							break;
						case SLOT_EGG:
							// Same checks as above, essentially? Eggs are just Chao with a type of 0...
							if (!Odekake_PickUpMenu_Garden_Chao_Slot_Available() || Odekake_PickUpMenu_Chao_Save_Slot_Available())
							{
								Odekake_PickUpMenu_Garden_Full_Error_Message(menu_data);
								return;
							}
							break;
						case SLOT_RINGS:
							// Rings don't need any special checks; skip to selection.
							break;
						case SLOT_ITEM_A:
						case SLOT_ITEM_B:
						case SLOT_ITEM_C:
						case SLOT_ITEM_D:
						case SLOT_ITEM_E:
						case SLOT_ITEM_F:
						case SLOT_ITEM_G:
						case SLOT_ITEM_H:
							if (!Odekake_PickUpMenu_Garden_Item_Slot_Available())
							{
								Odekake_PickUpMenu_Garden_Full_Error_Message(menu_data);
								return;
							}
							break;
						default:
							PrintDebug("Bad Pickup Menu horizontal selection %i!", menu_data->horizontalSelect);
							return;
					}

					// We did all our safety checks above, now we can actually process the selection.
					Odekake_Pickup_Menu_Prepare_Item_Select(menu_data);
				}
			}
		}
		// There appears to be no GBA connected! Or maybe the Chao data hasn't been loaded...?
		else
		{
			AL_MSGWarnKinderMessage_Init(80.0, 120.0, 480.0, 196.0);
			// Warning messages go here, DX indices 12 and 13. They appear to be
			// "Loading Chao Data." and "Do not disconnect the GBA cable."
			Odekake_SetMenuStatus(menu_data, PICKUP_MENU_WAIT_FOR_TEXT_DRAW);
		}
	}
}

/* Increments a timer in the menu's struct and returns true if that timer reaches the value of max_time. */
/* Used by states PICKUP_MENU_WAIT_FOR_MENU_EXIT, PICKUP_MENU_WAIT_FOR_BACKTRACK_60, and PICKUP_MENU_WAIT_FOR_BACKTRACK_30. */
bool Odekake_PickUpMenu_Increment_Timer(AL_OdekakeMenuMasterData1* menu_data, int max_time)
{
	menu_data->field_10++;
	
	if (menu_data->field_10 > max_time)
	{
		return true;
	}
	
	return false;
}

/* Toggles the selection of a Chao, an egg, or an item that can be picked up from the TCG. */
void Odekake_PickUpMenu_Select_Item_For_Pickup(AL_OdekakeMenuMasterData1* menu_data, int row, int column)
{
	if (AL_GBAManagerExecutor_ptr)
	{
		if (GBAManager_HasItemGBA(row, column))
		{
			int item_location = column + 1057 * row;
			
			if (GBAManager_HasItem(row, column))
			{
				AL_GBAManagerExecutor_ptr->field_18[0].hasItem[item_location] = 0;
			}
			else
			{
				AL_GBAManagerExecutor_ptr->field_18[0].hasItem[item_location] = 1;
			}
		}
	}
	
	Odekake_SetMenuStatus(menu_data, PICKUP_MENU_MAIN);
}

/* Determines if the player said Yes or No to the TCG Chao pickup warning and responds accordingly. */
void Odekake_PickUpMenu_Check_Player_Choice(AL_OdekakeMenuMasterData1* menu_data)
{
	if (!AL_MSGWarnDataArray[0].field_0)
	{
		// Player said no
		if (true)
		{
			Odekake_SetMenuStatus(menu_data, PICKUP_MENU_MAIN);
		}
		// Player said yes
		else
		{
			Odekake_SetMenuStatus(menu_data, PICKUP_MENU_SELECT_ITEM_FOR_PICKUP);
		}

		//sub_72D820(0); // Message cleanup

		int v1 = 0;

		if (AL_MSGWarnDataArray[0].field_4 > 0)
		{
			int v2 = 0; //AL_MSGWarnDataArray[0].field_14;
			for (int i = 0; i < AL_MSGWarnDataArray[0].field_4; i++)
			{
				//sub_724A90(v2); // something about heapfree
				v2++;
			}
		}

		AL_MSGWarnDataArray[0].field_0 = 0;
	}
}

/* Displays a warning message to the player describing how picking up a Chao from TCG works. */
void Odekake_PickUpMenu_PickUp_Chao_Warning(AL_OdekakeMenuMasterData1* menu_data)
{
	AL_MSGWarnKinderMessage_Init(80.0, 60.0, 480.0, 196.0);
	Odekake_SetMenuStatus(menu_data, PICKUP_MENU_PLAYER_CHOICE_YESNO);
}

/* Waits for 90 frames (?) before triggering an exit from the Chao Transporter back to the garden. */
void Odekake_PickUpMenu_Wait_For_Menu_Exit(AL_OdekakeMenuMasterData1* menu_data)
{
	if (Odekake_PickUpMenu_Increment_Timer(menu_data, 90))
	{
		Odekake_SetMenuStatus(menu_data, PICKUP_MENU_EXIT);
	}
}

/* Waits for 60 frames (?) before triggering a return to the main Chao Transporter menu. */
void Odekake_PickUpMenu_Wait_For_Backtrack_60(AL_OdekakeMenuMasterData1* menu_data)
{
	if (Odekake_PickUpMenu_Increment_Timer(menu_data, 60))
	{
		Odekake_SetMenuStatus(menu_data, PICKUP_MENU_WAIT_FOR_BACKTRACK_30);
	}
}

/* Waits for 30 frames (?) before triggering a return to the main Chao Transporter menu. */
void Odekake_PickUpMenu_Wait_For_Backtrack_30(AL_OdekakeMenuMasterData1* menu_data)
{
	if (Odekake_PickUpMenu_Increment_Timer(menu_data, 30))
	{
		Odekake_SetMenuStatus(menu_data, 16);
	}
}

/* Presents the player with a Yes or No choice, responding to the warning about the TCG Chao */
/* overwriting the chao already in the GC garden. */
void Odekake_PickUpMenu_Player_Choice_YesNo(AL_OdekakeMenuMasterData1* menu_data)
{
	// Yes-no messages and associated checking functions go here
	Odekake_SetMenuStatus(menu_data, PICKUP_MENU_CHECK_PLAYER_CHOICE);
}

void Odekake_PickUpMenu_Save_Data(AL_OdekakeMenuMasterData1* menu_data)
{

}

void Odekake_PickUpMenu_4(AL_OdekakeMenuMasterData1* menu_data)
{

}

void Odekake_PickUpMenu_11(AL_OdekakeMenuMasterData1* menu_data)
{

}

void Odekake_PickUpMenu_16(AL_OdekakeMenuMasterData1* menu_data)
{
	if (!AL_OdekakeMenuMaster_Data_ptr->field_1C)
	{
		Odekake_SetMenuStatus(menu_data, PICKUP_MENU_BACKTRACK);
	}
}

/* Main execution loop of the Pickup Menu. */
void Odekake_PickUpMenu(AL_OdekakeMenuMasterData1* menu_data) // sub_74CD80 in SADXPC
{
	if (!AL_OdekakeMenuMaster_Data_ptr)
	{
		return;
	}
	
	switch (AL_OdekakeMenuMaster_Data_ptr->Status)
	{
		case PICKUP_MENU_INIT: // 0
			Odekake_PickUpMenu_Init(menu_data);
			break;
		case PICKUP_MENU_WAIT_FOR_INIT: // 1
			Odekake_PickUpMenu_Wait_For_Init(menu_data);
			break;
		case PICKUP_MENU_MAIN: // 3
			Odekake_PickupMenu_Main(menu_data);
			break;
		case 4: // 4
			Odekake_PickUpMenu_4(menu_data);
			break;
		case PICKUP_MENU_PICKUP_CHAO_WARNING: // 5
			Odekake_PickUpMenu_PickUp_Chao_Warning(menu_data);
			break;
		case PICKUP_MENU_PLAYER_CHOICE_YESNO: // 7
			Odekake_PickUpMenu_Player_Choice_YesNo(menu_data);
			break;
		case PICKUP_MENU_CHECK_PLAYER_CHOICE: // 8
			Odekake_PickUpMenu_Check_Player_Choice(menu_data);
			break;
		case PICKUP_MENU_SELECT_ITEM_FOR_PICKUP: // 9
			Odekake_PickUpMenu_Select_Item_For_Pickup(menu_data, menu_data->verticalSelect + 1, menu_data->horizontalSelect);
			break;
		case PICKUP_MENU_SAVE_DATA: // 10
			Odekake_PickUpMenu_Save_Data(menu_data);
			break;
		case 11: // 11
			Odekake_PickUpMenu_11(menu_data);
			break;
		case PICKUP_MENU_WAIT_FOR_MENU_EXIT: // 12
			Odekake_PickUpMenu_Wait_For_Menu_Exit(menu_data);
			break;
		case PICKUP_MENU_WAIT_FOR_TEXT_DRAW: // 13
			break;
		case PICKUP_MENU_WAIT_FOR_BACKTRACK_60: // 14
			Odekake_PickUpMenu_Wait_For_Backtrack_60(menu_data);
			break;
		case PICKUP_MENU_WAIT_FOR_BACKTRACK_30: // 15
			Odekake_PickUpMenu_Wait_For_Backtrack_30(menu_data);
			break;
		case 16: // 16
			Odekake_PickUpMenu_16(menu_data);
			break;
		case PICKUP_MENU_BACKTRACK: // 17
			break;
		case PICKUP_MENU_EXIT: // 18
			break;
		case 2:
		case 6:
			// Not used
			break;
	}
}