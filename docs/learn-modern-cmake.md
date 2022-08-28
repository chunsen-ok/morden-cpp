# Learn Modern CMake

cmake的几个阶段

- 配置时
- 构建时（可使用生成器表达式）
- 安装时（可使用生成器表达式）

- 配置时
- 为不支持cmake的第三方库提供find-module
- 通过BUILD_INTERFACE, INSTALL_INTERFACE，正确导出自己写的库接口

