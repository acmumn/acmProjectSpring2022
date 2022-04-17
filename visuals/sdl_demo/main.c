#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// 2^20 = 1048576
#define ITOIF(x) ((x) * 1048576)
#define IFTOI(x) ((x) / 1048576)

/* #define ITOIF(x) ((x) * 4194304) */
/* #define IFTOI(x) ((x) / 4194304) */

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 825

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

	int oldx, oldy, oldz;

	int x = ITOIF(3);
	int y = ITOIF(3);
	int z = ITOIF(3);

	const int sigma = 10;
	const int betaN = 8;
	const int betaD = 3;
	const int rho = 28;
	const int dt = 60; // 1/60
	const int scale = 10;

	int oldWinX, oldWinY, winX, winY;
	oldWinX = (WINDOW_WIDTH/2) + IFTOI(x*scale);
	oldWinY = (WINDOW_HEIGHT/2) + IFTOI(y*scale);

	while (1) {

		int dx = sigma * (y - x);
		int dy = x * IFTOI(ITOIF(rho) - z) - y;
		int dz = x*IFTOI(y) - betaN*z / betaD;

		oldx = x;
		oldy = y;
		oldz = z;

		x += dx/dt;
		y += dy/dt;
		z += dz/dt;

		winX = (WINDOW_WIDTH/2) + IFTOI(x*scale);
		winY = (WINDOW_HEIGHT/2) + IFTOI(y*scale);

		SDL_RenderDrawLine(renderer, oldWinX, oldWinY, winX, winY);
		SDL_RenderPresent(renderer);

		oldWinX = winX;
		oldWinY = winY;

		if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
			break;
		}
		SDL_Delay(16); // 60fps
	}

	return EXIT_SUCCESS;
}
