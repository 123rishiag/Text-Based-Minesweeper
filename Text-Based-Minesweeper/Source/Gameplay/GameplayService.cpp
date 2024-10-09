#include "../../header/Gameplay/GameplayService.h"
#include "../../header/Gameplay/GameplayController.h"

namespace Gameplay
{
	GameplayService::GameplayService()
	{
		gameplay_controller = nullptr;
	}

	GameplayService::~GameplayService()
	{
		delete(gameplay_controller);
	}

	void GameplayService::initialize()
	{
		gameplay_controller = new GameplayController();
		gameplay_controller->initialize();
		startGame();
	}

	void GameplayService::update()
	{
		gameplay_controller->update();
	}

	void GameplayService::render()
	{
		gameplay_controller->render();
	}

	void GameplayService::startGame()
	{
		gameplay_controller->startGame();
	}

	void GameplayService::endGame(GameResult result)
	{
		gameplay_controller->endGame(result);
	}

	bool GameplayService::isGameOver() const
	{
		return gameplay_controller->isGameOver();
	}

	GameResult GameplayService::getGameResult() const
	{
		return gameplay_controller->getGameResult();
	}

	void GameplayService::destroy()
	{
		delete(gameplay_controller);
	}
}