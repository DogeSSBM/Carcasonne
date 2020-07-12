// CLIENT
#define PORT	8421
#define BUFFERLEN	1024
#define CTLEN	200
#define HCTLEN	(CTLEN/2)
#include "Includes.h"

typedef union{
	Coord arr[2];
	struct{
		Coord pos;
		Coord last;
	};
}MousePos;

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
