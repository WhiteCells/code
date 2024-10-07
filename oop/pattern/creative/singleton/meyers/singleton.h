#ifndef _SINGLETON_H_
#define _SINGLETON_H_

class Singleton {
public:
    static Singleton *getInstance();

private:
    Singleton() {}
    ~Singleton() {}

    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
};

#endif // _SINGLETON_H_