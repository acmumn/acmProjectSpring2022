#include <SDL2/SDL.h>
#include <unistd.h>

#define WINDOW_WIDTH 600

int main(int argc, char **argv) {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
	SDL_Event event;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	int count = 0;
	while (1) {
		count++;
		for (int i = 0; i < 10; i++) {
			SDL_RenderDrawPoint(renderer, count, 100+i);
		}
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
			break;
		}
		usleep(16666);
	}

	return EXIT_SUCCESS;
}
