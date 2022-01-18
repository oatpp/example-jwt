
#ifndef EXAMPLE_JWT_FULLTEST_HPP
#define EXAMPLE_JWT_FULLTEST_HPP

#include "oatpp-test/UnitTest.hpp"

class FullTest : public oatpp::test::UnitTest {
public:
  FullTest() : oatpp::test::UnitTest("[MyTest]")
  {}

  void onRun() override;

};


#endif //EXAMPLE_JWT_FULLTEST_HPP
