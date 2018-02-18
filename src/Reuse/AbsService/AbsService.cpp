#include "AbsService.h"
#include "../../Interfaces/ILoggingService.h"
#include "../../ServiceManager/ServiceManager.h"

AbsService::AbsService() : isStarted( false )
{
}

void AbsService::Startup()
{
    if (this->isStarted == false)
    {
        this->OnStartup();
        this->isStarted = true;
        ServiceManager::GetInstance().GetService<ILoggingService>()->InfoFromService( this, "started!" );
    }
}

void AbsService::OnStartup()
{
}

void AbsService::Shutdown()
{
    if (this->isStarted == true)
    {
        this->isStarted = false;
        this->OnShutdown();
        ServiceManager::GetInstance().GetService<ILoggingService>()->InfoFromService( this, "stopped!" );
    }
}

void AbsService::OnShutdown()
{
}

bool AbsService::IsStarted()
{
    return this->isStarted;
}