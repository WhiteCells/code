#ifndef _ROUND_H_
#define _ROUND_H_

class Round {
public:
    Round();
    virtual double getRadius() const;

private:
    double radius_;
};

#endif // _ROUND_H_