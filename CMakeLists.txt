cmake_minimum_required(VERSION 3.1)
project(example-jwt)

set(CMAKE_CXX_STANDARD 11)

add_library(example-jwt-lib
        src/controller/StaticController.hpp
        src/controller/UserController.hpp
        src/db/UserDb.hpp
        src/dto/PageDto.hpp
        src/dto/StatusDto.hpp
        src/dto/UserDto.hpp
        src/service/UserService.cpp
        src/service/UserService.hpp
        src/AppComponent.hpp
        src/DatabaseComponent.hpp
        src/SwaggerComponent.hpp
        src/ErrorHandler.cpp
        src/ErrorHandler.hpp)

## include directories

target_include_directories(example-jwt-lib PUBLIC src)


## link libs

find_package(oatpp          1.2.0 REQUIRED)
find_package(oatpp-swagger  1.2.0 REQUIRED)
find_package(oatpp-sqlite   1.2.0 REQUIRED)

target_link_libraries(example-jwt-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-sqlite
)

add_definitions(
        ## define path to swagger-ui static resources folder
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

        ## SQLite databse file
        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/db.sqlite"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(example-jwt-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

## add executables

add_executable(example-jwt-exe src/App.cpp)
target_link_libraries(example-jwt-exe example-jwt-lib)

add_executable(example-jwt-test
        test/tests.cpp
)
target_link_libraries(example-jwt-test example-jwt-lib)

enable_testing()
add_test(project-tests example-jwt-test)
