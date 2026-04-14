#include <iostream>

class Acc;

class Call
{
public:
    Call(Acc &acc);

    void hangup();

private:
    Acc &m_acc;
};