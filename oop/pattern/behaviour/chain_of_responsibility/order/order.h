#ifndef _ORDER_H_
#define _ORDER_H_

class Order {
public:
    Order(int id, double amount);
    int getId() const;
    double getAmount() const;
    
private:
    int id_;
    double amount_;
};

#endif // _ORDER_H_