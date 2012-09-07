#include "SDL.h"

SDL_Surface *screen;
int width = 1024;
int height = 768;

void flatcolour(unsigned short r, unsigned short g, unsigned short b) {
    SDL_UnlockSurface(screen);
    Uint32 white = SDL_MapRGB(screen->format, r,g,b);
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            Uint32 *pixmem = (Uint32*)screen->pixels + (y * width) + x;
            *pixmem = white;
        }
    }
    SDL_LockSurface(screen);
    SDL_Flip(screen);
}

void checkerboard() {
    SDL_UnlockSurface(screen);
    Uint32 white = SDL_MapRGB(screen->format, 255,255,255);
    Uint32 black = SDL_MapRGB(screen->format, 0,0,0);
    int checker = 0;
    for (int y=0; y<height; y++) {
        checker = y % 2;
        for (int x=0; x<width; x++) {
            Uint32 *pixmem = (Uint32*)screen->pixels + (y * width) + x;
            *pixmem = checker ? white : black;
            checker = !checker;
        }
    }
    SDL_LockSurface(screen);
    SDL_Flip(screen);
}

void checkerboard2() {
    SDL_UnlockSurface(screen);
    Uint32 white = SDL_MapRGB(screen->format, 255,255,255);
    Uint32 black = SDL_MapRGB(screen->format, 0,0,0);
    int checker = 0;
    for (int y=0; y<height; y++) {
        checker = y % 3;
        if (checker==2) checker=1;
        for (int x=0; x<width; x++) {
            Uint32 *pixmem = (Uint32*)screen->pixels + (y * width) + x;
            *pixmem = checker ? white : black;
            checker = !checker;
        }
    }
    SDL_LockSurface(screen);
    SDL_Flip(screen);
}

void grid(int size) {
    SDL_UnlockSurface(screen);
    Uint32 white = SDL_MapRGB(screen->format, 255,255,255);
    Uint32 black = SDL_MapRGB(screen->format, 0,0,0);
    int checker = 0;
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            Uint32 *pixmem = (Uint32*)screen->pixels + (y * width) + x;
            *pixmem = ((x % size == 0) || (y % size == 0)) ? white : black;
        }
    }
    SDL_LockSurface(screen);
    SDL_Flip(screen);
}

void boxes() {
    SDL_UnlockSurface(screen);
    Uint32 colours[8];
    colours[0] = SDL_MapRGB(screen->format, 255,255,255);
    colours[1] = SDL_MapRGB(screen->format, 255,0,0);
    colours[2] = SDL_MapRGB(screen->format, 0,255,0);
    colours[3] = SDL_MapRGB(screen->format, 0,0,255);
    colours[4] = SDL_MapRGB(screen->format, 0,255,255);
    colours[5] = SDL_MapRGB(screen->format, 255,0,255);
    colours[6] = SDL_MapRGB(screen->format, 255,255,0);
    colours[7] = SDL_MapRGB(screen->format, 0,0,0);

    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            Uint32 *pixmem = (Uint32*)screen->pixels + (y * width) + x;
            int xbar = (x < width/2) ? x/16 : (width-x)/16;
            int ybar = (y < height/2) ? y/16 : (height-y)/16;
            *pixmem = colours[(xbar < ybar ? xbar : ybar) % 8];
        }
    }
    SDL_LockSurface(screen);
    SDL_Flip(screen);
}

int main(int argc, char *argv[])
{
    Uint32 initflags = SDL_INIT_VIDEO;
	Uint8  video_bpp = 32;
	Uint32 videoflags;
	
    int done;
	SDL_Event event;

	if ( SDL_Init(initflags) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",
			SDL_GetError());
		exit(1);
	}

	screen=SDL_SetVideoMode(width,height,32,SDL_SWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
    if (screen == NULL) {
		SDL_Quit();
		exit(2);
	}
    
    flatcolour(0,0,0);
    
	done = 0;
	while ( !done ) {
		/* Check for events */
		while ( SDL_PollEvent(&event) ) {
			switch (event.type) {
				case SDL_MOUSEMOTION:
					break;
				case SDL_MOUSEBUTTONDOWN:
					break;
				case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                            flatcolour(255,255,255);
                            break;
                        case SDLK_k:
                            flatcolour(0,0,0);
                            break;
                        case SDLK_r:
                            flatcolour(255,0,0);
                            break;
                        case SDLK_g:
                            flatcolour(0,255,0);
                            break;
                        case SDLK_b:
                            flatcolour(0,0,255);
                            break;
                        case SDLK_c:
                            flatcolour(0,255,255);
                            break;
                        case SDLK_m:
                            flatcolour(255,0,255);
                            break;
                        case SDLK_y:
                            flatcolour(255,255,0);
                            break;
                        case SDLK_x:
                            checkerboard();
                            break;
                        case SDLK_e:
                            flatcolour(127,127,127);
                            break;
                        case SDLK_i:
                            grid(16);
                            break;
                        case SDLK_d:
                            grid(8);
                            break;
                        case SDLK_z:
                            checkerboard2();
                            break;
                        case SDLK_o:
                            boxes();
                            break;
                        default:
                            break;
                    }
					break;
				case SDL_QUIT:
					return 0;
					break;
				default:
					break;
			}
		}
	}
	return 0;
}
