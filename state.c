#include <state.h>
#include <SDL2/SDL.h>
#include <stdio.h>

void state_init(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		abort();
	}
}

void state_quit(void) {
	SDL_Quit();
}
