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

add_executable(C_Web WIN32 src/main.cpp)

# Include della cartella include di CEF
target_include_directories(C_Web PRIVATE
    ${CEF_ROOT}
)

# Definizione per usare DLL dinamica
target_compile_definitions(C_Web PRIVATE CEF_USE_DYNAMIC_LIB)

# Link con librerie CEF + librerie di sistema Windows
target_link_libraries(C_Web PRIVATE
    ${CEF_BIN_OS}/lib/libcef.lib
    ${CEF_BIN_OS}/lib/libcef_dll_wrapper.lib
    comctl32.lib
    shlwapi.lib
    rpcrt4.lib
)

# Copia dei DLL di CEF accanto all'eseguibile
add_custom_command(TARGET C_Web POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CEF_BIN_OS}/bin $<TARGET_FILE_DIR:C_Web>
)

# Copia della cartella Resources accanto all'eseguibile
add_custom_command(TARGET C_Web POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CEF_ROOT}/Resources $<TARGET_FILE_DIR:C_Web>
)

# Forza runtime /MT per tutte le configurazioni (Debug e Release)
if(MSVC)
    set_target_properties(C_Web PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreaded"
    )
endif()
