_COPTS = [
  #  "-Waggregate-return",  # Disable for Eigen.
  "-Wall",
  "-Wcast-align",
  "-Wcast-qual",
  "-Wconversion",
  "-Wdisabled-optimization",
  "-Weffc++",
  "-Werror",
  "-Wextra",
  "-Wfloat-equal",
  "-Wformat-nonliteral",
  "-Wformat-security",
  "-Wformat-y2k",
  "-Wformat=2",
  "-Wimport",
  "-Winit-self",
  "-Winline",
  "-Winvalid-pch",
  "-Wlong-long",
  "-Wmissing-field-initializers",
  "-Wmissing-format-attribute",
  "-Wmissing-noreturn",
  "-Wpacked",
  "-Wpadded",
  "-Wpointer-arith",
  "-Wredundant-decls",
  "-Wshadow",
  "-Wstack-protector",
  "-Wstrict-aliasing=2",
  "-Wswitch-default",
  "-Wswitch-enum",
  "-Wunreachable-code",
  "-Wunused",
  "-Wunused-parameter",
  "-Wvariadic-macros",
  "-Wwrite-strings",
  "-pedantic",
  "-pedantic-errors",
]

def project_cc_binary(copts=[], **kwargs):
  copts = _COPTS + copts
  native.cc_binary(copts=copts, **kwargs)

def project_cc_library(copts=[], **kwargs):
  copts = _COPTS + copts
  native.cc_library(copts=copts, **kwargs)

def project_cc_test(copts=[], deps=[], **kwargs):
  copts = _COPTS + [
    "-Iexternal/gtest/include",
    "-Wno-aggregate-return",
    "-Wno-padded",
    "-Wno-long-long",
    "-Wno-effc++"
  ] + copts
  deps = deps + [
    "@gtest//:main"
  ]
  native.cc_test(copts=copts, deps=deps, **kwargs)

