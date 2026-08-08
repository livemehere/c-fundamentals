#!/bin/bash

TARGET_DIR=$1
AUTO_RUN="${2:-}"

echo "================= PREPROCESS START $TARGET_DIR ================="

mkdir -p src/$TARGET_DIR/build
clang \
  -std=c23 \
  -E \
  src/$TARGET_DIR/main.c \
  -o src/$TARGET_DIR/build/main.i

echo "================= PREPROCESS END $TARGET_DIR ================="