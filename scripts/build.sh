#!/bin/bash

TARGET_DIR=$1
AUTO_RUN="${2:-}"

echo "================= BUILD START $TARGET_DIR ================="

mkdir -p src/$TARGET_DIR/build
clang \
  -std=c23 \
  -Wall \
  -Wextra \
  -Wpedantic \
  -g \
  src/$TARGET_DIR/main.c \
  -o src/$TARGET_DIR/build/main

echo "================= BUILD END $TARGET_DIR ================="

if [ "$AUTO_RUN" = "--run" ]; then
  ./src/$TARGET_DIR/build/main
fi