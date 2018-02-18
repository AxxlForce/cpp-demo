#include "UdpTransceiverService.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

using namespace std;

UdpTransceiverService::UdpTransceiverService() : delegate( nullptr )
{
}

void UdpTransceiverService::RegisterDelegate( IUdpDelegate* delegate )
{
    this->delegate = delegate;
}

void UdpTransceiverService::SendFrame( char* data, uint32_t length )
{
    // POSIX socket configuration in order to send UDP data
    struct sockaddr_in address{};
    memset( &address, 0, sizeof( address ) );
    address.sin_family = AF_INET;
    address.sin_port = htons( UdpTransceiverService::UDP_PORT );
    address.sin_addr.s_addr = htonl( INADDR_LOOPBACK );

    ssize_t returnValue = sendto( this->socketHandleUdp, data, length, MSG_DONTWAIT, (struct sockaddr*) &address, sizeof( address ) );

    // return value processing
    if (returnValue != length || returnValue == 0)
    {
        throw runtime_error( (string) "error sending UDP data: " + strerror( errno ) );
    }
}

void UdpTransceiverService::OnStartup()
{
    // POSIX socket configuration in order to receive UDP data
    socketHandleUdp = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
    struct sockaddr_in address{};
    memset( &address, 0, sizeof( address ) );
    address.sin_family = AF_INET;
    address.sin_port = htons( UdpTransceiverService::UDP_PORT );
    bind( socketHandleUdp, (struct sockaddr*) &address, sizeof( address ) );

    // spawn receiving thread
    this->receivingThread = new thread( &UdpTransceiverService::ReceiverLoop, this );
}

void UdpTransceiverService::OnShutdown()
{
    // join our receiving thread and delete object
    this->receivingThread->join();
    delete this->receivingThread;
    this->receivingThread = nullptr;

    // properly close socket by reconfiguring socket
    const int optVal = 1;
    const socklen_t optLen = sizeof( optVal );
    setsockopt( this->socketHandleUdp, SOL_SOCKET, SO_REUSEADDR, (void*) &optVal, optLen );
}

void UdpTransceiverService::ReceiverLoop()
{
    while (this->IsStarted() == true)
    {
        struct sockaddr_in address{};
        unsigned int addressLength = sizeof( address );

        // actual receive call
        ssize_t dataUdpLength = recvfrom( this->socketHandleUdp, this->dataUDP, UdpTransceiverService::MAX_BUFFER_SIZE, MSG_DONTWAIT, (struct sockaddr*) &address, &addressLength );

        // return value processing
        if (dataUdpLength > 0) // we got valid data: pass further if delegate registered
        {
            if (this->delegate != nullptr)
            {
                this->delegate->OnFrameReceived( this->dataUDP, static_cast<uint32_t>(dataUdpLength), address.sin_addr.s_addr, address.sin_port );
            }
        }

        memset( this->dataUDP, 0, sizeof( this->dataUDP ) );

        // usually we'd find a more elegant and more complete way to receive UDP data but this is not subject to this demonstration and we want to keep it simple
        usleep( 1000 );
    }
}