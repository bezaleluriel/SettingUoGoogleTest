cmake_minimum_required(VERSION 3.3)
project(SettingUoGoogleTest)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES src/sockets/Socket.cpp src/sockets/Socket.h src/sockets/Tcp.cpp
        src/sockets/Tcp.h Tests/ClassName.h Tests/test.cpp Tests/PoinTest.cpp src/Point.cpp
        src/Point.h src/BeginningInfoReader.cpp
        src/BeginningInfoReader.h src/Bfs.cpp src/Bfs.h src/Grid.cpp src/Grid.h src/GridNode.cpp
        src/GridNode.h src/Structure.h
        Tests/GridNodeTest.cpp Tests/GridTest.cpp Tests/bfsTest.cpp
        Tests/BeginningInfoReaderTest.cpp
        src/Color.h src/Driver.cpp
        src/Driver.h src/Gps.cpp src/Gps.h
        src/LuxuryCab.cpp src/LuxuryCab.h src/Manufacturer.h src/MaritalStatus.h src/Passenger.cpp src/Passenger.h
        src/StandardCab.cpp
        src/StandardCab.h src/TaxiCenter.cpp src/TaxiCenter.h src/TripInformation.cpp src/TripInformation.h
        Tests/DriverTest.cpp
        Tests/GpsTest.cpp
        src/MainFlow.cpp src/MainFlow.h
        Tests/PassengerTest.cpp Tests/TaxiCenterTest.cpp Tests/TripInformationTest.cpp
        Tests/StandartCabTest.cpp src/BaseCab.cpp src/BaseCab.h Tests/LaxuryCabTest.cpp
        )

add_executable(Client ${SOURCE_FILES} Client.cpp src/ThreadInfo.cpp src/ThreadInfo.h)
        target_link_libraries(Client gtest gtest_main)

add_executable(Server ${SOURCE_FILES} Server.cpp)
        target_link_libraries(Server gtest gtest_main)

add_executable(SettingUoGoogleTest ${SOURCE_FILES} main.cpp Tests/ClassName.h Tests/test.cpp Tests/PoinTest.cpp
        Tests/GridNodeTest.cpp Tests/GridTest.cpp Tests/bfsTest.cpp Tests/BeginningInfoReaderTest.cpp
        Tests/DriverTest.cpp
        Tests/GpsTest.cpp
        Tests/PassengerTest.cpp Tests/TaxiCenterTest.cpp Tests/TripInformationTest.cpp Tests/StandartCabTest.cpp src/BaseCab.cpp src/BaseCab.h Tests/LaxuryCabTest.cpp)

        target_link_libraries(SettingUoGoogleTest gtest gtest_main)


target_link_libraries(Server  ${Boost_LIBRARIES})
target_link_libraries(Client  ${Boost_LIBRARIES})

target_link_libraries(SettingUoGoogleTest ${Boost_LIBRARIES})
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

