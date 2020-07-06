// CLIENT
#define PORT	8421
#define BUFFERLEN	1024
#define CTLEN	200
#define HCTLEN	(CTLEN/2)
#include "Includes.h"

Coord mouseGridPos(const uint x, const uint y, const Offset gridOff, const uint scale)
{
	const Coord relMouse = {(x-gridOff.x)%scale, (y-gridOff.y)%scale};
	return relMouse;
}

int main(int argc, char const *argv[])
{
	init(1800, 1000);
	gameInit();

	Offset gridOff = {gfx.xlen/2, gfx.ylen/2};
	uint scale = 15;
	bool pan = false;
	Tile currentTile = tilePickup();
	while(1){
		const Ticks frameEnd = getTicks()+TPF;
		clear();
		drawGrid(gridOff.x, gridOff.y, scale);
		setColor(RED);
		fillSquare(gfx.xlen/2-(HCTLEN+8), gfx.ylen-(CTLEN+16), CTLEN+16);
		setColor(BLACK);
		fillSquare(gfx.xlen/2-(HCTLEN+5), gfx.ylen-(CTLEN+13), CTLEN+10);
		drawTile(currentTile, gfx.xlen/2-HCTLEN, gfx.ylen-(CTLEN+8), CTLEN, true);
		draw();
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
			// todo (rotating tile)
			break;
		case SDLK_a:
		case SDLK_LEFT:
			// todo (rotating tile)
			break;
		}
		break;
	case SDL_MOUSEMOTION: // panning
		if(pan){
			gridOff.x += event.motion.xrel;
			gridOff.y += event.motion.yrel;
		}
		break;
	case SDL_MOUSEWHEEL: // zooming
		if(event.wheel.y > 0)		// zooming in
			scale = CEIL(scale+1+scale/5, 200);
		else if(event.wheel.y < 0)	// zooming out
			scale = clamp(scale-1-scale/5, 3, 200);
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT: // enabling panning
			pan = true;
			break;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT: // disabling panning
			pan = false;
			break;
		}
		break;
	default:
		break;
	}
}
// ################################
// #        Event loop end        #
// ################################
	}
	return 0;
}
