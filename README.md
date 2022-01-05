# Example-JWT [![Build Status](https://dev.azure.com/lganzzzo/lganzzzo/_apis/build/status/oatpp.example-jwt?branchName=master)](https://dev.azure.com/lganzzzo/lganzzzo/_build?definitionId=9?branchName=master)

A complete example of a "CRUD" API secured with JSON Web Token (JWT) built with [Oat++](https://github.com/oatpp/oatpp) and [jwt-cpp](https://github.com/Thalhammer/jwt-cpp).

In this example:

- How to create CRUD endpoints.
- How to secure endpoints with JWT.
- How to use [Oat++ ORM](https://oatpp.io/docs/components/orm/#high-level-overview) - PostgreSQL example.
- How to document API with Swagger-UI and OpenApi 3.0.0.

More about Oat++:

- [Oat++ Website](https://oatpp.io/)
- [Oat++ Github Repository](https://github.com/oatpp/oatpp)
- [Get Started](https://oatpp.io/docs/start)

## Overview

This project is using the following oatpp modules:

- [oatpp](https://github.com/oatpp/oatpp) 
- [oatpp-swagger](https://github.com/oatpp/oatpp-swagger)
- [oatpp-postgresql](https://github.com/oatpp/oatpp-postgresql)
- [oatpp-openssl](https://github.com/oatpp/oatpp-openssl)

### 3rd party dependencies

- OpenSSL
- [jwt-cpp](https://github.com/Thalhammer/jwt-cpp).

### Project layout

```
|- CMakeLists.txt                        // projects CMakeLists.txt
|- sql/                                  // SQL migration scripts
|- src/
|   |
|   |- controller/                       // Folder containing REST Controllers (AuthController, StoryController)
|   |- db/                               // Folder containing database clients
|   |- dto/                              // DTOs are declared here
|   |- service/                          // Service business logic classes (AuthService, StoryService)
|   |- AppComponent.hpp                  // Service config
|   |- DatabaseComponent.hpp             // Database config
|   |- SwaggerComponent.hpp              // Swagger-UI config
|   |- App.cpp                           // main() is here
|
|- test/                                 // test folder
|- utility/install-oatpp-modules.sh      // utility script to install required oatpp-modules.
```

