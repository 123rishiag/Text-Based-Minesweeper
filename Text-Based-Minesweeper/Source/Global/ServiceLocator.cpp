#include "../../header/Global/ServiceLocator.h"
#include "../../header/Main/GameService.h"

namespace Global
{
	using namespace Time;
	using namespace Main;

	ServiceLocator::ServiceLocator()
	{
		time_service = nullptr;

		createServices();
	}

	ServiceLocator::~ServiceLocator() { clearAllServices(); }

	void ServiceLocator::createServices()
	{
		time_service = new TimeService();
	}

	void ServiceLocator::initialize()
	{
		time_service->initialize();
	}

	void ServiceLocator::update()
	{
		time_service->update();
	}

	void ServiceLocator::render()
	{
		// no time_service to render
	}

	void ServiceLocator::clearAllServices()
	{
		delete(time_service);
	}

	ServiceLocator* ServiceLocator::getInstance()
	{
		static ServiceLocator instance;
		return &instance;
	}

	TimeService* ServiceLocator::getTimeService() { return time_service; }

	void ServiceLocator::deleteServiceLocator() { delete(this); }
}