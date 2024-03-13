# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.25.0)

# Configuration spécifique à chaque système d'exploitation
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Définir la version du système pour cibler Windows Vista est supérieur
    set(CMAKE_SYSTEM_VERSION 6.0)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # Configurations spécifiques à macOS
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Architectures macOS" FORCE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0" CACHE STRING "macOS Deployment Target")
elseif(CMAKE_SYSTEM_NAME STREQUAL "iOS")
    # Configurations spécifiques à iOS
    if(CMAKE_OSX_SYSROOT MATCHES "iphoneos")
        set(CMAKE_OSX_ARCHITECTURES "arm64;arm64e;" CACHE STRING "Architectures iOS" FORCE)
    elseif(CMAKE_OSX_SYSROOT MATCHES "iphonesimulator")
        set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Architectures iOS" FORCE)
    endif()
  
    set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0" CACHE STRING "iOS Deployment Target")
endif()

project(rcenet)

# Require Compiler C
set(CMAKE_C_STANDARD_REQUIRED True)

# Configuration des drapeaux du compilateur
if(CMAKE_SYSTEM_NAME STREQUAL "Windows") # Windows
    # /W3 : Niveau d'avertissement 3 (equivalent a -Wall en C)
    # /W4 : Niveau d'avertissement 4 (equivalent a -Wextra en C)
    # /permissive- : Bien que principalement un drapeau C++, peut aider à identifier des constructions ambigues
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3 /W4 /permissive-")
else() # Unix
    # -Wall : Active tous les avertissements de base
    # -Wextra : Active des avertissements supplémentaires
    # -pedantic : Enforce strictement les standards C
    # -Wno-newline-eof : Désactive les avertissements pour les nouvelles lignes à la fin du fichier
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wno-newline-eof")
endif()

# Ajouter les fichiers sources de RCEnet
file(GLOB_RECURSE SOURCES 
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

# Créer une bibliothèque static
add_library(${PROJECT_NAME} 
    STATIC 
    ${SOURCES}
)

# Vérifications des fonctionnalités systèmes et définitions conditionnelles
include(CheckFunctionExists)
include(CheckStructHasMember)
include(CheckTypeSize)

check_function_exists("fcntl" HAS_FCNTL)
check_function_exists("poll" HAS_POLL)
check_function_exists("getaddrinfo" HAS_GETADDRINFO)
check_function_exists("getnameinfo" HAS_GETNAMEINFO)
check_function_exists("gethostbyname_r" HAS_GETHOSTBYNAME_R)
check_function_exists("gethostbyaddr_r" HAS_GETHOSTBYADDR_R)
check_function_exists("inet_pton" HAS_INET_PTON)
check_function_exists("inet_ntop" HAS_INET_NTOP)
check_struct_has_member("struct msghdr" "msg_flags" "sys/types.h;sys/socket.h" HAS_MSGHDR_FLAGS)
set(CMAKE_EXTRA_INCLUDE_FILES "sys/types.h" "sys/socket.h")
check_type_size("socklen_t" HAS_SOCKLEN_T BUILTIN_TYPES_ONLY)
unset(CMAKE_EXTRA_INCLUDE_FILES)

# Appliquer les définitions conditionnelles à la cible
if(HAS_FCNTL)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAS_FCNTL=1)
endif()
if(HAS_POLL)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAS_POLL=1)
endif()
if(HAS_GETNAMEINFO)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAS_GETNAMEINFO=1)
endif()
if(HAS_GETADDRINFO)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAS_GETADDRINFO=1)
endif()
if(HAS_GETHOSTBYNAME_R)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAS_GETHOSTBYNAME_R=1)
endif()
if(HAS_GETHOSTBYADDR_R)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAS_GETHOSTBYADDR_R=1)
endif()
if(HAS_INET_PTON)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAS_INET_PTON=1)
endif()
if(HAS_INET_NTOP)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAS_INET_NTOP=1)
endif()
if(HAS_MSGHDR_FLAGS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAS_MSGHDR_FLAGS=1)
endif()
if(HAS_SOCKLEN_T)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAS_SOCKLEN_T=1)
endif()

# Inclure les repertoires d'en-tete de RCENet
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

# Configuration spécifique à chaque système d'exploitation
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Configurations spécifiques à Windows
    target_link_libraries(${PROJECT_NAME}
        ws2_32 # Bibliothèque native à Windows (pour la librairie Enet concernant les sockets via Winsock2)
        winmm  # Bibliothèque native à Windows (pour la librairie Enet concernant les sockets via Winsock2)
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Solaris")
    # Configurations spécifiques à Solaris
    target_link_libraries(${PROJECT_NAME}
        socket # Bibliothèque native à Solaris (pour la librairie Enet concernant les sockets)
        nsl    # Bibliothèque native à Solaris (pour la librairie Enet concernant les sockets)
    )
endif()