
#ifndef EXAMPLE_JWT_AUTHSERVICE_HPP
#define EXAMPLE_JWT_AUTHSERVICE_HPP

#include "auth/JWT.hpp"

#include "db/UserDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/SignUpDto.hpp"
#include "dto/SignInDto.hpp"
#include "dto/AuthDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class AuthService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<UserDb>, m_database); // Inject database component
  OATPP_COMPONENT(std::shared_ptr<JWT>, m_jwt); // Inject JWT component
public:

  oatpp::Object<AuthDto> signUp(const oatpp::Object<SignUpDto>& dto);
  oatpp::Object<AuthDto> signIn(const oatpp::Object<SignInDto>& dto);
  oatpp::Object<StatusDto> deleteUserById(const oatpp::String& id);

};

#endif //EXAMPLE_JWT_AUTHSERVICE_HPP
