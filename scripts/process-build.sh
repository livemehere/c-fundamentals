#!/bin/bash

set -e

TARGET_DIR="$1"
AUTO_RUN="${2:-}"

SOURCE_DIR="src/$TARGET_DIR"
BUILD_DIR="$SOURCE_DIR/build"

echo "================= BUILD START $TARGET_DIR ================="

mkdir -p "$BUILD_DIR"
echo " ✅ create build directory $BUILD_DIR"

OBJECT_FILES=()

for SOURCE in "$SOURCE_DIR"/*.c; do
  NAME="$(basename "$SOURCE" .c)"

  PREPROCESSED="$BUILD_DIR/$NAME.i"
  ASSEMBLY="$BUILD_DIR/$NAME.s"
  OBJECT="$BUILD_DIR/$NAME.o"

  echo " 🔨 $NAME.c"

  # preprocess
  clang \
    -std=c23 \
    -E \
    "$SOURCE" \
    -o "$PREPROCESSED"

  # compile -> assembly
  clang \
    -std=c23 \
    -S \
    "$PREPROCESSED" \
    -o "$ASSEMBLY"

  # assemble -> object
  clang \
    -c \
    "$ASSEMBLY" \
    -o "$OBJECT"

  OBJECT_FILES+=("$OBJECT")
done

for obj in "${OBJECT_FILES[@]}"; do
  echo " 📂 $obj"
done

# link
clang \
  "${OBJECT_FILES[@]}" \
  -o "$BUILD_DIR/main"

echo " ✅ link success!"
echo "================= BUILD END $TARGET_DIR ================="

if [[ "$AUTO_RUN" == "--run" ]]; then
  "$BUILD_DIR/main"
fi