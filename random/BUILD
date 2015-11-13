package(default_visibility = ["//visibility:public"])

cc_library(
    name = "random",
    hdrs = [
        "rdrand.h",
    ],
)

cc_binary(
    name = "rdrand_bench",
    srcs = ["rdrand_bench.cc"],
    deps = [
        ":random",
        "//third_party/benchmark",
    ],
    copts = [
        "-fno-omit-frame-pointer",
        "-fno-exceptions",
        "-fno-rtti",
    ],
)
