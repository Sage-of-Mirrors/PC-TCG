
struct  OdekakePickUpMenuData
{
	char mode;
	char field_1;
	unsigned char byte2;
	char field_3;
	char field_4;
	char field_5;
	__int16 field_6;
	float positionX;
	float positionY;
	float alpha;
	float field_14;
	int sine;
	float field_1C;
	int animationTimer;
	int ringRotation;
	ObjectMaster* ChaoObject;
};

void __cdecl LoadOdekakePickUpMenuDraw(char a1, float a2, float a3, unsigned __int16 a4);