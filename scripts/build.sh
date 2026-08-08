#!/bin/bash

TARGET_DIR=$1

echo "================= BUILD START $TARGET_DIR ================="

mkdir -p src/$TARGET_DIR/build
clang src/$TARGET_DIR/main.c -o src/$TARGET_DIR/build/main

echo "================= BUILD END $TARGET_DIR ================="
