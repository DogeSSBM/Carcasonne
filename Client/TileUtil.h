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

void tileCpy(Tile *dest, const Tile *source)
{
	for(uint i = 0; i < 4; i++){
		dest->arr[i] = source->arr[i];
		dest->road.arr[i] = source->road.arr[i];
		dest->land.arr[i] = source->land.arr[i];
	}
	dest->land.C = source->land.C;
	dest->bonus = source->bonus;
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
			tileCpy(&deck[decknum], &tileVarients[v]);
			decknum++;
		}
	}
	printf("\n########DONE########\n");
}

void drawTile4(const Tile t, const uint x, const uint y, const uint scale)
{
	for(uint s = 0; s < 4; s++){
		Coord p = {x+scale/2, y+scale/2};
		setColor(t.land.arr[s]==L_CITY?BROWN:GREEN);
		for(uint i = 0; i < scale/2; i++){
			drawLineCoords(p, coordShift(p,dirROR(s),i*2));
			p = coordShift(p, s, 1);
			p = coordShift(p, dirROL(s), 1);
		}
	}
}

void drawTile5(const Tile t, const uint x, const uint y, const uint scale)
{
	drawTile4(t, x, y, scale);
	switch(t.land.C){
		case L_CITY:
			setColor(BROWN);
			break;
		case L_FIELD:
			setColor(GREEN);
			break;
		case L_CHURCH:
			setColor(RED);
			break;
	}
	fillSquare(x+scale/4, y+scale/4, scale/2);
}

uint tileNumRoad(const Tile t)
{
	uint total = 0;
	for(uint i = 0; i < 4; i++){
		total += t.road.arr[i];
	}
	return total;
}

void eraseTile(const uint x, const uint y, const uint scale)
{
	setColor(BLACK);
	fillSquare(x,y,scale);
}

void drawTile(const Tile t, const uint x, const uint y, const uint scale)
{
	if(t.land.C == L_NONE){
		//printf("t4\n");
		drawTile4(t, x, y, scale);
	}
	else{
		//printf("t5\n");
		drawTile5(t, x, y, scale);
	}
	const uint rscale = scale/12;
	setColor(GREY);
	for(uint i = 0; i < 4; i++){
		if(!t.road.arr[i])
			continue;
		Coord c1 = {x+scale/2, y+scale/2};
		Coord c2 = coordShift(c1, i, scale/2);
		c1 = coordShift(c1, dirROL(i), rscale);
		c2 = coordShift(c2, dirROR(i), rscale);
		if(tileNumRoad(t) != 2){
			c1 = coordShift(c1, i, rscale*2);
		}
		fillRectCoords(c1, c2);
	}
	drawSquare(x, y, scale);
}

void drawTileVariants(const uint xorig, const uint yorig, const uint scale)
{
	uint x = xorig;
	uint y = yorig;
	for(uint i = 0; i < TILE_VARIANTS; i++){
		printf("drawing variant %2u\n", i);
		drawTile(tileVarients[i], x, y, scale);
		if(y+scale*2 >= gfx.ylen){
			y = yorig;
			if(x+scale > gfx.xlen){
				printf("Cant fit any more tiles, returning early\n");
				return;
			}
			x+=scale;
		}else{
			y+=scale;
		}
	}
}
