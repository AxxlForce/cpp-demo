#ifndef APPLICATION_H
#define APPLICATION_H

#include "Interfaces/IUdpTransceiverService.h"
#include <cstdint>

class Application : IUdpDelegate
{
    public:

        void Start();

    private:

        /**
         * frame received handler (utilizes delegate pattern)
         */
        void OnFrameReceived( char* data, uint32_t length, uint32_t ip, uint32_t port ) override;

        /**
         * "endless" main working loop
         */
        void Main();
};

#endif