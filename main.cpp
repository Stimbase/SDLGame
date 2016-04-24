#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init() {
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
	} else {
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			success = false;
		} else gScreenSurface = SDL_GetWindowSurface(gWindow);
	}

	return success;
}

//Loads bitmap
bool loadBMP(SDL_Surface* &surface, char* fileName) {
	surface = SDL_LoadBMP(fileName);
	if(surface == NULL) {
		std::cout << "Unable to load image " << fileName << '!' << std::endl
				  << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

//Frees media
void freeMedia(SDL_Surface* &surface) {
	SDL_FreeSurface(surface);
	surface = NULL;
}

void close() {
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[]) {
	//Start up SDL and create window
	if(!init()) std::cout << "Failed to initialize!" << std::endl;
	else {
		//Load media
		if(!loadBMP(gHelloWorld, "hello.bmp")) std::cout << "Failed to load media!" << std::endl;
		else {
			//Apply the image
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
			
			//Update the surface
			SDL_UpdateWindowSurface(gWindow);

			//Wait five seconds
			SDL_Delay(5000);
		}
	}

	//Free resources and close SDL
	freeMedia(gHelloWorld);
	close();

	return 0;
}
