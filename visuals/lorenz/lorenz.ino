#include <Inkplate.h>
#include "Fonts/FreeMonoBold24pt7b.h"

Inkplate display(INKPLATE_1BIT);

#define WIDTH 1200
#define HEIGHT 825

// 2^20 = 1048576
#define ITOIF(x) ((x) * 1048576)
#define IFTOI(x) ((x) / 1048576)

const GFXfont *font = &FreeMonoBold24pt7b;

int oldx, oldy, oldz;

int x;
int y;
int z;

int oldWinX, oldWinY, winX, winY;

const int sigma = 10;
const int betaN = 8;
const int betaD = 3;
const int rho = 28;
const int dt = 120; // 1/120
const int scale = 10;

// how many lines it calculates before drawing
const int update_interval = 20;
int iteration;

void setup() {
	// put your setup code here, to run once:
	display.begin();

	x = ITOIF(3);
	y = ITOIF(3);
	z = ITOIF(3);
	iteration = 0;

	oldWinX = (WIDTH/2) + IFTOI(x*scale);
	oldWinY = (HEIGHT/2) + IFTOI(y*scale);

	/* sigma = 10; */
	/* beta = 8/3; */
	/* rho = 28; */
	/* dt = 0.01666; */

	/* scale = 10; */

	/* display.setFont(&FreeMonoBold24pt7b); */
	/* display.setTextSize(1); */
	/* display.setCursor(5,HEIGHT-8); */
	/* display.print("Hello, World!"); */
}

void loop() {
	// put your main code here, to run repeatedly:

	int dx = sigma * (y - x);
	int dy = x * IFTOI(ITOIF(rho) - z) - y;
	int dz = x*IFTOI(y) - betaN*z / betaD;

	oldx = x;
	oldy = y;
	oldz = z;

	x += dx/dt;
	y += dy/dt;
	z += dz/dt;

	winX = (WIDTH/2) + IFTOI(x*scale);
	winY = (HEIGHT/2) + IFTOI(y*scale);

	display.drawLine(oldWinX, oldWinY, winX, winY, BLACK);

	oldWinX = winX;
	oldWinY = winY;

	if (iteration == update_interval) {
		display.partialUpdate();
		iteration = 0;
	}

	iteration++;
}
