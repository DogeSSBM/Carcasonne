#pragma once

void drawCarSquare(const uint x, const uint y, const char letter)
{
	const uint sx = gridToScreen(x);
	const uint sy = gridToScreen(y);
	for(uint i = 0; i < NUMCAR; i++){
		if(letter == carArr[i].letter){
			setColor(carArr[i].color);
			break;
		}
	}
	fillSquare(x*SCALE+10, y*SCALE+10, SCALE-20);
	if(x < GRIDLEN-1 && grid[x+1][y] == grid[x][y])
		fillSquare(sx+HSCALE+15, sy+15, SCALE-30);
	if(y < GRIDLEN-1 && grid[x][y+1] == grid[x][y])
		fillSquare(sx+15, sy+HSCALE+15, SCALE-30);
}

void drawGrid(void)
{
	setColor(GREY2);
	fillScreen();
	setColor(GREY1);
	for(uint x = 0; x < GRIDLEN; x++){
		for(uint y = 0; y < GRIDLEN; y++){
			fillSquare(x*SCALE+10, y*SCALE+10, SCALE-20);
		}
	}
	setFontSize(HSCALE);
	for(uint i = 0; i < GRIDLEN; i++){
		drawText(i*SCALE+QSCALE, 2*SCALE+32, "-");
		drawText(i*SCALE+QSCALE+20, 2*SCALE+32, "-");
		drawText(i*SCALE+QSCALE+30, 2*SCALE+32, "-");
		drawText(i*SCALE+HSCALE-10, 2*SCALE+QSCALE, ">");
	}
}

void drawCarSquareOutline(const uint x, const uint y)
{
	const uint sx = gridToScreen(x);
	const uint sy = gridToScreen(y);
	setColor(WHITE);
	fillSquare(x*SCALE+5, y*SCALE+5, SCALE-10);
	if(x < GRIDLEN-1 && grid[x+1][y] == grid[x][y])
		fillSquare(sx+HSCALE+10, sy+10, SCALE-20);
	if(y < GRIDLEN-1 && grid[x][y+1] == grid[x][y])
		fillSquare(sx+10, sy+HSCALE+10, SCALE-20);
}

void drawCarOutline(const char letter)
{
	for(uint x = 0; x < GRIDLEN; x++){
		for(uint y = 0; y < GRIDLEN; y++){
			if(grid[x][y] == letter)
				drawCarSquareOutline(x, y);
		}
	}
}

void drawCars(void)
{
	for(uint x = 0; x < GRIDLEN; x++){
		for(uint y = 0; y < GRIDLEN; y++){
			if(grid[x][y] != '-'){
				drawCarSquare(x, y, grid[x][y]);
			}
		}
	}
}
