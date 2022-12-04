package(default_visibility = ["//visibility:public"])

cc_library(
    name = "ray",
    hdrs = ["ray.h"],
    deps = [
        ":vec",
    ],
)

cc_library(
    name = "color",
    hdrs = ["color.h"],
    deps = [
        ":vec",
    ],
)

cc_library(
    name = "vec",
    hdrs = ["vec.h"],
    deps = [
        "@com_google_absl//absl/functional:function_ref",
        "@com_google_absl//absl/strings",
    ],
)

cc_test(
    name = "vec_test",
    srcs = ["vec_test.cc"],
    deps = [
        ":vec",
        "@com_google_googletest//:gtest_main",
    ],
)
