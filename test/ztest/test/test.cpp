#include <iostream>
#include <string>

class Person {
public:
    Person(std::string name, std::string sex)
        : name_(name), sex_(sex) {}
    std::string getName() const {
        return name_;
    }
    void setName(std::string name) {
        name_ = name;
    }
    virtual void info() const {
        std::cout << name_ << " " << sex_ << std::endl;
    }
protected:
    std::string name_;
    std::string sex_;
};

class US : public Person {
public:
    US(std::string name, std::string sex)
        : Person(name, sex) {}
    virtual void info() const {
        std::cout << "---" <<  name_ << " " << sex_ << std::endl;
    }
};

class CH : public Person {
public:
    CH(std::string name, std::string sex) : Person(name, sex) {}
};

int main(int argc, char *argv[]) {
    Person *us = new US("alice", "famale");
    std::cout << us->getName() << std::endl;
    Person *ch = new CH("petter", "male");
    std::cout << ch->getName() << std::endl;
    std::cout << us->getName() << std::endl;
    us->info();
    ch->info();
    return 0;
}