#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include "../Interfaces/ILoggingService.h"
#include "../Reuse/Singleton/Singleton.h"
#include <typeinfo>
#include <map>

/**
 * The ServiceManager provides a minimal application framework. All code that is interacting with resources should
 * be encapsulated in services to control their states and life cycles. It is also meant to encapsulate C style
 * code which might be neccessary to use resources and thus providing proper OOP APIs to the rest of the application
 *
 * Every service is defined by an interface (e.g. ILoggingService) so that implementations of services can be switched
 * easily. This also facilitates creating mock services and unit testing
 *
 * Important: ServiceManager should be the only singleton we'll use in our code base.
 */
class ServiceManager : public Singleton<ServiceManager>
{
    public:

        /**
        * registers the default services which are critical to run the actual application (e.g. LoggingService)
        */
        void RegisterDefaultServices();

        /**
         * starts all registered services
         */
        void Startup();

        /**
         * shuts down all services and deallocates their objects
         *
         * TODO is missing proper error handling
         */
        void ShutdownAndDelete();

        /**
        * gets the name of a service according to its interface
        */
        std::string GetServiceName( IService* service );

        /**
         * registers a service. If there's already a service registered with the given interface,
         * throw an exception
         *
         * INFO: this template method has to be implemented "in-line" to satisfy compiler
         */
        template<typename T>
        void RegisterService( IService* service )
        {
            // find service in interfaceServiceMapping list
            for (ServiceMapIterator &pair : interfaceServiceMap)
            {
                if (pair.second == (std::string) typeid( T ).name())
                {
                    throw std::runtime_error( "service with interface \"" + this->FormatRuntimeTypeName( typeid( T ).name() ) + "\" is already registered!" );
                }
            }

            // Register the given interface for the specified service implementation
            ServiceMapPair pair = ServiceMapPair( service, (std::string) typeid( T ).name() );
            interfaceServiceMap.insert( pair );
        }

        /**
         * gets the pointer to the service with the given interface
         *
         * INFO: this template method has to be implemented "in-line" to satisfy compiler
         */
        template<typename T>
        T* GetService()
        {
            for (ServiceMapIterator &pair : interfaceServiceMap)
            {
                std::string &serviceName = pair.second;

                if (serviceName == (std::string) typeid( T ).name())
                {
                    // cast to correct type
                    IService* service = pair.first;
                    return dynamic_cast<T*>(service);
                }
            }

            // couldn't find service...
            throw std::runtime_error( "service not found: \"" + this->FormatRuntimeTypeName( typeid( T ).name() ) + "\"" );
        }

    private:

        // define types in order to improve readability
        typedef std::pair<IService*, std::string> ServiceMapPair;
        typedef std::pair<IService* const, std::string> ServiceMapIterator;

        std::map<IService*, std::string> interfaceServiceMap;

        /**
         * shuts down all services, the instances however remain an can be restarted
         */
        void Shutdown();

        /**
         * shuts down a specific service
         */
        void ShutdownService( IService* service );

        /**
         * parses c++ runtime type name
         */
        static std::string FormatRuntimeTypeName( std::string runtimeTypeName );
};

#endif