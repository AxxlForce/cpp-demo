#ifndef UDPTRANSCEIVERSERVICE_H
#define UDPTRANSCEIVERSERVICE_H

#include "../Interfaces/IUdpTransceiverService.h"
#include "../Reuse/AbsService/AbsService.h"
#include <thread>

/**
 * this is a very basic UDP (loopback) transceiver which encapsulates non OOP POSIX calls. It's far from complete
 * and just an example of how resources can be encapsulated
 */
class UdpTransceiverService : public IUdpTransceiverService, AbsService
{
    public:

        UdpTransceiverService();

        void RegisterDelegate( IUdpDelegate* delegate ) override;

        void SendFrame( char* data, uint32_t length ) override;

    private:

        static const int UDP_PORT = 0x1337;
        static const int MAX_BUFFER_SIZE = 1400;

        IUdpDelegate* delegate;
        std::thread* receivingThread;
        int socketHandleUdp;
        char dataUDP[MAX_BUFFER_SIZE];

        /**
         * create POSIX socket to receive data from loopback and spawns receiver thread
         */
        void OnStartup() override;

        /**
         * close POSIX receive socket and join receiver thread
         */
        void OnShutdown() override;

        /**
         * loop receives from socket within receiver thread
         */
        void ReceiverLoop();
};

#endif