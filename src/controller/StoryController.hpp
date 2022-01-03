#ifndef EXAMPLE_JWT_STORYCONTROLLER_HPP
#define EXAMPLE_JWT_STORYCONTROLLER_HPP

#include "service/StoryService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * Story REST controller.
 */
class StoryController : public oatpp::web::server::api::ApiController {
public:
  StoryController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
private:
  StoryService m_storyService; // Create story service.
public:

  static std::shared_ptr<StoryController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  ){
    return std::make_shared<StoryController>(objectMapper);
  }
  
  ENDPOINT_INFO(createStory) {
    info->summary = "Create new Story";

    info->addConsumes<Object<StoryDto>>("application/json");

    info->addResponse<Object<StoryDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST", "stories", createStory,
           BUNDLE(String, userId),
           BODY_DTO(Object<StoryDto>, storyDto))
  {
    storyDto->id = nullptr;
    storyDto->userId = userId;
    return createDtoResponse(Status::CODE_200, m_storyService.createStory(storyDto));
  }
  
  
  ENDPOINT_INFO(putStory) {
    info->summary = "Update Story by storyId";

    info->addConsumes<Object<StoryDto>>("application/json");

    info->addResponse<Object<StoryDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["storyId"].description = "Story Identifier";
  }
  ENDPOINT("PUT", "stories/{storyId}", putStory,
           BUNDLE(String, userId),
           PATH(String, storyId),
           BODY_DTO(Object<StoryDto>, storyDto))
  {
    storyDto->id = storyId;
    storyDto->userId = userId;
    return createDtoResponse(Status::CODE_200, m_storyService.updateStory(storyDto));
  }
  
  
  ENDPOINT_INFO(getStoryById) {
    info->summary = "Get one Story by storyId";

    info->addResponse<Object<StoryDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["storyId"].description = "Story Identifier";
  }
  ENDPOINT("GET", "stories/{storyId}", getStoryById,
           BUNDLE(String, userId),
           PATH(String, storyId))
  {
    return createDtoResponse(Status::CODE_200, m_storyService.getStoryByIdAndUserId(storyId, userId));
  }
  
  
  ENDPOINT_INFO(getStories) {
    info->summary = "get all user stories";

    info->addResponse<oatpp::Object<UsersPageDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "stories/offset/{offset}/limit/{limit}", getStories,
           BUNDLE(String, userId),
           PATH(UInt32, offset),
           PATH(UInt32, limit))
  {
    return createDtoResponse(Status::CODE_200, m_storyService.getAllUserStories(userId, offset, limit));
  }
  
  
  ENDPOINT_INFO(deleteStory) {
    info->summary = "Delete story by storyId";

    info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["storyId"].description = "Story Identifier";
  }
  ENDPOINT("DELETE", "stories/{userId}", deleteStory,
           BUNDLE(String, userId),
           PATH(String, storyId))
  {
    return createDtoResponse(Status::CODE_200, m_storyService.deleteStoryByIdAndUserId(storyId, userId));
  }

};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif /* EXAMPLE_JWT_STORYCONTROLLER_HPP */
