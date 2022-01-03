
#include "StoryService.hpp"

oatpp::Object<StoryDto> StoryService::createStory(const oatpp::Object<StoryDto>& dto) {

  auto dbResult = m_database->createStory(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  return getStoryByIdAndUserId(dto->id, dto->userId);

}

oatpp::Object<StoryDto> StoryService::updateStory(const oatpp::Object<StoryDto>& dto) {

  auto dbResult = m_database->updateStoryByIdAndUserId(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  return getStoryByIdAndUserId(dto->id, dto->userId);

}

oatpp::Object<StoryDto> StoryService::getStoryByIdAndUserId(const oatpp::String& id,
                                                            const oatpp::String& userId,
                                                            const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection)
{

  auto dbResult = m_database->getStoryByIdAndUserId(id, userId, connection);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "User story not found");

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<StoryDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

  return result[0];

}

oatpp::Object<PageDto<oatpp::Object<StoryDto>>> StoryService::getAllUserStories(const oatpp::String& userId,
                                                                                const oatpp::UInt32& offset,
                                                                                const oatpp::UInt32& limit)
{

  oatpp::UInt32 countToFetch = limit;

  if(limit > 10) {
    countToFetch = 10;
  }

  auto dbResult = m_database->getAllUserStories(userId, offset, countToFetch);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<StoryDto>>>();

  auto page = PageDto<oatpp::Object<StoryDto>>::createShared();
  page->offset = offset;
  page->limit = countToFetch;
  page->count = items->size();
  page->items = items;

  return page;

}

oatpp::Object<StatusDto> StoryService::deleteStoryByIdAndUserId(const oatpp::String &id, const oatpp::String &userId) {
  auto dbResult = m_database->deleteStoryByIdAndUserId(id, userId);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  auto status = StatusDto::createShared();
  status->status = "OK";
  status->code = 200;
  status->message = "User story was successfully deleted";
  return status;
}