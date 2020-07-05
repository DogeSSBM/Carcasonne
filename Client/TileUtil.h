#pragma once

Length gridLen = {0, 0};
Tile** grid = NULL;

Tile tileRotate(const Tile t, const Direction dir)
{
	Tile r = {0};
	r.bonus = t.bonus;
	r.land.C = t.land.C;
	if(dirLR(dir)){
		for(uint i = 0; i < 4; i++){
			r.road.arr[dir==DIR_R?dirROR(i):dirROL(i)] = t.road.arr[i];
			r.land.arr[dir==DIR_R?dirROR(i):dirROL(i)] = t.land.arr[i];
		}
	}else{
		for(uint i = 0; i < 4; i++){
			r.road.arr[dirINV(i)] = t.road.arr[i];
			r.land.arr[dirINV(i)] = t.land.arr[i];
		}
	}
	return r;
}

void deckShuffle(void)
{
	for(uint i = 0; i < deckSize*32; i++){
		const uint tileIndex1 = rand()%deckSize;
		const uint tileIndex2 = rand()%deckSize;
		Tile temp = deck[tileIndex1];
		deck[tileIndex1] = deck[tileIndex2];
		deck[tileIndex2] = temp;
	}
	printf("Shuffled  Deck\n");
}

void deckInit(void)
{
	uint current = 0;
	for(uint v = 0; v < TILE_VARIANTS; v++){
		printf("Varient %2u\n", v);
		for(uint n = 0; n < tileVarientNum[v]; n++){
			printf(
				"\tdeck tile: %2u/%2u \t  (%2u/%2u)\n",
				current+1,
				TILE_TOTAL,
				n+1,
				tileVarientNum[v]
			);
			deck[current++]=tileVarients[v];
		}
		putchar('\n');
	}
	printf("Constructed Deck\n");
}

uint tileNumRoad(const Tile t)
{
	uint total = 0;
	for(uint i = 0; i < 4; i++){
		total += t.road.arr[i];
	}
	return total;
}

void gridInit(void)
{
	grid = malloc(TILE_TOTAL*sizeof(Tile*));
	for(uint x = 0; x < TILE_TOTAL; x++){
		// printf("allocing  grid[%2u]\n", x);
		grid[x]=malloc(TILE_TOTAL*sizeof(Tile));
	}
	gridLen.x = TILE_TOTAL;
	gridLen.y = TILE_TOTAL;
	grid[gridLen.x/2][gridLen.y/2]=deck[51];
	deck[51]=deck[--deckSize];
}

void gameInit(void)
{
	deckInit();
	gridInit();
	deckShuffle();
}
