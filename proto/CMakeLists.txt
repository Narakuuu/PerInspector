
# find and load Protobuf gRPC CMake config file
find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
# grpc lib
find_package(c-ares CONFIG)
# find_package(Threads)

#
# Protobuf/Grpc source files
#
set(PROTO_FILES
    monitor_info.proto
    cpu_load.proto
    cpu_softirq.proto
    cpu_stat.proto
    mem_info.proto
    net_info.proto
)


#
# Add Library target with protobuf sources
#
add_library(monitor_proto ${PROTO_FILES})


# target_link_libraries
# Link the monitor_proto library to the Protobuf and gRPC libraries    dynamic link
target_link_libraries(monitor_proto
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)

# message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")

# target_include_directories
# specify the header file directory for monitor_proto library
target_include_directories(monitor_proto PUBLIC
${PROTOBUF_INCLUDE_DIRS} 
${CMAKE_CURRENT_BINARY_DIR})




#
# Compile protobuf and grpc files in mointor proto target to cpp
#
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)

# protoc --proto_path=IMPORT_PATH --cpp_out=DST_DIR    .pb.h .pb.cc
#
# compile and generate .pb.h .pb.cc  to monitor_proto
#
protobuf_generate(TARGET monitor_proto LANGUAGE cpp)

# .grpc.pb.h .grpc.pb.cc
#
# compile and generate .grpc.pb.cc  .grpc.pb.h to monitor_proto
#
protobuf_generate(TARGET monitor_proto LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")
