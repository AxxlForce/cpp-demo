#ifndef LOGGINGSERVICE_H
#define LOGGINGSERVICE_H

#include "../Interfaces/ILoggingService.h"
#include "../Reuse/AbsService/AbsService.h"

class LoggingService : public ILoggingService, AbsService
{
    public:

        void Info( std::string message ) override;

        void InfoFromService( IService* service, std::string message ) override;

        void ErrorWithInfo( std::exception exception, std::string message ) override;

    private :

        void Log( std::string message );
};

#endif