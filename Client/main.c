// CLIENT
#define PORT	8421
#define BUFFERLEN	1024
#include "Includes.h"

int main(int argc, char const *argv[])
{
	init(1800, 1000);
	const uint qs = gfx.xlen/4;
	gameInit();
	Offset gridOff = {gridLen.x,0};
	while(1){
		clear();
		const Ticks frameEnd = getTicks()+TPF;
		drawGrid(gridOff.x, gridOff.x, 20);
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
			printf("Shuffling deck\n");
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			for(uint j = 0; j < deckSize; j++){
				deck[j] = tileRotate(deck[j], DIR_R);
			}
			break;
		case SDLK_a:
		case SDLK_LEFT:
			for(uint j = 0; j < deckSize; j++){
				deck[j] = tileRotate(deck[j], DIR_L);
			}
			break;
		}
		break;
	case SDL_MOUSEMOTION:

		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			break;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
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
