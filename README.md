# c-fundamentals

## check env

```bash
clang --version # Apple clang version 17.0.0 (clang-1700.6.3.2)
lldb --version # lldb-1703.0.236.21
bear --version # bear 4.2.0
```

## build and run

>`brew install bear` to create `compile_commands.json` automatically.
 
for debugger : configure app in CLion ide manually

```bash
# example
bear -- ./scripts/process-build.sh <target_dir> --debug --clean && ./build/main
```