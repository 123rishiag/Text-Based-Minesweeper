#include "../../header/Main/GameService.h"

namespace Main
{
	using namespace Global;

	GameState GameService::current_state = GameState::BOOT;

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
		startGameplay();
	}

	void GameService::startGameplay()
	{
		setGameState(GameState::GAMEPLAY);
	}

	void GameService::update()
	{
		service_locator->update();
	}

	void GameService::render()
	{
		service_locator->render();
	}

	bool GameService::isRunning() { return !service_locator->getInstance()->getGameplayService()->isGameOver(); }

	void GameService::setGameState(GameState new_state)
	{
		current_state = new_state;
	}

	GameState GameService::getGameState()
	{
		return current_state;
	}

	void GameService::destroy()
	{
		service_locator->deleteServiceLocator();
	}
}