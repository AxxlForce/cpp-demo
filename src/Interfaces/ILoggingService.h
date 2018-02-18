#ifndef ILOGGINGSERVICE_H
#define ILOGGINGSERVICE_H

#include "IService.h"
#include <string>

class ILoggingService : virtual public IService
{
    public:

        virtual ~ILoggingService() = default;

        virtual void InfoFromService( IService* service, std::string message ) = 0;

        virtual void Info( std::string message ) = 0;

        virtual void ErrorWithInfo( std::exception, std::string message ) = 0;
};

#endif