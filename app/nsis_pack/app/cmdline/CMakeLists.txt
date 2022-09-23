add_executable(cmdline main.cpp)

target_compile_features(cmdline PRIVATE cxx_std_17)

install(TARGETS cmdline DESTINATION "bin")

set(CPACK_PACKAGE_VENDOR "Lcs")
set(CPACK_PACKAGE_EXECUTABLES "cmdline;CmdLine")
set(CPACK_CREATE_DESKTOP_LINKS "CmdLine")
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
set(CPACK_NSIS_MUI_FINISHPAGE_RUN ON)
include(CPack)
