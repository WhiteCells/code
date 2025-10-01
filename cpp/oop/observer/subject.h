#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "observer.h"
#include <vector>
#include <memory>

class Subject
{
public:
    void attach(std::shared_ptr<Observer> observer)
    {
        m_observer.push_back(observer);
    }

    void notify()
    {
        for (const auto &observer : m_observer) {
            observer->update();
        }
    }

private:
    std::vector<std::shared_ptr<Observer>> m_observer;
};

#endif // _SUBJECT_H_