#ifndef EXAMPLE_JWT_STORYDTO_HPP
#define EXAMPLE_JWT_STORYDTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class StoryDto : public oatpp::DTO {

  DTO_INIT(StoryDto, DTO)

  DTO_FIELD(String, id);
  DTO_FIELD(String, userId, "userid");
  DTO_FIELD(String, content, "content");

};

#include OATPP_CODEGEN_END(DTO)


#endif //EXAMPLE_JWT_STORYDTO_HPP
