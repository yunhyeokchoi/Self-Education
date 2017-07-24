#include <SDL.h>
//For printf, since we don't have any debug tools which can break the program atm.
#include <stdio.h>
//This is where all the pointers to image files will be stored.
#include <list>

class KatoEngine
{
	public:
		KatoEngine(const char* title,
					  unsigned int scrwidth, unsigned int scrheight)
			: pm_scrwidth(scrwidth), pm_scrheight(scrheight),
			  pm_title(title), pm_isquit(false)
		{
			SDLInit();
		}

		void Update()
		{
			SDL_Event eventhnd; //an event handler

			while (!pm_isquit)
			{
				//Till the event gets emptied out.
				while (SDL_PollEvent(&eventhnd))
				{
					/*
						https://wiki.libsdl.org/SDL_EventType#Remarks
						#1 An SDL_QUIT event is generated when the user clicks 
							on the close button of the last existing window.
					*/
					if (eventhnd.type == SDL_QUIT)
					{
						pm_isquit = true;
						//Stop assessing for the leftover msgs, and just break.
						//break;
					}
					else if (eventhnd.type == SDL_KEYDOWN)
					{
						switch (eventhnd.key.keysym.sym)
						{
							case SDLK_UP :
							{
								printf("UP\n");
								break;
							}
							case SDLK_DOWN :
							{
								printf("DOWN\n");
								break;
							}
							case SDLK_LEFT :
							{
								printf("LEFT\n");
								break;
							}
							case SDLK_RIGHT :
							{
								printf("RIGHT\n");
								break;
							}
						}
					}
					
				}
			}

			this->Quit();
		}

		~KatoEngine() {};

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
					//SDL_Delay(5000);
				}
			}
		}

		void Quit()
		{
			SDL_DestroyWindow(pm_psdlwin);
			SDL_Quit();
		}

		unsigned int pm_scrwidth;
		unsigned int pm_scrheight;
		const char* pm_title;

		SDL_Window* pm_psdlwin;
		SDL_Surface* pm_psurf;

		bool pm_isquit;
		std::list<SDL_Surface*> pm_listpimage;
};

//Function signature for the main should be like this,
//so as to make it compatible with SDL.
int main(int, char*[])
{
	KatoEngine engine("Supreme Lord Yunhyeok", 800, 600);
	engine.Update();

	return 0;
}