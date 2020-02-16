cc_library(
  name = "tree_lib",
  hdrs = ["tree.h"],
)

cc_test(
  name = "tree_test",
  srcs = ["tree_test.cc"],
  deps = [
    ":tree_lib",
    "@gtest//:gtest_main",
    "@absl//absl/random:random",
    "@absl//absl/algorithm:container",
  ],
)