#ifndef EXAMPLE_JWT_STORYSERVICE_HPP
#define EXAMPLE_JWT_STORYSERVICE_HPP

#include "db/model/StoryModel.hpp"
#include "db/StoryDb.hpp"

#include "dto/StoryDto.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class StoryService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  oatpp::Object<StoryDto> storyDtoFromModel(const oatpp::Object<StoryModel>& model);
  oatpp::Object<StoryModel> storyModelFromDto(const oatpp::String& userId, const oatpp::Object<StoryDto>& dto);
private:
  OATPP_COMPONENT(std::shared_ptr<StoryDb>, m_database); // Inject database component
public:

  oatpp::Object<StoryDto> createStory(const oatpp::String& userId, const oatpp::Object<StoryDto>& dto);
  oatpp::Object<StoryDto> updateStory(const oatpp::String& userId, const oatpp::Object<StoryDto>& dto);
  oatpp::Object<StoryDto> getStoryByUserIdAndId(const oatpp::String& userId, const oatpp::String& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);
  oatpp::Object<PageDto<oatpp::Object<StoryDto>>> getAllUserStories(const oatpp::String& userId, const oatpp::UInt32& offset, const oatpp::UInt32& limit);
  oatpp::Object<StatusDto> deleteStoryByUserIdAndId(const oatpp::String& userId, const oatpp::String& id);

};

#endif //EXAMPLE_JWT_STORYSERVICE_HPP
