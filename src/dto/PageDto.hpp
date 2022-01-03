
#ifndef EXAMPLE_JWT_PAGEDTO_HPP
#define EXAMPLE_JWT_PAGEDTO_HPP

#include "AuthDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class PageDto : public oatpp::DTO {

  DTO_INIT(PageDto, DTO)

  DTO_FIELD(UInt32, offset);
  DTO_FIELD(UInt32, limit);
  DTO_FIELD(UInt32, count);
  DTO_FIELD(Vector<T>, items);

};

class UsersPageDto : public PageDto<oatpp::Object<AuthDto>> {

  DTO_INIT(UsersPageDto, PageDto<oatpp::Object<AuthDto>>)

};

#include OATPP_CODEGEN_END(DTO)

#endif //EXAMPLE_JWT_PAGEDTO_HPP
