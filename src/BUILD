package(default_visibility = ["//visibility:public"])

cc_library(
    name = "rtweekend",
    hdrs = ["rtweekend.h"],
)

cc_library(
    name = "sphere",
    hdrs = ["sphere.h"],
    deps = [
        ":hittable",
        ":ray",
        ":vec",
    ],
)

cc_library(
    name = "hittable_list",
    hdrs = ["hittable_list.h"],
    deps = [
        ":hittable",
        ":ray",
    ],
)

cc_library(
    name = "hittable",
    hdrs = ["hittable.h"],
    deps = [
        ":ray",
        ":vec",
    ],
)

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
