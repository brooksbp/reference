package(default_visibility = ["//visibility:public"])

test_suite(
    name = "all_tests",
)

cc_library(
    name = "base",
    srcs = [
        "cache.h",
        "compiler.h",
        "compile_time_macros.h",
        "eintr_wrapper.h",
        "file.h",
        "file.c",
        "file_path.h",
        "file_path.c",
        "file_util.h",
        "file_util.c",
        "logging.h",
        "logging.c",
        "prefetch.h",
        "rdrand.h",
        "string_util.h",
        "string_util.c",
        "time.h",
        "time.c",
        "types.h",
    ],
)

cc_test(
    name = "logging_test",
    srcs = ["logging_test.c"],
    deps = [":base"]
)

cc_test(
    name = "string_util_test",
    srcs = ["string_util_test.cc"],
    deps = [
        ":base",
        "//third_party/googletest:gtest_main",
    ],
)

cc_binary(
    name = "rdrand_bench",
    srcs = ["rdrand_bench.cc"],
    deps = [
        ":base",
        "//third_party/benchmark",
    ],
    copts = [
        "-fno-omit-frame-pointer",
        "-fno-exceptions",
        "-fno-rtti",
    ],
)