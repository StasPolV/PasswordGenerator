include(FetchContent)

set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTORCC OFF)

# cmake-lint: disable=C0103
set(gtest_force_shared_crt ON)
set(INSTALL_GTEST OFF)
set(BUILD_GMOCK OFF)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(googletest)

set(CMAKE_AUTOMOC ON)

add_executable(PasswordGeneratorTests main.cpp PasswordGeneratorModelTest.cpp)

target_link_libraries(PasswordGeneratorTests PRIVATE Model Qt6::Core
                                                     GTest::gtest)

include(GoogleTest)
gtest_discover_tests(PasswordGeneratorTests)
