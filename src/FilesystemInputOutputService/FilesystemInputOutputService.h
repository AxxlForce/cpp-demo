#ifndef FILESYSTEMINPUTOUTPUTSERVICE_H
#define FILESYSTEMINPUTOUTPUTSERVICE_H

#include "../Interfaces/IService.h"
#include "../Interfaces/IFilesystemInputOutputService.h"
#include "../Reuse/AbsService/AbsService.h"
#include <string>
#include <fstream>

class FilesystemInputOutputService : public IFilesystemInputOutputService, AbsService
{
    public:

        void OnStartup() override;

        void OnShutdown() override;

        void WriteLineToFile( std::string msg ) override;

    private:

        static constexpr const char* FILE_NAME = "myFile.txt";
        std::ofstream file;
};

#endif
