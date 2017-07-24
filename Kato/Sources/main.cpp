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
			: pm_scrwidth(scrwidth), pm_scrheight(scrheight), pm_title(title), 
				pm_psdlwin(0), pm_psurf(0), pm_isquit(false)
		{
			Initialize();
		}

		void Update()
		{
			SDL_Event eventhnd; //an event handler

#if defined(_DEBUG)
{
			printf("Following Timer::Show should be 0.\n");
			pm_timer.Show();
			pm_timer.Start();

			printf("Following Timer::Show should be {elapsed_tick + (current_tick - init_tick)}.\n");
			pm_timer.Show();

			printf("Timer::Pause should be called once.\n");
			pm_timer.Pause();
			pm_timer.Pause();
			pm_timer.Pause();

			printf("Following Timer::Show should be (elapsed_tick).\n");
			pm_timer.Show();
			pm_timer.Stop();
			pm_timer.Start();
			pm_timer.Pause();

			printf("Timer::Unpause should be called once.\n");
			pm_timer.Unpause();
			pm_timer.Unpause();
			pm_timer.Unpause();

			printf("Following Timer::Show should be {elapsed_tick + (current_tick - init_tick)}.\n");
			pm_timer.Show();
}
#endif

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
					//PhysicsUpdate(1.f);
				}
			}

			this->Quit();
		}

	private:
		class Timer
		{
			public:
				/*
					Start and timer starts counting from 0.
					Pressing Start at any situation should do one thing; Start.
				*/
				void Start()
				{
					//Initialize the Timer to clean slate.
					Stop();

					pm_isstarted = true;

					//Setting up the initial tick, so that we can take out
					//what it's storing after the Timer's been paused.
					pm_itick = SDL_GetTicks();

					printf("Timer::Start();\n");
				}

				/*
					Stops and it resets the number to 0.
					Do one thing no matter what; Stop.
				*/
				void Stop()
				{
					pm_isstarted = false;
					pm_ispause = false;
					pm_itick = 0;
					pm_etick = 0;

					printf("Timer::Stop();\n");
				}

				/*
					Pause the timer and the number stops being incremented.
					Do nothing when Timer is not started.
					Stop counting up the Timer when it has been started in the past.
				*/
				void Pause()
				{
					if (pm_isstarted &&
							//It disables client prompting Pause multiple times,
							//when Timer is paused.
							!pm_ispause)
					{
						pm_ispause = true;
						//pm_etick is accumulated as the number of calls to Pause increases.
						pm_etick += SDL_GetTicks() - pm_itick;

						printf("Timer::Pause();\n");
					}
				}

				/*
					Show the Timer.
					Show 0 when Timer is not started.
					Show GetTick() - initialtick when it's not paused.
					Show elapsedtick when it's paused.
				*/
				Uint32 Show()
				{
					if (pm_isstarted)
					{
						if (pm_ispause)
						{
							printf("Timer::Show() : (elapsed_tick)\n");
							return pm_etick;
						}
						else
						{
							printf("Timer::Show() : {elapsed_tick + (current_tick - init_tick)}\n");
							return pm_etick + SDL_GetTicks() - pm_itick;
						}
					}

					printf("Timer::Show() : 0\n");
					return 0;
				}

				/*
					Unpause the timer and number starts being incremented again.
					Do nothing when Timer is not started.
					Start counting the Timer again.
				*/
				void Unpause()
				{
					if (pm_isstarted && 
							//It disables client prompting Unpause multiple times,
							//when Timer is paused.
							pm_ispause)
					{
						pm_ispause = false;
						pm_itick = SDL_GetTicks();

						printf("Timer::Unpause();\n");
					}
				}
			
			private:
				friend KatoEngine::KatoEngine(const char* title, unsigned int scrwidth, unsigned int scrheight);
				Timer()
					: pm_ispause(false), pm_isstarted(false)
				{

				}

				bool pm_ispause;
				bool pm_isstarted;
				//Initial tick.
				Uint32 pm_itick;
				//Ticks elapsed 
				Uint32 pm_etick;
		};

		void Initialize()
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

		void PhysicsUpdate(float/* dt*/)
		{
			
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
		Timer pm_timer;
};

//Function signature for the main should be like this,
//so as to make it compatible with SDL.
int main(int, char*[])
{
	KatoEngine engine("Supreme Lord Yunhyeok", 800, 600);
	engine.Update();

	return 0;
}