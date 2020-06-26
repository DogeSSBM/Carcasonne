#pragma once

typedef enum{L_FIELD, L_CITY, L_NONE}LandType;


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
	Road road;
	Land land;
	union{
		struct Tile *arr[4];
		struct{
			struct Tile *U;
			struct Tile *R;
			struct Tile *D;
			struct Tile *L;
		};
	};
}Tile;

void drawTile(const Tile t, const uint x, const uint y, const uint scale)
{

}
