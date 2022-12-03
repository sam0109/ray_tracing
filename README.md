# basic_setup_cc

## Do once per repo:
- set compile_commands path to `${workspaceFolder}/compile_commands.json` in advanced section of "C/C++ Configurations"

## Do after changing / adding files:
- To refresh targets for autocomplete etc: `bazel run @hedron_compile_commands//:refresh_all`

## Do once in a while:
- Every once in a while, update the hashes in WORKSPACE to head