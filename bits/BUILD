package(default_visibility = ["//visibility:public"])

cc_test(
    name = "popcount_test",
    srcs = ["popcount_test.cc"],
    deps = ["//third_party/googletest:gtest_main"],
    linkopts = ["-lm"],
)

cc_binary(
    name = "popcount_bench",
    srcs = ["popcount_bench.cc"],
    deps = ["//third_party/benchmark"],
    linkopts = ["-lm"],
)
