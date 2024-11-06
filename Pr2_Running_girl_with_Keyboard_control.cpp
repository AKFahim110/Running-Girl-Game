Practice - 2


#include <stdio.h>
#include <graphics.h>
#include "conio.h"
#include "EasyXPng.h"

#define WIDTH  600
#define HEIGHT 480
#define ROAD_Y 380    // Adjust this value to match your road's y-position
#define FRAMES 4

int speed = 10; // Speed of movement
int x = WIDTH / 2; // Start in the middle of the screen
int y = ROAD_Y; // Start at the road's y-position
int frameIndex = 0; // Current frame index
char direction = 'd'; // Direction: d = down, l = left, r = right, u = up

int main() {
	IMAGE im_bk;
	initgraph(WIDTH, HEIGHT);

	TCHAR filename[100];
	IMAGE img[FRAMES * 4]; // Array for all direction frames

	// Load animation frames for each direction
	for (int i = 0; i < FRAMES; i++) {
		_stprintf_s(filename, 100, _T("Z:\\Desktop\\assets\\girl\\gd%d.png"), i); // Down
		loadimage(&img[i], filename);

		_stprintf_s(filename, 100, _T("Z:\\Desktop\\assets\\girl\\gl%d.png"), i); // Left
		loadimage(&img[i + FRAMES], filename);

		_stprintf_s(filename, 100, _T("Z:\\Desktop\\assets\\girl\\gr%d.png"), i); // Right
		loadimage(&img[i + FRAMES * 2], filename);

		_stprintf_s(filename, 100, _T("Z:\\Desktop\\assets\\girl\\gu%d.png"), i); // Up
		loadimage(&img[i + FRAMES * 3], filename);
	}

	loadimage(&im_bk, _T("Z:\\Desktop\\assets\\Materials\\bg.png"));

	BeginBatchDraw();
	while (1) {
		putimage(0, 0, &im_bk); // Draw the background

		// Draw the character image based on direction
		if (direction == 'd') {
			putimagePng(x, y, &img[frameIndex]); // Down
		}
		else if (direction == 'l') {
			putimagePng(x, y, &img[frameIndex + FRAMES]); // Left
		}
		else if (direction == 'r') {
			putimagePng(x, y, &img[frameIndex + FRAMES * 2]); // Right
		}
		else if (direction == 'u') {
			putimagePng(x, y, &img[frameIndex + FRAMES * 3]); // Up
		}

		// Handle keyboard input for movement
		if (GetAsyncKeyState(VK_RIGHT) && x < WIDTH - 50) { // Move right
			x += speed;
			direction = 'r';
		}
		if (GetAsyncKeyState(VK_LEFT) && x > 0) { // Move left
			x -= speed;
			direction = 'l';
		}
		if (GetAsyncKeyState(VK_UP) && y > 0) { // Move up
			y -= speed;
			direction = 'u';
		}
		if (GetAsyncKeyState(VK_DOWN) && y < HEIGHT - 50) { // Move down
			y += speed;
			direction = 'd';
		}

		// Update frame index for animation
		frameIndex = (frameIndex + 1) % FRAMES;

		Sleep(60); // Control frame rate
		FlushBatchDraw(); // Refresh the screen

		// Exit condition (press ESC to quit)
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}
	}

	closegraph();
	return 0;
}
