licenses(["notice"])

cc_library(
    name = "gtest",
    visibility = ["//visibility:public"],
    srcs = glob(["upstream/googletest/include/gtest/internal/*.h"]) + [
        "upstream/googletest/src/gtest-death-test.cc",
        "upstream/googletest/src/gtest-filepath.cc",
        "upstream/googletest/src/gtest-internal-inl.h",
        "upstream/googletest/src/gtest-port.cc",
        "upstream/googletest/src/gtest-printers.cc",
        "upstream/googletest/src/gtest-test-part.cc",
        "upstream/googletest/src/gtest-typed-test.cc",
        "upstream/googletest/src/gtest.cc",
    ],
    hdrs = [
        "upstream/googletest/include/gtest/gtest-death-test.h",
        "upstream/googletest/include/gtest/gtest-message.h",
        "upstream/googletest/include/gtest/gtest_pred_impl.h",
        "upstream/googletest/include/gtest/gtest-test-part.h",
        "upstream/googletest/include/gtest/gtest.h",
        "upstream/googletest/include/gtest/gtest-param-test.h",
        "upstream/googletest/include/gtest/gtest-printers.h",
        "upstream/googletest/include/gtest/gtest-spi.h",
        "upstream/googletest/include/gtest/gtest-typed-test.h",
    ],
    includes = ["upstream/googletest/include"],
    copts = ["-Ithird_party/googletest/upstream/googletest"],
    deps = ["//third_party/gflags"],
    testonly = 1,
)

cc_library(
    name = "gtest_main",
    visibility = ["//visibility:public"],
    srcs = ["upstream/googletest/src/gtest_main.cc"],
    deps = [":gtest"],
    testonly = 1,
)
