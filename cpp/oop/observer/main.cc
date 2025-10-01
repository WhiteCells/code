#include "subject.h"
#include "observer_a.h"
#include "observer_b.h"

int main()
{
    auto sub = std::make_shared<Subject>();
    sub->attach(std::make_shared<ObserverA>());
    sub->attach(std::make_shared<ObserverB>());
    sub->notify();
    return 0;
}