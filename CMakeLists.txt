cmake_minimum_required(VERSION 3.21.1)

#set(QT_HOST_PATH "/home/development/qt-host")
#set(CMAKE_PREFIX_PATH "/usr/local/qt6")

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(CamaroDashboardV2App LANGUAGES C CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick Charts)
# Optionally set Lua paths manually if CMake cannot find them
set(LUA_INCLUDE_DIR "/usr/include/lua5.3")
set(LUA_LIBRARIES "/usr/lib/x86_64-linux-gnu/liblua5.3.so")

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_standard_project_setup()
endif()

file(GLOB SOURCES "src/microshell/src/src/*.c" "src/microshell/src/src/commands/*.c" "src/microshell/src/config/posix/*.c")
message(STATUS "SOURCES: ${SOURCES}")

qt_add_executable(CamaroDashboardV2App src/main.cpp
    src/GaugeController.cpp
    src/GaugeController.h
    src/interactiveshell.h src/interactiveshell.cpp
    ${SOURCES} src/HolleyCANDecoder.cpp src/HolleyCANDecoder.h
        src/globals.h
        src/globals.cpp
        src/DigitalGaugeController.h
        src/DigitalGaugeController.cpp
        src/AlarmEngine.cpp
        src/AlarmEngine.h
        src/iconController.cpp
        src/packetProtocol.cpp
        src/packetProtocol.h
        src/led.cpp
        src/led.h
        src/ImageGauge.cpp
        src/ImageGauge.h
        src/LogWidgetController.cpp
        src/LogWidgetController.h
        src/RPMProvider.cpp
        src/RPMProvider.h
        src/canThread.cpp
        src/canThread.h
        src/SettingsHandler.h
        src/SettingsHandler.cpp
        src/timeout_manager.cpp
        src/timeout_manager.h
        src/utils.cpp
        src/utils.h
        src/gps.cpp
        src/gps.h
        src/DigitalInputIndicator.cpp
        src/DigitalInputIndicator.h
        src/ButtonInputWidget.cpp
        src/ButtonInputWidget.h
        src/tinyxml2.h
        src/tinyxml2.cpp
        src/XMLSettingsHandler.cpp
        src/XMLSettingsHandler.h
)
target_include_directories(CamaroDashboardV2App PUBLIC src/microshell/src/inc src/microshell/src src/microshell/src/config/posix src/microshell/src/config/ src/cppcodec/ src/spdlog/include ${LUA_INCLUDE_DIR})

qt_add_resources(CamaroDashboardV2App "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

target_link_libraries(CamaroDashboardV2App PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    lua5.3
    Qt6::Charts
)

if (BUILD_QDS_COMPONENTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

if (LINK_INSIGHT)
    include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
endif ()

include(GNUInstallDirs)
install(TARGETS CamaroDashboardV2App
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# make IDEs aware of the QML import path
set(QML_IMPORT_PATH ${PROJECT_BINARY_DIR}/qml CACHE PATH
    "Path to the custom QML components defined by the project")
