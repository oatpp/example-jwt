cmake_minimum_required(VERSION 3.1)
project(example-jwt)

set(CMAKE_CXX_STANDARD 11)

if( NOT CMAKE_BUILD_TYPE )
   set( CMAKE_BUILD_TYPE Debug ... FORCE )
endif() 

enable_testing()

if(CMAKE_BUILD_TYPE MATCHES Debug)
   set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Output/Debug/lib)
   set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Output/Debug/lib)
   set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Output/Debug/bin)
elseif(CMAKE_BUILD_TYPE MATCHES MinSizeRel)   
   set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Output/MinSizeRel/lib)
   set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Output/MinSizeRel/lib)
   set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Output/MinSizeRel/bin)
elseif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)   
   set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Output/RelWithDebInfo/lib)
   set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Output/RelWithDebInfo/lib)
   set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Output/RelWithDebInfo/bin)   
else()
   set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Output/Release/lib)
   set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Output/Release/lib)
   set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Output/Release/bin)   
endif() 


add_library(example-jwt-lib
        src/auth/AuthHandler.cpp
        src/auth/AuthHandler.hpp
        src/auth/JWT.cpp
        src/auth/JWT.hpp
        src/controller/StaticController.hpp
        src/controller/StoryController.hpp
        src/controller/AuthController.hpp
        src/db/model/StoryModel.hpp
        src/db/model/UserModel.hpp
        src/db/StoryDb.hpp
        src/db/UserDb.hpp
        src/dto/AuthDto.hpp
        src/dto/PageDto.hpp
        src/dto/SignInDto.hpp
        src/dto/SignUpDto.hpp
        src/dto/StatusDto.hpp
        src/dto/StoryDto.hpp
        src/interceptor/AuthInterceptor.cpp
        src/interceptor/AuthInterceptor.hpp
        src/service/AuthService.cpp
        src/service/AuthService.hpp
        src/service/StoryService.cpp
        src/service/StoryService.hpp
        src/AppComponent.hpp
        src/DatabaseComponent.hpp
        src/SwaggerComponent.hpp
        src/ErrorHandler.cpp
        src/ErrorHandler.hpp
)

## include directories

target_include_directories(example-jwt-lib PUBLIC src)

find_package(OpenSSL 1.1 REQUIRED)

## link libs

find_package(oatpp              1.3.0 REQUIRED)
find_package(oatpp-swagger      1.3.0 REQUIRED)
find_package(oatpp-postgresql   1.3.0 REQUIRED)
find_package(oatpp-openssl      1.3.0 REQUIRED)

find_package(jwt-cpp REQUIRED PATHS /usr/share/cmake)

target_link_libraries(example-jwt-lib
        # oatpp
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-postgresql
        PUBLIC oatpp::oatpp-openssl

        # third-party
        PUBLIC jwt-cpp::jwt-cpp
        PUBLIC OpenSSL::SSL
        PUBLIC OpenSSL::Crypto

)

add_definitions(
        ## define path to swagger-ui static resources folder
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

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
        test/FullTest.cpp
        test/FullTest.hpp
        test/tests.cpp
)
target_link_libraries(example-jwt-test example-jwt-lib)

enable_testing()
add_test(project-tests example-jwt-test)
