package(default_visibility = ["//visibility:public"])

java_library(
    name = "algs4",
    srcs = glob(["src/**/*.java"]),
)

java_test(
    name = "CounterTest",
    srcs = ["test/algs4/CounterTest.java"],
    deps = [
        ":algs4",
        "//third_party/java:junit",
    ],
)
