add_library(Model PasswordGeneratorModel.h PasswordGeneratorModel.cpp)

target_include_directories(Model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Model PUBLIC Qt6::Core)
