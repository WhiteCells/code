#include "concrete_observer.h"
#include "concrete_subject.h"

int main(int argc, char *argv[]) {
    Subject *subject = new ConcreteSubject();
    Observer *observer1 = new ConcreteObserver();
    Observer *observer2 = new ConcreteObserver();
    Observer *observer3 = new ConcreteObserver();
    subject->attach(observer1);
    subject->attach(observer2);
    subject->attach(observer3);

    // subject->detach(observer2);
    dynamic_cast<ConcreteSubject *>(subject)->stateChanged();

    delete subject;
    return 0;
}