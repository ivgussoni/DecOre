#include "GameEngine.h"
#include "Button.h"

#define SDL_MAIN_HANDLED
#include "SDL.h"

int WinMain()
{
	std::shared_ptr<GameEngine> GEngine = std::make_shared<GameEngine>();
	GEngine->Run();

	return 0;
}
