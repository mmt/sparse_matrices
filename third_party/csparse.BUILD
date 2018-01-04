cc_library(
    name = "main",
    srcs = glob(
        ["Source/*.c"],
    ),
    hdrs = glob([
        "Include/**/*.h",
    ]),
    includes = ["Include"],
    data = glob(["Matrix/**"]),
    visibility = ["//visibility:public"],
)
