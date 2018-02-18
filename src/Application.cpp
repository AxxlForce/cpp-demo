#include "Application.h"
#include "ServiceManager/ServiceManager.h"
#include "FilesystemInputOutputService/FilesystemInputOutputService.h"
#include "UdpTransceiverService/UdpTransceiverService.h"
#include <iostream>

using namespace std;

void Application::OnFrameReceived( char* data, uint32_t length, uint32_t ip, uint32_t port )
{
    string receivedMsg = string( data, length );

    ServiceManager::GetInstance().GetService<ILoggingService>()->Info( (string) "received via UDP loopback: \"" + receivedMsg + "\"" );

    // only to demonstrate further resource encapsulation...
    ServiceManager::GetInstance().GetService<IFilesystemInputOutputService>()->WriteLineToFile( receivedMsg );
}

void Application::Start()
{
    // register the services we're planing to use in our app
    ServiceManager::GetInstance().RegisterDefaultServices();
    ServiceManager::GetInstance().RegisterService<IFilesystemInputOutputService>( new FilesystemInputOutputService() );
    ServiceManager::GetInstance().RegisterService<IUdpTransceiverService>( new UdpTransceiverService() );

    // startup services in order to use them within main application logic
    ServiceManager::GetInstance().Startup();

    // kick off application logic main loop. when it returns the application's work is done.
    // this is the place for our last resort catch handler for the main thread
    try
    {
        this->Main();
    }
    catch (exception &e)
    {
        ServiceManager::GetInstance().GetService<ILoggingService>()->ErrorWithInfo( e, "uncaught exception occurred in main thread" );
    }

    // we're done: shutdown services for proper resource deallocation
    ServiceManager::GetInstance().ShutdownAndDelete();
}

void Application::Main()
{
    // register ourselves to receive incoming UDP data
    ServiceManager::GetInstance().GetService<IUdpTransceiverService>()->RegisterDelegate( this );

    // print some instructions for the user
    cout << endl << "type something to send via UDP loopback or type \"exit\" to terminate program" << endl;

    // main loop work
    while (true)
    {
        // read user input from console
        string userInput;
        getline( cin, userInput );

        // if "exit" command is given the work of the application is done
        if (userInput == "exit")
        {
            return;
        }

        // if there is valid user input send it via loopback
        if (userInput.empty() == false)
        {
            ServiceManager::GetInstance().GetService<IUdpTransceiverService>()->SendFrame( const_cast<char*>(userInput.c_str()), static_cast<uint32_t>(userInput.length()) );
        }
    }
}