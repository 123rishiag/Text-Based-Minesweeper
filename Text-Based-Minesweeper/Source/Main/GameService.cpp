#include "../../header/Main/GameService.h"

namespace Main
{
	using namespace Global;

	GameService::GameService()
	{
		service_locator = nullptr;
	}

	GameService::~GameService()
	{
		destroy();
	}

	void GameService::ignite()
	{
		service_locator = ServiceLocator::getInstance();
		initialize();
	}

	void GameService::initialize()
	{
		service_locator->initialize();
	}

	void GameService::update()
	{
		service_locator->update();
	}

	void GameService::render()
	{
		service_locator->render();
	}

	bool GameService::isRunning() { return true; }

	void GameService::destroy()
	{
		service_locator->deleteServiceLocator();
	}
}