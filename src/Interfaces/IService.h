#ifndef ISERVICE_H
#define ISERVICE_H

class IService
{
    public:

        virtual ~IService() = default;

        virtual bool IsStarted() = 0;

        virtual void Startup() = 0;

        virtual void Shutdown() = 0;
};

#endif