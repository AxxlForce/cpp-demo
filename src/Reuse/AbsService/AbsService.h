#ifndef ABSSERVICE_H
#define ABSSERVICE_H

#include "../../Interfaces/IService.h"

class AbsService : virtual IService
{
    public:

        AbsService();

        ~AbsService() override = default;

        void Startup() final;

        virtual void OnStartup();

        void Shutdown() final;

        virtual void OnShutdown();

        bool IsStarted() final;

    private:

        bool isStarted;
};

#endif