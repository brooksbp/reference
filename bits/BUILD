package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "parity_bench",
    srcs = ["parity_bench.cc"],
    deps = ["//third_party/benchmark"],
    linkopts = ["-lm"],
)

cc_test(
    name = "parity_test",
    srcs = ["parity_test.cc"],
    deps = ["//third_party/googletest:gtest_main"],
    linkopts = ["-lm"],
)

cc_binary(
    name = "popcount_bench",
    srcs = ["popcount_bench.cc"],
    deps = ["//third_party/benchmark"],
    linkopts = ["-lm"],
)

cc_test(
    name = "popcount_test",
    srcs = ["popcount_test.cc"],
    deps = ["//third_party/googletest:gtest_main"],
    linkopts = ["-lm"],
)

cc_test(
    name = "powers_of_two_test",
    srcs = ["powers_of_two_test.cc"],
    deps = ["//third_party/googletest:gtest_main"],
)
