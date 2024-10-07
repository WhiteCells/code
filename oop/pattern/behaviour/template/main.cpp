#include "concrete_template.h"

int main(int argc, char *argv[]) {
    Template *template1 = new ConcreteTemplate1();
    template1->process();

    delete template1;

    Template *template2 = new ConcreteTemplate2();
    template2->process();

    delete template2;

    return 0;
}