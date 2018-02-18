#ifndef IFILESYSTEMINPUTOUTPUTSERVICE_H
#define IFILESYSTEMINPUTOUTPUTSERVICE_H

#include "IService.h"
#include <string>

class IFilesystemInputOutputService : virtual public IService
{
    public:

        virtual ~IFilesystemInputOutputService() = default;

        virtual void WriteLineToFile( std::string msg ) = 0;
};

#endif