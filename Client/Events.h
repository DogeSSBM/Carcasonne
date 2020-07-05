#pragma once

void events(Ticks frameEnd, bool *thing)
{
	*thing = false;
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
			case SDLK_SPACE:
				printf("Shuffling deck\n");
				*thing = true;
				break;
			case SDLK_w:
			case SDLK_UP:
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				break;
			case SDLK_s:
			case SDLK_DOWN:
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
		ticksLeft = frameEnd - getTicks();
	}
}
