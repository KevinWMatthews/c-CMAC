add_library(ByteArrayOps
    "${CMAKE_HOME_DIRECTORY}/src/BitOperation.c"
)
# Not sure about including the src/ directory...
target_include_directories(ByteArrayOps
    PUBLIC
        "${CMAKE_HOME_DIRECTORY}/src"
)
target_compile_options(ByteArrayOps
    PRIVATE
        "-Wall"
)
add_library(ByteArrayOpsLib::ByteArrayOpsLib ALIAS ByteArrayOps)

#TODO this needs to link against libgcrypt
add_library(CmacOps
    "${CMAKE_HOME_DIRECTORY}/src/CmacAesOps.h"
    "${CMAKE_HOME_DIRECTORY}/src/CmacAesOps.c"
    "${CMAKE_HOME_DIRECTORY}/src/CmacAesSubkeys.h"
    "${CMAKE_HOME_DIRECTORY}/src/CmacAesSubkeys.c"
)
# PUBLIC or PRIVATE?
target_include_directories(CmacOps
    PUBLIC
        "${CMAKE_HOME_DIRECTORY}/src"
)
target_link_libraries(CmacOps
    PUBLIC
        Aes128::Aes128
    PRIVATE
        ByteArrayOpsLib::ByteArrayOpsLib
)
target_compile_options(CmacOps
    PRIVATE
        "-Wall"
)
if(COMPILE_TESTS)
    target_include_directories(CmacOps
        PUBLIC
            "${CMAKE_HOME_DIRECTORY}/mocks"
    )
endif()
add_library(CmacOpsLib::CmacOpsLib ALIAS CmacOps)


add_library(Cmac
    "${CMAKE_HOME_DIRECTORY}/include/CmacAes.h"
    "${CMAKE_HOME_DIRECTORY}/src/CmacAes.c"
)
target_include_directories(Cmac
    PUBLIC
        "${CMAKE_HOME_DIRECTORY}/include"
)
target_link_libraries(Cmac
    CmacOpsLib::CmacOpsLib
)
target_compile_options(Cmac
    PRIVATE
        "-Wall"
)
if(COMPILE_TESTS)
    target_include_directories(Cmac
        PUBLIC
            "${CMAKE_HOME_DIRECTORY}/mocks"
    )
endif()
add_library(CmacLib::CmacLib ALIAS Cmac)
