struct AL_OdekakeMenuMasterData1
{
	int gap0;
	int menuID;
	int field_8;
	int Status;
	int field_10;
	int field_14;
	int field_18;
	int field_1C;
	int field_20;
	int horizontalSelect;
	int verticalSelect;
};
VoidFunc(sub_57E680, 0x57E680);

DataPointer(AL_OdekakeMenuMasterData1*, AL_OdekakeMenuMaster_Data_ptr, 0x1AED324);
void __cdecl AL_OdekakeMenuMaster_(ObjectMaster* a1);
void sub_72DC40();
//int sub_72DBF0();