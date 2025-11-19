cmake_minimum_required(VERSION 3.16)

project(Client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets Network Sql)
find_package(spdlog CONFIG REQUIRED)

qt_standard_project_setup()

file(GLOB SRC "src/*.cpp")
file(GLOB HEADERS "headers/*.h" "resources/*.")
file(GLOB UI "ui/*.ui")

qt_add_executable(Client
    ${SRC}
    ${HEADERS}
    ${UI}
)

target_include_directories(Client PRIVATE headers ui resources resources/qss)
target_link_libraries(Client PRIVATE spdlog::spdlog Qt6::Network Qt6::Sql)

set_target_properties(Client PROPERTIES AUTOUIC_SEARCH_PATHS "./ui")

target_link_libraries(Client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Client PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
