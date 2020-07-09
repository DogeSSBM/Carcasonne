#pragma once

void eraseTile(const uint x, const uint y, const uint scale)
{
	setColor(BLACK);
	fillSquare(x,y,scale);
}

void drawTile4(const Tile t, const uint x, const uint y, const uint scale, const bool solid)
{
	for(uint s = 0; s < 4; s++){
		Coord p = {x+scale/2, y+scale/2};
		if(solid)
			setColor(t.land.arr[s]==L_CITY?BROWN:GREEN);
		else
			setColor(t.land.arr[s]==L_CITY?TBROWN:TGREEN);
		for(uint i = 0; i < scale/2; i++){
			drawLineCoords(p, coordShift(p,dirROR(s),i*2));
			p = coordShift(p, s, 1);
			p = coordShift(p, dirROL(s), 1);
		}
	}
}

void drawTile5(const Tile t, const uint x, const uint y, const uint scale, const bool solid)
{
	drawTile4(t, x, y, scale, solid);
	switch(t.land.C){
		case L_CITY:
			setColor(solid?BROWN:TBROWN);
			break;
		case L_FIELD:
			setColor(solid?GREEN:TGREEN);
			break;
		case L_CHURCH:
			setColor(solid?RED:TRED);
			break;
	}
	fillSquare(x+scale/4, y+scale/4, scale/2);
}

void drawTile(const Tile t, const uint x, const uint y, const uint scale, const bool solid)
{
	if(t.land.C == L_NONE){
		//printf("t4\n");
		drawTile4(t, x, y, scale, solid);
	}
	else{
		//printf("t5\n");
		drawTile5(t, x, y, scale, solid);
	}
	const uint rscale = scale/12;
	setColor(solid?GREY:TGREY);
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
	const uint sscale = (scale/2)/3;
	if(t.bonus){
		setColor(solid?BLUE:TBLUE);
		fillSquare(x+sscale, y+sscale, sscale);
		setColor(solid?WHITE:TWHITE);
		fillSquare(x+sscale, y+sscale, sscale/2);
		fillSquare(x+sscale+sscale/2, y+sscale+sscale/2, sscale/2);
	}
}

/*void drawTileVariants(const uint xorig, const uint yorig, const uint scale)
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
}*/

/*void drawDeck(const uint xorig, const uint yorig,
const uint scale, const uint numTiles)
{
	setFontSize(scale/4);
	setFontColor(BLACK);
	uint x = xorig;
	uint y = yorig;
	for(uint i = 0; i < numTiles; i++){
		if(i >= deckSize){
			printf("Reached end of deck early\n");
			return;
		}
		//printf("Drawing deck[%2u]\n", i);
		drawTile(deck[i], x, y, scale);
		char istr[] = "00";
		sprintf(istr, "%02u", i);
		drawTextCentered(x+scale/2, y+scale/2, istr);
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
}*/

void drawGrid(const Offset off, const uint scale)
{
	const uint xoff = off.x-(scale*(gridLen.x/2));
	const uint yoff = off.y-(scale*(gridLen.y/2));
	for(uint x = 0; x < gridLen.x; x++){
		for(uint y = 0; y < gridLen.y; y++){
			const int sx = (x*scale)+xoff;
			const int sy = (y*scale)+yoff;
			if(isTileEmpty(grid[x][y]) || sx < 0 || sy < 0 ||
			sx > gfx.xlen || sy > gfx.ylen){
				continue;
			}
			drawTile(grid[x][y], sx, sy, scale, true);
		}
	}
	Coord gorig = {xoff, yoff};
	setColor(WHITE);
	drawRectCoords(
		gorig,
		coordShift(
			coordShift(
				gorig, DIR_D, gridLen.y*scale
			),
			DIR_R,
			gridLen.x*scale
		)
	);
}

void drawCurrentTile(const Tile currentTile)
{
	setColor(RED);
	fillSquare(gfx.xlen/2-(HCTLEN+8), gfx.ylen-(CTLEN+16), CTLEN+16);
	setColor(BLACK);
	fillSquare(gfx.xlen/2-(HCTLEN+5), gfx.ylen-(CTLEN+13), CTLEN+10);
	drawTile(currentTile, gfx.xlen/2-HCTLEN, gfx.ylen-(CTLEN+8), CTLEN, true);
}
