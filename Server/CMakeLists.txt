cmake_minimum_required(VERSION 3.16)

project(Server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC "src/*.cpp")
file(GLOB HEADERS "headers/*.h")

find_package(Qt6 REQUIRED COMPONENTS Core Network Sql)
find_package(spdlog CONFIG REQUIRED)
find_package(unofficial-libmysql CONFIG REQUIRED)

qt_standard_project_setup()

qt_add_executable(Server
  ${SRC}
  ${HEADERS}
)

target_include_directories(Server PRIVATE headers)
target_link_libraries(Server PRIVATE Qt6::Network spdlog::spdlog Qt6::Sql unofficial::libmysql::libmysql)

install(TARGETS Server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
