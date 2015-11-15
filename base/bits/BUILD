package(default_visibility = ["//visibility:public"])

test_suite(
    name = "all_tests",
)

cc_library(
    name = "bits",
    hdrs = [
        "parity.h",
        "popcount.h",
        "powers_of_two.h",
    ],
    linkopts = [
        "-lm",
    ],
)

cc_test(
    name = "parity_test",
    srcs = ["parity_test.cc"],
    deps = [
        ":bits",
        "//third_party/googletest:gtest_main"
    ],
)

cc_test(
    name = "popcount_test",
    srcs = ["popcount_test.cc"],
    deps = [
        ":bits",
        "//third_party/googletest:gtest_main"
    ],
)

cc_test(
    name = "powers_of_two_test",
    srcs = ["powers_of_two_test.cc"],
    deps = [
        ":bits",
        "//third_party/googletest:gtest_main"
    ],
)

cc_binary(
    name = "parity_bench",
    srcs = ["parity_bench.cc"],
    deps = [
        ":bits",
        "//third_party/benchmark"
    ],
)

cc_binary(
    name = "popcount_bench",
    srcs = ["popcount_bench.cc"],
    deps = [
        ":bits",
        "//third_party/benchmark"
    ],
)
