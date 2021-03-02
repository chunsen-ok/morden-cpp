// 策略模式
// 
#include <iostream>

class Result {};

class Strategy {
public:
    Result eval(int p1, int p2);
};

class Context {
public:
    void exec(int param) {
        if (0 == param) {
            // strategy 1
        } else {
            // strategy default
        }
    }
};

int main() {
    return 0;
}
