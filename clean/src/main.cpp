//! https://my.oschina.net/u/5447363/blog/5460840
//!
//! clean/
//! |- core
//! |  |- service
//! |- ui
//! |  |- cli
//! |  |- gui
//! |  |- ...
//! |- infras
//! |   |- db
//! |   |- disk
//! |   |- web service
//! |- tests
//!
//! 不同 data 中存在相同 role 时，如何处理？（实现时应当避免这种情况出现，即使真的需要相同的role，也应该近一步区分它们（比如通过数据中携带ID），使之唯一。）
//! 

#include <iostream>
#include "actions.hpp"

namespace view {}
namespace vmodel {}
namespace service {

    class AppService
    {
    public:
        
    };

}
namespace infras {}

int main(int argc, char *argv[])
{
    return 0;
}
