package(default_visibility = ["//visibility:public"])

test_suite(
    name = "all_tests",
)

cc_library(
    name = "spin_lock",
    srcs = [
        "mcs.h",
        "tas.h",
        "ticket.h",
    ],
    linkopts = [
        "-lm",
    ],
)

cc_library(
    name = "synchronization",
    srcs = [
        "lock.h",
    ],
    deps = [
        "//base",
        "//base/threading",
    ],
)

cc_test(
    name = "lock_test",
    srcs = ["lock_test.cc"],
    deps = [
        ":synchronization",
        "//third_party/googletest:gtest_main",
    ],
)

cc_binary(
    name = "spin_lock_bench",
    srcs = ["spin_lock_bench.cc"],
    deps = [
        ":spin_lock",
        "//base",
        "//third_party/benchmark"
    ],
)
