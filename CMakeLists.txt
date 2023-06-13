cmake_minimum_required(VERSION 3.24)
project(test)

set(CMAKE_CXX_STANDARD 17)

include(cmake/CPM.cmake)

#########################################
# poco (executável: 4,8mb)
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
# yasio (executável: 4,8mb com openssl e 2mb com mbedtls)
#########################################
set(YASIO_VERSION 3.39.11)
set(YASIO_VERSION dev)

CPMAddPackage(
  NAME yasio
  GITHUB_REPOSITORY yasio/yasio
  GIT_TAG ${YASIO_VERSION}
  OPTIONS
        "YASIO_SSL_BACKEND 2"
        "YASIO_BUILD_WITH_LUA NO"
        "YASIO_BUILD_WITH_CCLUA NO"
        "YASIO_BUILD_TESTS NO"
        "YASIO_BUILD_LUA_EXAMPLE NO"
        "YAISO_BUILD_NI NO"
)

add_executable(test main-yasio.cpp)
target_link_libraries(test yasio yasio_http)
target_link_libraries(test mbedtls)
