package(default_visibility = ["//visibility:public"])

cc_library(
    name = "library",
    srcs = ["library.cc"],
    hdrs = ["library.h"],
)

cc_test(
    name = "library_test",
    srcs = ["library_test.cc"],
    deps = [
        #":library",
        "@com_google_googletest//:gtest_main",
    ],
)
