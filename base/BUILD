package(default_visibility = ["//visibility:public"])

cc_library(
    name = "base",
    srcs = [
        "cache.h",
        "compiler.h",
        "compile_time_macros.h",
        "prefetch.h",
        "rdrand.h",
        "types.h",
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