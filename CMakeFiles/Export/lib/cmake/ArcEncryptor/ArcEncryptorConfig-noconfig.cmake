#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ArcEncryptor::arc-encryptor-lib" for configuration ""
set_property(TARGET ArcEncryptor::arc-encryptor-lib APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ArcEncryptor::arc-encryptor-lib PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libarc-encryptor-lib.so"
  IMPORTED_SONAME_NOCONFIG "libarc-encryptor-lib.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS ArcEncryptor::arc-encryptor-lib )
list(APPEND _IMPORT_CHECK_FILES_FOR_ArcEncryptor::arc-encryptor-lib "${_IMPORT_PREFIX}/lib/libarc-encryptor-lib.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
