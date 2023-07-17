
#ifndef EXAMPLE_JWT_DATABASECOMPONENT_HPP
#define EXAMPLE_JWT_DATABASECOMPONENT_HPP

#include "db/StoryDb.hpp"
#include "db/UserDb.hpp"

class DatabaseComponent
{
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::postgresql::ConnectionPool>, connectionPool)
    ([] {
        oatpp::String connStr = "postgresql://postgres:db-pass@localhost:5432/postgres";

        /* Create database-specific ConnectionProvider */
        auto connectionProvider = std::make_shared<oatpp::postgresql::ConnectionProvider>(connStr);

        /* Create database-specific ConnectionPool */
        return oatpp::postgresql::ConnectionPool::createShared(connectionProvider, 10 /* max-connections */, std::chrono::seconds(5) /* connection TTL */);
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::postgresql::Executor>, databaseExecutor)
    ([] {
        /* get connection pool component */
        OATPP_COMPONENT(std::shared_ptr<oatpp::postgresql::ConnectionPool>, connectionPool);

        /* Create database-specific Executor */
        return std::make_shared<oatpp::postgresql::Executor>(connectionPool);
    }());

    /**
   * Create database client
   */
    OATPP_CREATE_COMPONENT(std::shared_ptr<UserDb>, userDb)
    ([] {
        /* get DB executor component */
        OATPP_COMPONENT(std::shared_ptr<oatpp::postgresql::Executor>, databaseExecutor);

        /* Create MyClient database client */
        return std::make_shared<UserDb>(databaseExecutor);
    }());

    /**
   * Create database client
   */
    OATPP_CREATE_COMPONENT(std::shared_ptr<StoryDb>, storyDb)
    ([] {
        /* get DB executor component */
        OATPP_COMPONENT(std::shared_ptr<oatpp::postgresql::Executor>, databaseExecutor);

        /* Create MyClient database client */
        return std::make_shared<StoryDb>(databaseExecutor);
    }());
};

#endif //EXAMPLE_JWT_DATABASECOMPONENT_HPP
