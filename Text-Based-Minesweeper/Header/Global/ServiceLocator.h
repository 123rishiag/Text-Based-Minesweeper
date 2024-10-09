#pragma once
#include "../../header/Time/TimeService.h"

namespace Global
{
    class ServiceLocator
    {
    private:
        Time::TimeService* time_service;

        ServiceLocator();
        ~ServiceLocator();

        void createServices();
        void clearAllServices();

    public:
        static ServiceLocator* getInstance();

        void initialize();
        void update();
        void render();

        Time::TimeService* getTimeService();

        void deleteServiceLocator();
    };
}