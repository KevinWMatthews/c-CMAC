add_library(ByteArrayOps
    "${CMAKE_HOME_DIRECTORY}/src/BitOperation.c"
)
# Not sure about including the src/ directory...
target_include_directories(ByteArrayOps
    PUBLIC
        "${CMAKE_HOME_DIRECTORY}/src"
)
add_library(ByteArrayOpsLib::ByteArrayOpsLib ALIAS ByteArrayOps)


add_library(CmacOps
    "${CMAKE_HOME_DIRECTORY}/src/CmacOps.h"
    "${CMAKE_HOME_DIRECTORY}/src/CmacOps.c"
    "${CMAKE_HOME_DIRECTORY}/src/AesCmacSubkeys.h"
    "${CMAKE_HOME_DIRECTORY}/src/AesCmacSubkeys.c"
)
target_include_directories(CmacOps
    PUBLIC
        "${CMAKE_HOME_DIRECTORY}/src"
)
target_link_libraries(CmacOps
    PRIVATE
        ByteArrayOpsLib::ByteArrayOpsLib
)
if(COMPILE_TESTS)
    target_include_directories(CmacOps
        PUBLIC
            "${CMAKE_HOME_DIRECTORY}/mocks"
    )
endif()
add_library(CmacOpsLib::CmacOpsLib ALIAS CmacOps)


add_library(Cmac
    "${CMAKE_HOME_DIRECTORY}/include/AesCmac.h"
    "${CMAKE_HOME_DIRECTORY}/src/AesCmac.c"
)
target_include_directories(Cmac
    PUBLIC
        "${CMAKE_HOME_DIRECTORY}/include"
)
target_link_libraries(Cmac
    CmacOpsLib::CmacOpsLib
)
if(COMPILE_TESTS)
    target_include_directories(Cmac
        PUBLIC
            "${CMAKE_HOME_DIRECTORY}/mocks"
    )
endif()
add_library(CmacLib::CmacLib ALIAS Cmac)
