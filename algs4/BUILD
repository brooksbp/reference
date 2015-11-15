package(default_visibility = ["//visibility:public"])

java_library(
    name = "algs4",
    srcs = glob(["src/**/*.java"]),
)

test_suite(
    name = "all_tests",
)

java_test(
    name = "BinarySearchTest",
    srcs = ["test/algs4/BinarySearchTest.java"],
    args = ["algs4.BinarySearchTest"],
    deps = [
        ":algs4",
        "//third_party/java:junit",
    ],
)

java_test(
    name = "CounterTest",
    srcs = ["test/algs4/CounterTest.java"],
    args = ["algs4.CounterTest"],
    deps = [
        ":algs4",
        "//third_party/java:junit",
    ],
)

load("/build_tools/javadoc", "javadoc")

javadoc(
    name = "algs4-javadoc",
    srcs = glob(["src/**/*.java"]),
)
