licenses(["notice"])

cc_library(
    name = "benchmark",
    visibility = ["//visibility:public"],
    srcs = [
        "upstream/src/arraysize.h",
        "upstream/src/benchmark.cc",
        "upstream/src/check.h",
        "upstream/src/colorprint.cc",
        "upstream/src/colorprint.h",
        "upstream/src/commandlineflags.cc",
        "upstream/src/commandlineflags.h",
        "upstream/src/console_reporter.cc",
        "upstream/src/csv_reporter.cc",
        "upstream/src/cycleclock.h",
        "upstream/src/internal_macros.h",
        "upstream/src/json_reporter.cc",
        "upstream/src/log.cc",
        "upstream/src/log.h",
        "upstream/src/mutex.h",
        "upstream/src/re.h",
        "upstream/src/reporter.cc",
       #"upstream/src/re_posix.cc",
        "upstream/src/re_std.cc",
        "upstream/src/sleep.cc",
        "upstream/src/sleep.h",
        "upstream/src/stat.h",
        "upstream/src/string_util.cc",
        "upstream/src/string_util.h",
        "upstream/src/sysinfo.cc",
        "upstream/src/sysinfo.h",
        "upstream/src/walltime.cc",
        "upstream/src/walltime.h",
    ],
    includes = ["upstream/include"],
    defines = [
        "HAVE_STD_REGEX",
    ],
    copts = [
        "-Ithird_party/benchmark/upstream"
    ],
    linkopts = [
        "-lm",
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
