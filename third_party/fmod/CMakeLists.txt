add_library(fmod SHARED IMPORTED GLOBAL)

message(STATUS "FMOD: Konfiguration wird geladen: ${CMAKE_BUILD_TYPE}")
message(STATUS "CURRENT PROJEKT DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

if (WIN32)
message(STATUS "FMOD: Windows-Konfiguration aktiv")
set_property(TARGET fmod PROPERTY
             IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/win/api/core/lib/x64/fmod.dll")
set_property(TARGET fmod PROPERTY
             IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/win/api/core/lib/x64/fmod_vc.lib")
set_property(TARGET fmod PROPERTY
             INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/win/api/core/inc")
elseif(LINUX)
message(STATUS "FMOD: Linux-Konfiguration aktiv")
set_property(TARGET fmod PROPERTY
             IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/linux/api/core/lib/x86_64/")
set_property(TARGET fmod PROPERTY
             INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/linux/api/core/inc")
set_property(TARGET fmod PROPERTY
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/linux/api/core/lib/x86_64/libfmod.so")
endif()

message(STATUS "FMOD: include dir: ${CMAKE_CURRENT_SOURCE_DIR}/win/api/core/inc")
message(STATUS "FMOD: lib dir: ${CMAKE_CURRENT_SOURCE_DIR}/win/api/core/lib/x64/")

set(fmod_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/win/api/core/inc" PARENT_SCOPE)