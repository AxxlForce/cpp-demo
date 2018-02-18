#include "ServiceManager.h"
#include "../LoggingService/LoggingService.h"

using namespace std;

void ServiceManager::Startup()
{
    try
    {
        // first assure that there are no services already running
        this->Shutdown();

        // startup each registered service:
        // services have to be registered in correct order otherwise the application won't boot up
        for (ServiceMapIterator &pair : this->interfaceServiceMap)
        {
            pair.first->Startup();
        }
    }
    catch (const exception &e)
    {
        this->GetService<ILoggingService>()->ErrorWithInfo( e, "uncaught exception while starting up services" );
    }

    // log start of services
    this->GetService<ILoggingService>()->Info( "All registered services started!" );
}

string ServiceManager::GetServiceName( IService* service )
{
    // find service in map
    for (ServiceMapIterator &pair : this->interfaceServiceMap)
    {
        if (pair.first == service)
        {
            return this->FormatRuntimeTypeName( pair.second );
        }
    }

    return "NO_SERVICE_INFORMATION";
}

string ServiceManager::FormatRuntimeTypeName( string runtimeTypeName )
{
    // this is a bit of a hack/workaround:
    //
    // we take C++'s typeid(T).name() return value
    // and chop off everything but the interface name.
    // Unfortunately the return value is implementation
    // dependent so be aware that this might break on
    // different platforms or OS. Should be fine as we
    // only use it for logging purpose

    static const uint8_t PREFIX_LENGTH_OFFSET = 2;
    runtimeTypeName.erase( runtimeTypeName.begin(), runtimeTypeName.begin() + PREFIX_LENGTH_OFFSET );

    return runtimeTypeName;
}

void ServiceManager::RegisterDefaultServices()
{
    this->RegisterService<ILoggingService>( new LoggingService() );
}

void ServiceManager::ShutdownService( IService* service )
{
    // check if shutdown is necessary
    if (service != nullptr && service->IsStarted())
    {
        service->Shutdown();
    }
}

void ServiceManager::ShutdownAndDelete()
{
    this->GetService<ILoggingService>()->Info( "Shutting down all services..." );

    // reverse iterate over map: not pretty but works as expected
    for (reverse_iterator<_Rb_tree_iterator<ServiceMapIterator> > iter = this->interfaceServiceMap.rbegin(); iter != this->interfaceServiceMap.rend(); ++iter)
    {
        IService* service = iter->first;

        if (service != nullptr)
        {
            // perform service shutdown logic
            this->ShutdownService( service );

            // delete allocated service object
            delete service;
        }
    }

    this->interfaceServiceMap.clear();
}

void ServiceManager::Shutdown()
{
    // shutdown each service by iterating over map
    for (ServiceMapIterator &pair : this->interfaceServiceMap)
    {
        this->ShutdownService( pair.first );
    }
}