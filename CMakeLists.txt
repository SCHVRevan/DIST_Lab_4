cmake_minimum_required(VERSION 3.5)
project(Lab4)

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR}) 
add_executable(lab4 main.cpp encryptor.cpp dir_checker.cpp cipher.cpp)

target_link_libraries(lab4 ${OPENSSL_LIBRARIES})
