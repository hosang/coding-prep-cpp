load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
     name = "absl",
     urls = ["https://github.com/abseil/abseil-cpp/archive/master.zip"],
     strip_prefix = "abseil-cpp-master",
)

git_repository(
    name = "gtest",
    remote = "https://github.com/google/googletest.git",
    commit = "d25268a55f6f6f38c65a7d1b7b119e33a46d1688",
)