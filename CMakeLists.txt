cmake_minimum_required(VERSION 3.20)
project(C_Web VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CEF_ROOT "${CMAKE_SOURCE_DIR}/cef_binary")

# --- Selezione dinamica cartella binari CEF ---
if(WIN32)
    set(CEF_BIN_OS "${CEF_ROOT}/win")

    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(CEF_BIN_OS "${CEF_BIN_OS}/x64")
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(CEF_BIN_OS "${CEF_BIN_OS}/x86")
    else()
        message(FATAL_ERROR "Architettura non riconosciuta su Windows")
    endif()
else()
    message(FATAL_ERROR "Sistema operativo non supportato: ${CMAKE_SYSTEM_NAME}")
endif()

message(STATUS "CEF_BIN_OS = ${CEF_BIN_OS}")
# ----------------------------------------------

# Opzione: EXE o DLL (default EXE)
option(BUILD_AS_DLL "Build as DLL instead of Win32 EXE" OFF)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

# Un unico target che cambia tipo in base a BUILD_AS_DLL
add_library(C_Web SHARED ${SOURCES})
if(NOT BUILD_AS_DLL)
    set_target_properties(C_Web PROPERTIES
        WIN32_EXECUTABLE TRUE
        OUTPUT_NAME "C_Web"
    )
else()
    target_compile_definitions(C_Web PRIVATE BUILD_DLL)
endif()

# Include della cartella include di CEF
target_include_directories(C_Web PRIVATE
    ${CEF_ROOT}
)

# Definizioni comuni
target_compile_definitions(C_Web PRIVATE 
    CEF_USE_DYNAMIC_LIB 
    UNICODE 
    _UNICODE
)

# Link con librerie CEF + librerie di sistema Windows
target_link_libraries(C_Web PRIVATE
    ${CEF_BIN_OS}/lib/libcef.lib
    ${CEF_BIN_OS}/lib/libcef_dll_wrapper.lib
    comctl32.lib
    shlwapi.lib
    rpcrt4.lib
)

# Copia dei DLL di CEF accanto all'output
add_custom_command(TARGET C_Web POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CEF_BIN_OS}/bin $<TARGET_FILE_DIR:C_Web>
)

# Copia della cartella Resources accanto all'output
add_custom_command(TARGET C_Web POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CEF_ROOT}/Resources $<TARGET_FILE_DIR:C_Web>
)

# Forza runtime /MT
if(MSVC)
    set_target_properties(C_Web PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreaded"
    )
    target_compile_definitions(C_Web PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
    )
endif()
