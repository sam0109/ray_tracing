load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Googletest
http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/1f643f71d4151c3b364c0e9302042f7a6debd439.zip"],
  strip_prefix = "googletest-1f643f71d4151c3b364c0e9302042f7a6debd439",
)

# Hedron's Compile Commands Extractor for Bazel
# https://github.com/hedronvision/bazel-compile-commands-extractor
http_archive(
    name = "hedron_compile_commands",

    # Replace the commit hash in both places (below) with the latest, rather than using the stale one here.
    # Even better, set up Renovate and let it do the work for you (see "Suggestion: Updates" in the README).
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/a69b071b78120a6cdadc9f6a9968ed36c2206556.tar.gz",
    strip_prefix = "bazel-compile-commands-extractor-a69b071b78120a6cdadc9f6a9968ed36c2206556",
    # When you first run this tool, it'll recommend a sha256 hash to put here with a message like: "DEBUG: Rule 'hedron_compile_commands' indicated that a canonical reproducible form can be obtained by modifying arguments sha256 = ..."
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")
hedron_compile_commands_setup()

http_archive(
  name = "com_google_absl",
  urls = ["https://github.com/abseil/abseil-cpp/archive/4e5ff1559ca3bd7bb777a1c48106464cb656e041.zip"],
  strip_prefix = "abseil-cpp-4e5ff1559ca3bd7bb777a1c48106464cb656e041",
)

http_archive(
  name = "bazel_skylib",
  urls = ["https://github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz"],
  sha256 = "f7be3474d42aae265405a592bb7da8e171919d74c16f082a5457840f06054728",
)