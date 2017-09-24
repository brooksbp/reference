package(default_visibility = ["//visibility:public"])

test_suite(
    name = "all_tests",
)

cc_library(
    name = "synchronization",
    srcs = [
        "lock.h",
        "spin_lock_mcs.h",
        "spin_lock_tas.h",
        "spin_lock_ticket.h",
    ],
    linkopts = [
        "-lm",
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
        ":synchronization",
        "//third_party/benchmark"
    ],
)

cc_binary(
    name = "atomic_bench",
    srcs = ["atomic_bench.cc"],
    deps = [
        "//third_party/benchmark"
    ],
)
