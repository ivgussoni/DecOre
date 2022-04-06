#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "GameEngine.h"
#include "Button.h"

int main()
{
	std::shared_ptr<GameEngine> GEngine = std::make_shared<GameEngine>();
	GEngine->Run();

	return 0;
}
