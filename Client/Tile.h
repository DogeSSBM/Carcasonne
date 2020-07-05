#pragma once
typedef enum{L_NONE, L_FIELD, L_CITY, L_CHURCH, L_NUM}LandType;

typedef union{
	bool arr[4];
	struct{
		bool U;
		bool R;
		bool D;
		bool L;
	};
}Road;

typedef union{
	LandType arr[5];
	struct{
		LandType U;
		LandType R;
		LandType D;
		LandType L;
		LandType C;
	};
}Land;

typedef struct Tile{
	bool bonus;
	Road road;
	Land land;
}Tile;
