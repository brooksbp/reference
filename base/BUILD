package(default_visibility = ["//visibility:public"])

cc_library(
    name = "base",
    srcs = [
        "cache.h",
        "compiler.h",
        "compile_time_macros.h",
        "logging.h",
        "logging.c",
        "prefetch.h",
        "rdrand.h",
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