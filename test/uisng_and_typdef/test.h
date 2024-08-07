#ifndef _TEST_H_
#define _TEST_H_

class A {
    using ll1 = long long;
    typedef long long ll2;
    ll1 foo(ll1);
    ll2 foo(ll2);
};

A::ll1 A::foo(ll1) {

}

A::ll2 A::foo(ll2) {
    
}

#endif // _TEST_H_