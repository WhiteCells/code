#ifndef _SINGLETON_H_
#define _SINGLETON_H_

class Singleton {
public:
    static Singleton *getInstance();

private:
    Singleton() {}
    ~Singleton() {}

    static Singleton *instance_;

    class CleanUp;
    friend class CleanUp;

    class CleanUp {
    public:
        ~CleanUp() {
            if (Singleton::instance_) {
                delete Singleton::instance_;
                Singleton::instance_ = nullptr;
            }
        }
    };

    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
};

#endif // _SINGLETON_H_