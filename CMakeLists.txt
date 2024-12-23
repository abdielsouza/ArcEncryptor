cmake_minimum_required(VERSION 3.20.0)
project(ArcEncryptor VERSION 0.1.0)

set(CXX_STANDARD 17)
include(CPack)

# file(GLOB_RECURSE sources CMAKE_CONFIGURE_DEPENDS "src/**/*.hpp" "src/**/*.h" "src/**/*.cpp" "src/**/*.c")

include_directories(
    src/**
)

add_library(arc-encryptor-lib SHARED "src/arc_encryptor.cpp" "src/arc_encryptor.hpp" "src/arc_utils.hpp")

# Especifica os diretórios de cabeçalhos
target_include_directories(arc-encryptor-lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(arc-encryptor-lib PRIVATE ssl)
target_link_libraries(arc-encryptor-lib PRIVATE crypto)

# Define padrões de compilação
set_target_properties(arc-encryptor-lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Cria um alias para facilitar o uso no modo de instalação
add_library(ArcEncryptor::ArcEncryptor ALIAS arc-encryptor-lib)

# Define as regras de instalação
install(TARGETS arc-encryptor-lib
    EXPORT ArcEncryptorTargets           # Exporta configurações para projetos que usam a biblioteca
    ARCHIVE DESTINATION lib           # Para bibliotecas estáticas
    LIBRARY DESTINATION lib           # Para bibliotecas compartilhadas
    RUNTIME DESTINATION bin           # Para executáveis, se houver
    INCLUDES DESTINATION include
)

# Instala os cabeçalhos
install(DIRECTORY src/
    DESTINATION include
)

# Exporta as configurações de uso da biblioteca
install(EXPORT ArcEncryptorTargets
    FILE ArcEncryptorConfig.cmake        # Nome do arquivo de configuração
    NAMESPACE ArcEncryptor::             # Namespace usado para referenciar a biblioteca
    DESTINATION lib/cmake/ArcEncryptor   # Caminho para os arquivos de configuração
)

# Gera um pacote de configuração no build tree
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/ArcEncryptorConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

export(EXPORT ArcEncryptorTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/ArcEncryptorConfig.cmake"
    NAMESPACE ArcEncryptor::
)

add_subdirectory(test)