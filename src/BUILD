package(default_visibility = ["//visibility:public"])

cc_library(
    name = "vec",
    hdrs = ["vec.h"],
)

cc_test(
    name = "vec_test",
    srcs = ["vec_test.cc"],
    deps = [
        ":vec",
        "@com_google_googletest//:gtest_main",
    ],
)
