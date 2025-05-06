int x = 1;

int getVal() {
    return x;
}

void setVal(int a) {
    &a;
    x = a;
}

int main() {
    &++x;
    // &x++; // compilation failed

    int y = getVal();
    // &getVal(); // compilation failed

    setVal(2);
    // &setVal(2); // compilation failed

    const char(*p)[] = &"hello";
    return 0;
}