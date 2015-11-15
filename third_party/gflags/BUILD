licenses(["notice"])

cc_library(
    name = "gflags",
    visibility = ["//visibility:public"],
    includes = ["build/include"],
    srcs = [
        "upstream/src/gflags.cc",
        "upstream/src/gflags_completions.cc",
        "upstream/src/gflags_reporting.cc",
        "upstream/src/mutex.h",
        "upstream/src/util.h",
    ],
    hdrs = [
        "build/include/gflags/gflags_completions.h",
        "build/include/gflags/gflags_declare.h",
        "build/include/gflags/gflags_gflags.h",
        "build/include/gflags/gflags.h",
    ],
    copts = [
        "-Ithird_party/gflags/build/include/gflags",
    ],
    linkopts = [
        "-pthread",
    ],
)

cc_test(
    name = "gflags_unittest",
    srcs = [
        "upstream/test/gflags_unittest.cc",
    ],
    copts = [
        "-Ithird_party/gflags/build/include/gflags",
        "-Ithird_party/gflags/upstream/src",
    ],
    deps = [
        ":gflags"
    ],
)