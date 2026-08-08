#!/bin/bash

set -e

TARGET_DIR=$1
AUTO_RUN="${2:-}"

echo "================= PREPROCESS START $TARGET_DIR ================="

mkdir -p src/$TARGET_DIR/build

# pre process
clang \
  -std=c23 \
  -E \
  src/$TARGET_DIR/main.c \
  -o src/$TARGET_DIR/build/main.i

# compile -> assembly
clang \
  -std=c23 \
  -S \
  src/$TARGET_DIR/build/main.i \
  -o src/$TARGET_DIR/build/main.s

# assemble -> object
clang \
  -c \
  src/$TARGET_DIR/build/main.s \
  -o src/$TARGET_DIR/build/main.o

clang \
  -c \
  src/$TARGET_DIR/foo.c \
  -o src/$TARGET_DIR/build/foo.o

# link
clang \
  src/$TARGET_DIR/build/main.o \
  src/$TARGET_DIR/build/foo.o \
  -o src/$TARGET_DIR/build/main

echo "================= PREPROCESS END $TARGET_DIR ================="

if [ "$AUTO_RUN" = "--run" ]; then
  ./src/$TARGET_DIR/build/main
fi
