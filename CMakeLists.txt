cmake_minimum_required(VERSION 3.24)
project(test)

set(CMAKE_CXX_STANDARD 17)

include(cmake/CPM.cmake)

#########################################
# poco (executable: 4,8mb)
#########################################
# CPMAddPackage(
#     NAME Poco
#     GITHUB_REPOSITORY pocoproject/poco
#     GIT_TAG poco-1.12.4-release
#     OPTIONS
#         "BUILD_SHARED_LIBS NO"
#         "POCO_UNBUNDLED OFF"
#         "ENABLE_NETSSL ON"
# )

# add_executable(test main-poco.cpp)

# target_link_libraries(test PUBLIC Poco::Foundation Poco::NetSSL)

#########################################
# yasio (executable: 4,8mb with openssl and 2mb with mbedtls)
#########################################
set(YASIO_VERSION v4.1.0)

CPMAddPackage(
  NAME yasio
  GITHUB_REPOSITORY yasio/yasio
  GIT_TAG ${YASIO_VERSION}
  OPTIONS
        "YASIO_SSL_BACKEND ${YASIO_SSL_BACKEND}"
        "YASIO_BUILD_EXT_HTTP YES"
        "YASIO_BUILD_WITH_LUA NO"
        "YASIO_BUILD_WITH_CCLUA NO"
        "YASIO_BUILD_TESTS NO"
        "YASIO_BUILD_LUA_EXAMPLE NO"
        "YAISO_BUILD_NI NO"
        "MBEDTLS_FATAL_WARNINGS NO"
)

add_executable(test main-yasio.cpp)
target_link_libraries(test yasio yasio_http)

if(IOS)
    set_target_properties(test PROPERTIES
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER com.example.myapp
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
    )
endif()
