#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

class Template {
public:
    virtual ~Template() {}
    void process() {
        operateA();
        operateB();
    }

protected:
    virtual void operateA() = 0;
    virtual void operateB() = 0;
};

#endif // _TEMPLATE_H_