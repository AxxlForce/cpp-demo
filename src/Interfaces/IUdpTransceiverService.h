#ifndef IUDPTRANSCEIVERSERVICE_H
#define IUDPTRANSCEIVERSERVICE_H

#include "IService.h"
#include <cstdint>

class IUdpDelegate
{
    public:

        virtual ~IUdpDelegate() = default;

        /**
         * receive event handler
         */
        virtual void OnFrameReceived( char* data, uint32_t length, uint32_t ip, uint32_t port ) = 0;
};

class IUdpTransceiverService : virtual public IService
{
    public:

        virtual ~IUdpTransceiverService() = default;

        /**
         * send a UDP frame
         */
        virtual void SendFrame( char* data, uint32_t length ) = 0;

        /**
         * register delegate object that wants to process the received UDP data
         */
        virtual void RegisterDelegate( IUdpDelegate* delegate ) = 0;
};

#endif