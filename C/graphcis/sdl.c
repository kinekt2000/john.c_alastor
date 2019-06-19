#include <SDL/SDL.h>


int main(){
	SDL_Surface* hello;
	SDL_Surface* screen;

	SDL_Init(SDL_INIT_EVERYTHING);

	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
	hello = SDL_LoadBMP("phyllotaxis.bmp");

	SDL_BlitSurface(hello, NULL, screen, NULL);
	SDL_Flip(screen);

	SDL_Delay(2000);

	SDL_FreeSurface(hello);
	SDL_FreeSurface(screen);
	SDL_Quit();
	return 0;
}
