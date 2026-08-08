#!/bin/bash

set -e

TARGET_DIR=$1
AUTO_RUN="${2:-}"

SOURCE_DIR="src/$TARGET_DIR"
BUILD_DIR="src/$TARGET_DIR/build"

echo "================= BUILD START $TARGET_DIR ================="

mkdir -p src/$TARGET_DIR/build
echo "✅ create build directory $BUILD_DIR"

for SOURCE in $SOURCE_DIR/*.c; do
  echo "$SOURCE"
done


exit;


# pre process
clang \
  -std=c23 \
  -E \
  $SOURCE_DIR/main.c \
  -o $BUILD_DIR/main.i

# compile -> assembly
clang \
  -std=c23 \
  -S \
  $BUILD_DIR/main.i \
  -o $BUILD_DIR/main.s

# assemble -> object
clang \
  -c \
  $BUILD_DIR/main.s \
  -o $BUILD_DIR/main.o

clang \
  -c \
  $SOURCE_DIR/foo.c \
  -o $BUILD_DIR/foo.o

# link
clang \
  $BUILD_DIR/main.o \
  $BUILD_DIR/foo.o \
  -o $BUILD_DIR/main

echo "================= PREPROCESS END $TARGET_DIR ================="

if [ "$AUTO_RUN" = "--run" ]; then
  ./$BUILD_DIR/main
fi
