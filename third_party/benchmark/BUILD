licenses(["notice"])

cc_library(
    name = "benchmark",
    visibility = ["//visibility:public"],
    srcs = [
        "upstream/src/benchmark.cc",
        "upstream/src/colorprint.cc",
        "upstream/src/commandlineflags.cc",
        "upstream/src/console_reporter.cc",
        "upstream/src/csv_reporter.cc",
        "upstream/src/json_reporter.cc",
        "upstream/src/log.cc",
        "upstream/src/reporter.cc",
        "upstream/src/sleep.cc",
        "upstream/src/string_util.cc",
        "upstream/src/sysinfo.cc",
        "upstream/src/walltime.cc",

        "upstream/src/re_std.cc"
    ],
    includes = ["upstream/include"],
    defines = [
        "HAVE_STD_REGEX",
    ],
    copts = [
        "-Ithird_party/benchmark/upstream"
    ],
    linkopts = [
        "-pthread",
        "-flto",
    ],
)

cc_test(
    name = "basic_test",
    srcs = ["upstream/test/basic_test.cc"],
    deps = [":benchmark"],
)

cc_test(
    name = "benchmark_test",
    srcs = ["upstream/test/benchmark_test.cc"],
    deps = [":benchmark"],
)
