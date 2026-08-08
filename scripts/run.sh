#!/bin/bash

TARGET_DIR=$1

echo "================= RUN $TARGET_DIR ================="

./src/$TARGET_DIR/build/main

echo "================= END $TARGET_DIR ================="
