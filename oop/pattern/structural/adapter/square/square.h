#ifndef _SQUARE_H_
#define _SQUARE_H_

class Square {
public:
    Square(double length);

    double getLength() const;

private:
    double length_;
};

#endif // _SQUARE_H_