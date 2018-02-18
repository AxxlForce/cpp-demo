#ifndef SINGLETON_H
#define SINGLETON_H

/**
 * basic singleton base class
 */
template<typename T>
class Singleton
{
    public:

        Singleton( Singleton const & ) = delete;

        Singleton &operator=( Singleton const & ) = delete;

        static T &GetInstance()
        {
            static T instance;
            return instance;
        }

    protected:

        Singleton() = default;

        ~Singleton() = default;
};

#endif