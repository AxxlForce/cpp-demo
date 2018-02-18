#include "LoggingService.h"
#include "../ServiceManager/ServiceManager.h"
#include <iostream>

using namespace std;

void LoggingService::Info( string message )
{
    this->Log( message );
}

void LoggingService::InfoFromService( IService* service, string message )
{
    // compose info
    string log = "(" + ServiceManager::GetInstance().GetServiceName( service ) + ") " + message;

    this->Log( log );
}

void LoggingService::ErrorWithInfo( exception exception, string message )
{
    // compose info
    string log = (string) "(Exception message: " + exception.what() + ") " + message;

    this->Log( log );
}

void LoggingService::Log( string message )
{
    cout << message << endl;
}