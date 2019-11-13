# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
COPTS = [
    "-DGFLAGS=gflags",
    "-DOS_LINUX",
    "-DSNAPPY",
    "-DHAVE_SSE42",
    "-DNDEBUG",
    "-fno-omit-frame-pointer",
    "-momit-leaf-frame-pointer",
    "-msse4.2",
    "-pthread",
    "-Wsign-compare",
    "-Wno-unused-parameter",
    "-Wno-unused-variable",
    "-Woverloaded-virtual",
    "-Wnon-virtual-dtor",
    "-Wno-missing-field-initializers"
]

cc_library(
    name = "client_integration_common_lib",
    srcs = glob([
        "*.h",
        "*.cpp"],
    ),
    copts = COPTS,
    defines = ["FIU_ENABLE"],
    linkopts = ["-lfiu"],
    visibility = ["//visibility:public"],
    deps = [
        "//external:braft",
        "//external:brpc",
        "//external:gflags",
        "//external:glog",
        "//external:leveldb",
        "//external:protobuf",
        "//include/client:include_client",
        "//src/client:curve_client",
        "//src/common:curve_common",
        "//src/common/concurrent:curve_concurrent",
        "//src/mds/dao:mdsrepo",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
)