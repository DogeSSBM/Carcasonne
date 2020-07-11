// CLIENT
#define PORT	8421
#define BUFFERLEN	1024
#define CTLEN	200
#define HCTLEN	(CTLEN/2)
#include "Includes.h"

void drawCrosshair(const Coord pos, const uint size)
{
	setColor(WHITE);
	Coord p1 = coordShift(pos, DIR_L, size);
	Coord p2 = coordShift(pos, DIR_R, size);
	drawLineCoords(p1, p2);
	p1 = coordShift(pos, DIR_U, size);
	p2 = coordShift(pos, DIR_D, size);
	drawLineCoords(p1, p2);
}

Coord mouseGridPos(const Coord pos, const Offset gridOff, const uint scale)
{
	const Coord gorig = {
		gridOff.x-(scale*(gridLen.x/2)),
		gridOff.y-(scale*(gridLen.y/2))
	};
	const Coord mgoff = {
		pos.x>=gorig.x?(pos.x - gorig.x)/scale:-1,
		pos.y>=gorig.y?(pos.y - gorig.y)/scale:-1
	};
	return mgoff;
}

typedef union{
	Coord arr[2];
	struct{
		Coord pos;
		Coord last;
	};
}MousePos;

void drawMouse(const Coord pos, const Offset gridOff, const uint scale)
{
		static char buffer[20] = {0};
		setFontSize(16);
		setFontColor(WHITE);
		sprintf(buffer, "(%4u,%4u)", pos.x, pos.y);
		drawText(pos.x, pos.y, buffer);
		Coord gpos = {pos.x/scale, pos.y/scale};
		sprintf(buffer, "(%4u,%4u)", gpos.x, gpos.y);
		drawText(pos.x, pos.y+16, buffer);

		Coord gorig = {
			gridOff.x-(scale*(gridLen.x/2)),
			gridOff.y-(scale*(gridLen.y/2))
		};
		Coord mgoff = {
			pos.x>=gorig.x?(pos.x - gorig.x)/scale:-1,
			pos.y>=gorig.y?(pos.y - gorig.y)/scale:-1
		};

		sprintf(buffer, "(%4d,%4d)", mgoff.x, mgoff.y);
		drawText(pos.x, pos.y+32, buffer);

		mgoff.x*=scale;
		mgoff.x+=gorig.x;
		mgoff.y*=scale;
		mgoff.y+=gorig.y;
		drawCrosshair(mgoff, scale);
}

void drawGhost(const Tile t, const Coord pos, const Offset gridOff, const uint scale)
{
	Coord gorig = {
		gridOff.x-(scale*(gridLen.x/2)),
		gridOff.y-(scale*(gridLen.y/2))
	};
	Coord mgoff = mouseGridPos(pos, gridOff, scale);
	const bool placeable = tileCanPlace(t, mgoff);
	mgoff.x*=scale;
	mgoff.x+=gorig.x;
	mgoff.y*=scale;
	mgoff.y+=gorig.y;
	if(placeable)
		drawTile(t, mgoff.x, mgoff.y, scale, true);
	setColor(placeable?BLUE:RED);
	fillBorder(mgoff.x, mgoff.y, scale, scale, scale/16);
}

int main(int argc, char const *argv[])
{
	init(1800, 1000);
	gameInit();

	Offset gridOff = {gfx.xlen/2, gfx.ylen/2};
	uint scale = 15;
	bool pan = false;
	Tile currentTile = tilePickup();
	MousePos mpos = {0};

	while(1){
		const Ticks frameEnd = getTicks()+TPF;
		clear();
		drawGrid(gridOff, scale);
		drawGhost(currentTile, mpos.pos, gridOff, scale);
		drawCurrentTile(currentTile);
		//drawMouse(mpos.pos, gridOff, scale);
// ################################
// #       Event loop Start       #
// ################################
while(getTicks() < frameEnd){
	static Event event;
	if(!SDL_WaitEventTimeout(&event, frameEnd-getTicks()))
		break;
	switch(event.type){
	case SDL_QUIT:
		printf("Quitting now!\n");
		exit(0);
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			printf("Esc key pressed, exiting now\n");
			exit(0);
			break;
		case SDLK_SPACE:
			gridOff.x = gfx.xlen/2;
			gridOff.y = gfx.ylen/2;
			scale = 15;
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			currentTile = tileRotate(currentTile, DIR_R);
			break;
		case SDLK_a:
		case SDLK_LEFT:
			currentTile = tileRotate(currentTile, DIR_L);
			break;
		case SDLK_r:
			currentTile = tilePickupSwap(currentTile);
			break;
		}
		break;
	case SDL_MOUSEMOTION: // panning
		mpos.pos.x = event.motion.x;
		mpos.pos.y = event.motion.y;
		if(pan){
			gridOff.x += event.motion.xrel;
			gridOff.y += event.motion.yrel;
		}
		break;
	case SDL_MOUSEWHEEL:
		if(event.wheel.y > 0)		// zooming in
			scale = CEIL(scale+1+scale/5, 200);
		else if(event.wheel.y < 0)	// zooming out
			scale = clamp(scale-1-scale/5, 3, 200);
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			mpos.last.x = event.button.x;
			mpos.last.y = event.button.y;
			pan = true;
			break;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			pan = false;
			if(!sameCoord(mpos.last, mpos.pos))
				break;
			Coord gpos = mouseGridPos(mpos.pos, gridOff, scale);
			if(tilePlace(currentTile, gpos)){
				currentTile = tilePickup();
			}
			break;
		}
		break;
	default:
		break;
	}
}
	draw();
// ################################
// #        Event loop end        #
// ################################
	}
	return 0;
}
