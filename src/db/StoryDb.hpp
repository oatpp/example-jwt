
#ifndef EXAMPLE_JWT_STORYDB_HPP
#define EXAMPLE_JWT_STORYDB_HPP

#include "dto/StoryDto.hpp"
#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * StoryDb client definitions.
 */
class StoryDb : public oatpp::orm::DbClient {
public:

  StoryDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
    : oatpp::orm::DbClient(executor)
  {
  }

  QUERY(createStory,
        "INSERT INTO Stories"
        "(id, userid, content) VALUES "
        "(uuid_generate_v4(), :story.userid, :story.content) "
        "RETURNING *;",
        PREPARE(true), // prepared statement!
        PARAM(oatpp::Object<StoryDto>, story))

  QUERY(updateStoryByIdAndUserId,
        "UPDATE Stories "
        "SET "
        " content=:story.content, "
        "WHERE "
        " id=:story.id AND userid=:story.userid "
        "RETURNING *;",
        PREPARE(true), // prepared statement!
        PARAM(oatpp::Object<StoryDto>, story))

  QUERY(getStoryByIdAndUserId,
        "SELECT * FROM Stories WHERE id=:id AND userid=:userid;",
        PREPARE(true), // prepared statement!
        PARAM(oatpp::String, id),
        PARAM(oatpp::String, userId, "userid"))

  QUERY(getAllUserStories,
        "SELECT * FROM Stories WHERE userid=:userid LIMIT :limit OFFSET :offset;",
        PREPARE(true), // prepared statement!
        PARAM(oatpp::String, userId, "userid"),
        PARAM(oatpp::UInt32, offset),
        PARAM(oatpp::UInt32, limit))

  QUERY(deleteStoryByIdAndUserId,
        "DELETE FROM Stories WHERE id=:id AND userid=:userid;",
        PREPARE(true), // prepared statement!
        PARAM(oatpp::String, id),
        PARAM(oatpp::String, userId, "userid"))

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen


#endif //EXAMPLE_JWT_STORYDB_HPP
