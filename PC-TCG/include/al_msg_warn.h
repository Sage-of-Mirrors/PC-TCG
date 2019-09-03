#include <SA2ModLoader.h>

#pragma pack(push, 8)
struct __declspec(align(4)) MessageFontThing
{
	signed __int16 signed0;
	__int16 gap2;
	__int16 field_4;
	__int16 field_6;
	signed __int16* psigned8;
};
#pragma pack(pop)

#pragma pack(push, 8)
struct __declspec(align(4)) Message380
{
	int Mode;
	Buttons ButtonPress;
	int ButtonOn;
	float floatC;
	float float10;
	float float14;
	int dword18;
};
#pragma pack(pop)


struct Message380Array
{
	Message380 array[32];
};



#pragma pack(push, 8)
struct __declspec(align(4)) MessageField0
{
	MessageFontThing* dword0;
	float float4;
	float float8;
	float xSize;
	float ySize;
	int field_14;
	float field_18;
};
#pragma pack(pop)


#pragma pack(push, 8)
struct MessageField0Array
{
	MessageField0 array[9];
};
#pragma pack(pop)

#pragma pack(push, 8)
struct __declspec(align(4)) KinderCoMessageThing
{
	MessageField0Array* gap0;
	Message380Array* pointerToSomething0x380;
	__int16 someKindaCount;
	__int16 wordsLeftMaybe;
	float floatC;
	float posX;
	float posY;
	float rectSizeX;
	float rectSizeY;
	float field_20;
	float field_24;
	__int16 field_28;
	char enabled;
	char field_2B;
	int ContinueDotColor;
};
#pragma pack(pop)


#pragma pack(push, 8)
struct __declspec(align(4)) AL_MSGWarnKinderCoMessageThing
{
	char initialized;
	char field_1;
	char field_2;
	char field_3;
	float field_4;
	float field_8;
	float field_C;
	float field_10;
	KinderCoMessageThing* pkindercomessagething14;
};
#pragma pack(pop)
#pragma pack(push, 8)
struct __declspec(align(4)) AL_MSGWarnData
{
	char field_0;
	char field_1;
	char field_2;
	char field_3;
	float field_4;
	float field_8;
	float field_C;
	float field_10;
	MessageFontThing field_14[4];
};
#pragma pack(pop)

DataArray(AL_MSGWarnKinderCoMessageThing,AL_MSGWarnKinderMessageArray, 0x1A259E8, 4);
DataArray(AL_MSGWarnData, AL_MSGWarnDataArray, 0x01A276D8, 1);
FunctionPointer(void, __cdecl AL_MSGWarnKinderMessage_Init, (float a1, float a2, float a3, float a4), 0x005436F0);
VoidFunc(sub_543800,0x543800);//sub_72D880
FastcallFunctionPointer(void ,__fastcall sub_52DC90,(int a1),0x52DC90);
VoidFunc(sub_543860,0x543860); //72D910
VoidFunc(sub_52FB80, 0x52FB80); //72D930
VoidFunc(sub_5437B0,0x5437B0);
FunctionPointer(void, __cdecl sub_57EE80,(float a1, float a2, float a3),0x57EE80);
DataPointer(int, dword_19F6444, 0x19F6444);
VoidFunc(al_confirmsave_load_zero,0x530230);