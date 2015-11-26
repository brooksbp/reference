package(default_visibility = ["//visibility:public"])

cc_library(
    name = "threading",
    srcs = [
        "platform_thread.h",
        "platform_thread.c",
    ],
    linkopts = [
        "-pthread",
    ],
    deps = [
        "//base",
    ],
)

cc_test(
    name = "platform_thread_test",
    srcs = ["platform_thread_test.cc"],
    deps = [
        ":threading",
        "//third_party/googletest:gtest_main",
    ],
)
