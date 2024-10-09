#include "../../header/Global/ServiceLocator.h"
#include "../../header/Main/GameService.h"

namespace Global
{
	using namespace Gameplay::Board;
	using namespace Gameplay;
	using namespace Main;

	ServiceLocator::ServiceLocator()
	{
		board_service = nullptr;
		gameplay_service = nullptr;
		createServices();
	}

	ServiceLocator::~ServiceLocator() { clearAllServices(); }

	void ServiceLocator::createServices()
	{
		board_service = new BoardService();
		gameplay_service = new GameplayService();
	}

	void ServiceLocator::initialize()
	{
		board_service->initialize();
		gameplay_service->initialize();
	}

	void ServiceLocator::update()
	{
		if (GameService::getGameState() == GameState::GAMEPLAY)
		{
			board_service->update();
			gameplay_service->update();
		}
	}

	void ServiceLocator::render()
	{
		if (GameService::getGameState() == GameState::GAMEPLAY)
		{
			board_service->render();
			gameplay_service->render();
		}
	}

	void ServiceLocator::clearAllServices()
	{
		delete(board_service);
		delete(gameplay_service);
	}

	ServiceLocator* ServiceLocator::getInstance()
	{
		static ServiceLocator instance;
		return &instance;
	}

	BoardService* ServiceLocator::getBoardService() { return board_service; }
	GameplayService* ServiceLocator::getGameplayService() { return gameplay_service; }

	void ServiceLocator::deleteServiceLocator() { delete(this); }
}