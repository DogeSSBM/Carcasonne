#pragma once

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
	// printf("\n#########Shuffled  Deck#########\n");
}

void deckInit(void)
{
	uint decknum = 0;
	for(uint v = 0; v < TILE_VARIANTS; v++){
		for(uint n = 0; n < tileVarientNum[v]; n++){
			printf(
				"decknum: %2u variant: %2u (%2u of %2u)\n",
				decknum,
				v,
				n+1,
				tileVarientNum[n]
			);
			deck[decknum]=tileVarients[v];
			decknum++;
		}
	}
	printf("\n########Constructed Deck########\n");
}

uint tileNumRoad(const Tile t)
{
	uint total = 0;
	for(uint i = 0; i < 4; i++){
		total += t.road.arr[i];
	}
	return total;
}
