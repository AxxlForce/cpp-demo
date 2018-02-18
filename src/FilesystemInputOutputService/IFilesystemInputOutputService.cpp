#include "FilesystemInputOutputService.h"
#include <iostream>

using namespace std;

void FilesystemInputOutputService::OnStartup()
{
    // open file and keep it open as long as the service is started
    this->file.open( FilesystemInputOutputService::FILE_NAME );
}

void FilesystemInputOutputService::OnShutdown()
{
    // release our resource on shutdown
    this->file.close();
}

void FilesystemInputOutputService::WriteLineToFile( std::string msg )
{
    this->file << msg << endl;
}