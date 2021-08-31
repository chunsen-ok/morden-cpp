// 折叠表达式：通过二元操作符规约（reduce）参数包
// 一元右折叠 (pack op ...)，即从参数包右侧开始执行 op 的计算。
// 一元左折叠 (... op pack)，与一元右折叠相反。
// 二元右折叠 (pack op ... op init)，从右侧开始，根据提供初始值开始。
// 二元左折叠 (init op ... op pack)，与二元右折叠方向相反。
//
#include <iostream>

template<typename... Args>
int sum(Args... args) {
    return (... + args);
}

int main() {
    std::cout << sum(1,2,3,4,5,6,7,8,9) << std::endl;
    return 0;
}
