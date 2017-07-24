#include <SDL.h>
#include <stdio.h>

class SDLCls
{
	public:
		SDLCls(const char* title, 
				 unsigned int scrwidth, unsigned int scrheight)
			: pm_scrwidth(scrwidth), pm_scrheight(scrheight),
			  pm_title(title)
		{
			SDLInit();
		}

		void Quit()
		{
			SDL_DestroyWindow(pm_psdlwin);
			SDL_Quit();

			SDL_DestroyWindow(pm_psdlwin);
			SDL_Quit();

			SDL_DestroyWindow(pm_psdlwin);
			SDL_Quit();
		}

		~SDLCls() {};

	private:
		void SDLInit()
		{
			if (SDL_Init(//SDL's video subsystem
							 SDL_INIT_VIDEO) < 0)
				printf("Failed to initialize SDL; %s\n", SDL_GetError());
			else
			{
				pm_psdlwin = SDL_CreateWindow(pm_title,
														SDL_WINDOWPOS_CENTERED,
														SDL_WINDOWPOS_CENTERED,
														pm_scrwidth,
														pm_scrheight,
														SDL_WINDOW_SHOWN);
				if (!pm_psdlwin)
					printf("Failed to create Window; %s\n", SDL_GetError());
				else
				{
					//Get HDC for the window(?)
					pm_psurf = SDL_GetWindowSurface(pm_psdlwin);
					//perhaps format in the SDL_Surface struct has something to do with
					//pixelformatdescriptor(?)
					SDL_FillRect(pm_psurf, 0, SDL_MapRGB(pm_psurf->format, 0xFF, 0xFF, 0xFF));
					//SwapBuffer(?)
					SDL_UpdateWindowSurface(pm_psdlwin);
					SDL_Delay(5000);
				}
			}
		}

		unsigned int pm_scrwidth;
		unsigned int pm_scrheight;
		const char* pm_title;

		SDL_Window* pm_psdlwin;
		SDL_Surface* pm_psurf;
};

int main(int, char*[])
{
	SDLCls sdlcls("Supreme Lord Yunhyeok", 800, 600);
	sdlcls.Quit();

	return 0;
}