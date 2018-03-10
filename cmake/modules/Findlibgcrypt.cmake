#.rst
# Findlibgcrypt
# -------------
# Find the libgcrypt cryptography library.
#
# IMPORTED Targets
# ^^^^^^^^^^^^^^^^
# This module defines the `IMPORTED` targets:
#
# ``libgcrypt::libgcrypt``
#  Defined if libgcrypt has been found.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
# This module sets the following variables:
#
# ``LIBGCRYPT_FOUND``
#   True if libgcrypt hsa been found.
#   If false, do not try to use libgcrypt.
#
# ``libgcrypt_INCLUDE_DIR``
#   The directory containing libgcrypt headers.
#
# ``libgcrypt_LIBRARY``
#   The libraries needed to use libgcrypt.
#


find_path(libgcrypt_INCLUDE_DIR
    NAMES gcrypt.h
    DOC "The libgcrypt include directory"
)
mark_as_advanced(libgcrypt_INCLUDE_DIR)

find_library(libgcrypt_LIBRARY
    NAMES gcrypt
    DOC "The libgcrypt library"
)
mark_as_advanced(libgcrypt_LIBRARY)

# libgcrypt-config is an executable that provides information about the libgcrypt build and installation.
# It can be run with options such as:
#   --version
#   --libs
#   --cflags
#   --prefix
find_program(libgcrypt_CONFIG_EXECUTABLE
    NAMES libgcrypt-config
    DOC "The libgcrypt configuration executable. Provides libgcrypt package information."
)

if(libgcrypt_CONFIG_EXECUTABLE)
    execute_process(COMMAND ${libgcrypt_CONFIG_EXECUTABLE} --version
        OUTPUT_VARIABLE libgcrypt_VERSION
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()
unset(libgcrypt_CONFIG_EXECUTABLE)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(libgcrypt
    REQUIRED_VARS libgcrypt_LIBRARY libgcrypt_INCLUDE_DIR
    VERSION_VAR libgcrypt_VERSION
)

if(LIBGCRYPT_FOUND AND NOT TARGET libgcrypt::libgcrypt)
    add_library(libgcrypt::libgcrypt UNKNOWN IMPORTED)
    set_target_properties(libgcrypt::libgcrypt PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${libgcrypt_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${libgcrypt_INCLUDE_DIR}"
    )
endif()
