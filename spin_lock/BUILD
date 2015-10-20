package(default_visibility = ["//visibility:public"])

test_suite(
    name = "all_tests",
)

cc_library(
    name = "spin_lock",
    hdrs = [
        "tas.h",
    ],
    linkopts = [
        "-lm",
    ],
)

cc_binary(
    name = "tas_bench",
    srcs = ["tas_bench.cc"],
    deps = [
        ":spin_lock",
        "//third_party/benchmark"
    ],
)
