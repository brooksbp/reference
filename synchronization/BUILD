package(default_visibility = ["//visibility:public"])

test_suite(
    name = "all_tests",
)

cc_library(
    name = "spin_lock",
    hdrs = [
        "mcs.h",
        "tas.h",
        "ticket.h",
    ],
    linkopts = [
        "-lm",
    ],
)

cc_binary(
    name = "spin_lock_bench",
    srcs = ["spin_lock_bench.cc"],
    deps = [
        ":spin_lock",
        "//third_party/benchmark"
    ],
)
