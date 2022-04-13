// Imports
#include <iostream>
#include <SDL.h>
#include <math.h>
#include<stdlib.h>
#include "Screen.h"
#include "Swarm.h"
// Namespace
using namespace std;
//Start main function
int main(int argc, char* argv[]) {
	// Initializes the screen and swarm header files, and checks to make sure that the SDL library is initializing properly
	srand(time(NULL));
	Screen screen;
	if (screen.init() == false) {
		cout << "Error initialising SDL." << endl;
	}
	Swarm swarm;

	while (true) {
		//Updates particles based on a function in the SDL library
		int elapsed = SDL_GetTicks();	
		swarm.update(elapsed);
		// Sets Colours and colour changes	
		unsigned char red = (unsigned char)(1 + sin(elapsed * 0.003)) * 128;
		unsigned char green = (unsigned char)(1 + sin(elapsed * 0.002)) * 128;
		unsigned char blue = (unsigned char)(1 + sin(elapsed * 0.001)) * 128;
		if (red == 255) {
			red = 3;
		}
		if (green == 255) {
			green = 2;
		}
		if (blue == 255) {
			blue = 4;
		}

		//Draw particles
		const Particle* const pParticles = swarm.getParticles();
		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];
			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH/2;
			int y = particle.m_y * Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT/2;
			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();

			//Draw the Screen
			screen.update();
		//Check for messages/events
		if (screen.processEvents() == false) {
			break;
		}
	}
	return 0;
}
// End main function