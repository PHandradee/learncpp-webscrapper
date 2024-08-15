# Configura a versão mínima do CMake necessária para compilar o projeto
cmake_minimum_required(VERSION 3.10)

# Define o nome do projeto e sua versão
project(learn-cpp-webscrapper VERSION 1.0.0)

# Configura o padrão C++ para C++23 e outras opções
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define o diretório de origem dos arquivos-fonte
set(srcDir ${CMAKE_SOURCE_DIR}/src)

# Obtém todos os arquivos .cpp no diretório de origem
file(GLOB srcFiles "${srcDir}/*.cpp")

# Configurações de compilação
# - Wall: ativa todos os avisos
# - Werror: trata avisos como erros
set(CMAKE_CXX_FLAGS "-Wall -Werror")

# Configurações de depuração
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")

# Configurações de release
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -pedantic")

# Define o caminho para os arquivos de inclusão (headers)
set(includePath "${CMAKE_SOURCE_DIR}/libs/include" CACHE PATH "Caminho para os arquivos de inclusão")

# Define o caminho para a biblioteca dinâmica liblexbor-html.so.2.5.0
set(liblexborDynamic ${CMAKE_SOURCE_DIR}/libs/liblexbor-html.so.2.5.0)

# Define o diretório de saída para os executáveis
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Inclui os diretórios de inclusão
include_directories(${includePath})

# Cria o executável com os arquivos-fonte listados
add_executable(${PROJECT_NAME} ${srcFiles})

# Vincula a biblioteca dinâmica ao executável
target_link_libraries(${PROJECT_NAME} PRIVATE ${liblexborDynamic})

# Copia a DLL para o diretório de saída do executável
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${liblexborDynamic}"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
