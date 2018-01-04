load("//bazel:cc.bzl", "project_cc_test", "project_cc_binary", "project_cc_library")

project_cc_library(
    name = "csparse_matrices",
    srcs = ["matrices.cc"],
    hdrs = ["matrices.h"],
    deps = [
        "@csparse//:main",
    ],
    visibility = [
        "//visibility:public"
    ],
)

project_cc_library(
    name = "eigen_util",
    srcs = ["eigen_util.cc"],
    hdrs = ["eigen_util.h"],
    deps = [
        "@csparse//:main",
        "@eigen//:eigen",
    ],
    visibility = [
        "//visibility:public"
    ],
)

project_cc_test(
    name = "eigen_util_test",
    srcs = ["eigen_util_test.cc"],
    deps = [
        ":eigen_util",
    ],
)
