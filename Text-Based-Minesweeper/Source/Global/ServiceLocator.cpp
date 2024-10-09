#include "../../header/Global/ServiceLocator.h"
#include "../../header/Main/GameService.h"

namespace Global
{
	using namespace Time;
	using namespace Gameplay;
	using namespace Gameplay::Board;
	using namespace Main;

	ServiceLocator::ServiceLocator()
	{
		time_service = nullptr;
		gameplay_service = nullptr;
		board_service = nullptr;
		createServices();
	}

	ServiceLocator::~ServiceLocator() { clearAllServices(); }

	void ServiceLocator::createServices()
	{
		time_service = new TimeService();
		gameplay_service = new GameplayService();
		board_service = new BoardService();
	}

	void ServiceLocator::initialize()
	{
		time_service->initialize();
		gameplay_service->initialize();
		board_service->initialize();
	}

	void ServiceLocator::update()
	{
		time_service->update();
		if (GameService::getGameState() == GameState::GAMEPLAY)
		{
			gameplay_service->update();
			board_service->update();
		}
	}

	void ServiceLocator::render()
	{
		// no time_service to render
		if (GameService::getGameState() == GameState::GAMEPLAY)
		{
			gameplay_service->render();
			board_service->render();
		}
	}

	void ServiceLocator::clearAllServices()
	{
		delete(time_service);
		delete(gameplay_service);
		delete(board_service);
	}

	ServiceLocator* ServiceLocator::getInstance()
	{
		static ServiceLocator instance;
		return &instance;
	}

	TimeService* ServiceLocator::getTimeService() { return time_service; }
	GameplayService* ServiceLocator::getGameplayService() { return gameplay_service; }
	BoardService* ServiceLocator::getBoardService() { return board_service; }

	void ServiceLocator::deleteServiceLocator() { delete(this); }
}