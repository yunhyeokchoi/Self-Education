#include <SDL.h>
//For printf, since we don't have any debug tools which can break the program atm.
#include <stdio.h>
//This is where all the pointers to image files will be stored.
#include <list>
#if defined(_DEBUG)
#include <crtdbg.h>
#endif
//#define TIMER_TEST

//Function signature for the main should be like this,
//so as to make it compatible with SDL.
int main(int, char*[])
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	KatoEngine engine("Supreme Lord Yunhyeok", 800, 600);
	engine.Update();

	return 0;
}