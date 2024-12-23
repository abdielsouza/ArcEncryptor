cmake_minimum_required(VERSION 3.20.0)
project(ArcEncryptorTestApplication VERSION 0.1.0)

add_executable(arc-encryptor-testing "main.cpp")

target_link_libraries(arc-encryptor-testing PRIVATE ArcEncryptor::ArcEncryptor)