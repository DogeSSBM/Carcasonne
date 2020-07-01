#pragma once
#define DBGSCALE 48

void drawDbgText(const uint scale, const uint index)
{
	setFontSize(DBGSCALE);
	setFontColor(WHITE);
	printf("scale = %3u\n", scale);
	printf("index = %3u\n", index);
	char buffer[20] = {0};
	sprintf(buffer, "scale = %3u", scale);
	drawText(DBGSCALE, DBGSCALE, buffer);
	sprintf(buffer, "scale = %3u", scale);
	drawText(DBGSCALE, DBGSCALE*2, buffer);
}

void events(Ticks frameEnd)
{
	static uint tileIndex = 0;
	static Tile t = {0};
	static uint scale = 90;
	static uint x = 0;
	static uint y = 0;

	i32 ticksLeft = frameEnd - getTicks();
	while(ticksLeft > 0){
		static Event event;
		if(!SDL_WaitEventTimeout(&event, ticksLeft))
			return;
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
				return;
				break;
			case SDLK_w:
			case SDLK_UP:
				if(y+scale*2 >= gfx.ylen){
					tileIndex = wrap(tileIndex-1,0,TILE_VARIANTS);
					t = tileVarients[tileIndex];
				}
				break;
			case SDLK_d:
			case SDLK_RIGHT:

				break;
			case SDLK_s:
			case SDLK_DOWN:
				tileIndex = wrap(tileIndex-1,0,TILE_VARIANTS);
				t = tileVarients[tileIndex];
				clear();

				draw();
				break;
			case SDLK_a:
			case SDLK_LEFT:

				break;
			}
			break;
		case SDL_MOUSEMOTION:

			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:

				break;
			case SDL_BUTTON_RIGHT:

				break;
			case SDL_BUTTON_MIDDLE:

				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:

				break;
			case SDL_BUTTON_RIGHT:

				break;
			case SDL_BUTTON_MIDDLE:

				break;
			}
			break;
		default:

			break;
		}
		ticksLeft = frameEnd - getTicks();
	}
}
