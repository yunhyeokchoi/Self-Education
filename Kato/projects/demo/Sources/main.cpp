
#include "Engine.h"
//Following should be included, since contents in SampleEngine.lib is built based on SDL.
#include <SDL.h>

#include "DebugTools.h"

//#if defined(_DEBUG)
//#include <crtdbg.h>
//#endif
//#define TIMER_TEST

//Function signature for the main should be like this,
//so as to make it compatible with SDL.
int main(int argc, char* args[])
{
  argc;
  args;
  DEBUG_CREATE_CONSOLE();

	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	KatoEngine::Engine engine("Supreme Lord Yunhyeok", 800, 600, args[0]);
	engine.Update();

  DEBUG_DESTROY_CONSOLE();

	return 0;
}