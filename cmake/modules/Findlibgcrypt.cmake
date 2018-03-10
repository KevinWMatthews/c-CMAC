




# libgcrypt does not ship with pkgconfig or CMake support.
# Instead, it provides a custom executable, libgcrypt-config.
# This execytabke knows all of libgcrypt's installation details ships in the bin/ directory.
# It is detailed in the libgcrypt documentation.
#
# You can run libgcrypt-config with options such as:
#   --libs
#   --cflags
#   --prefix


# find_program(LIBGCRYPT_CONFIG_EXECUTABLE libgcrypt-config
    # DOC "libgcrypt-config executable. Contains libgcrypt package information (instead of pkgconfig)."
# )

# if(NOT LIBGCRYPT_CONFIG_EXECUTABLE)
#     message(FATAL_ERROR "libgcrypt-config not found in LIBGCRYPT_HOME: ${LIBGCRYPT_HOME}")
# endif()

# execute_process(
#     COMMAND ${LIBGCRYPT_CONFIG_EXECUTABLE} --libs
#     RESULT_VARIABLE LIBGCRYPT_CONFIG_ERROR
#     OUTPUT_VARIABLE LIBGCRYPT_LIBS
#     OUTPUT_STRIP_TRAILING_WHITESPACE
# )

# if(LIBGCRYPT_CONFIG_ERROR)
#     message(FATAL_ERROR "${LIBGCRYPT_CONFIG_EXECUTABLE} failed")
# endif()

mark_as_advanced(LIBGCRYPT_CONFIG_EXECUTABLE)
