//! https://my.oschina.net/u/5447363/blog/5460840

#include <iostream>

namespace app_core {

    //! entity, value object, basic entity logic
    namespace domain_model {

    }

    //! 涉及多个实体的领域逻辑
    namespace domain_service {

    }

    //! 业务逻辑
    //! 应用的入口和出口，各种需要的接口，供外部实现
    namespace app_service {

        //! 各种对外部系统提供的可扩展接口
        namespace interface {}
    }
}

namespace ui {
    namespace vmodel {}
    namespace controller {}
    
    namespace cli {}
    namespace web_ui {}
    namespace dashboard {}
}

namespace infras {

    namespace database {

    }

    namespace local_storage {

    }

    namespace web_service {

    }

}

namespace tests {

}

int main(int argc, char *argv[])
{
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
