class X {
public:
    int a_;

protected:
    int b_;

private:
    int c_;
};

/**
 * public 继承
 * 派生类以 public 访问控制符继承基类
 * 基类 public    -> 派生类 public
 * 基类 protected -> 派生类 protected
 * 基类 private   -> 派生类 Unaccessible
 */
class A : public X {};

/**
 * protected 继承
 * 派生类以 protected 访问控制符继承基类
 * 基类 public    -> 派生类 protected
 * 基类 protected -> 派生类 protected
 * 基类 private   -> 派生类 Unaccessible
 */
class B : protected X {};

/**
 * private 继承
 * 派生类以 private 访问控制符继承基类
 * 基类 public    -> 派生类 private
 * 基类 protected -> 派生类 private
 * 基类 private   -> 派生类 Unaccessible
 *
 */
class C : private X {};

void test() {
    A a;
    a.a_;

    B b;
    // b.a_; // error

    C c;
    // c.a_; // error
}

int main() {
    return 0;
}