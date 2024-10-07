#ifndef _MEMENTO_H_
#define _MEMENTO_H_

#include <string>

class Memento {
public:
    Memento(std::string state);
    void setState(const std::string &state);
    std::string getState() const;
    
private:
    std::string state_;
};

#endif // _MEMENTO_H_