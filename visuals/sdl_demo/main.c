#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char **argv) {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	SDL_Event event;

	// white background
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	// black lines for attractor
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	double oldx, oldy, oldz;

	double x = 3;
	double y = 3;
	double z = 3;

	double sigma = 10;
	double beta = 8/3;
	double rho = 28;
	double dt = 0.01666;

	// deviate values a little bit
	srand((unsigned int) time(NULL));

	double scale = 10;

	while (1) {

		double dx = sigma * (y - x);
		double dy = x * (rho - z) - y;
		double dz = x*y - beta*z;

		oldx = x;
		oldy = y;
		oldz = z;

		x += dx*dt;
		y += dy*dt;
		z += dz*dt;

		SDL_RenderDrawLine(renderer, (WINDOW_WIDTH/2)+(oldx*scale), (WINDOW_HEIGHT/2)+(oldy*scale), (WINDOW_WIDTH/2)+(x*scale), (WINDOW_HEIGHT/2)+(y*scale));
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
			break;
		}
		SDL_Delay(16); // 60fps
	}

	return EXIT_SUCCESS;
}
