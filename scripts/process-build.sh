#!/bin/bash

set -e
shopt -s nullglob

TARGET_DIR="$1"
shift

AUTO_RUN=false
LIB_TYPE=""

while [[ $# -gt 0 ]]; do
  case "$1" in
    --run)
      AUTO_RUN=true
      ;;

    --lib=static)
      LIB_TYPE="static"
      ;;

    --lib=dynamic)
      LIB_TYPE="dynamic"
      ;;

    *)
      echo "❌ Unknown option: $1"
      exit 1
      ;;
  esac

  shift
done


SOURCE_DIR="src/$TARGET_DIR"
LIB_DIR="$SOURCE_DIR/lib"
BUILD_DIR="$SOURCE_DIR/build"

echo "================= BUILD START $TARGET_DIR ================="

mkdir -p "$BUILD_DIR"

OBJECT_FILES=()

#
# source
#

for SOURCE in "$SOURCE_DIR"/*.c; do
  NAME="$(basename "$SOURCE" .c)"

  PREPROCESSED="$BUILD_DIR/$NAME.i"
  ASSEMBLY="$BUILD_DIR/$NAME.s"
  OBJECT="$BUILD_DIR/$NAME.o"

  clang \
    -std=c23 \
    -E \
    "$SOURCE" \
    -o "$PREPROCESSED"

  clang \
    -std=c23 \
    -S \
    "$PREPROCESSED" \
    -o "$ASSEMBLY"

  clang \
    -c \
    "$ASSEMBLY" \
    -o "$OBJECT"

  OBJECT_FILES+=("$OBJECT")
done


#
# library
#

LINK_LIBS=()

if [[ -n "$LIB_TYPE" ]]; then
  LIB_SOURCES=("$LIB_DIR"/*.c)

  if ((${#LIB_SOURCES[@]} == 0)); then
    echo "❌ --lib=$LIB_TYPE specified, but no library sources found"
    exit 1
  fi

  echo "---- lib ($LIB_TYPE) ----"

  mkdir -p "$BUILD_DIR/lib"

  LIB_OBJECT_FILES=()

  for LIB_SOURCE in "${LIB_SOURCES[@]}"; do
    NAME="$(basename "$LIB_SOURCE" .c)"
    OBJ="$BUILD_DIR/lib/$NAME.o"

    clang \
      -std=c23 \
      -c \
      "$LIB_SOURCE" \
      -o "$OBJ"

    LIB_OBJECT_FILES+=("$OBJ")
  done

  case "$LIB_TYPE" in
    static)
      STATIC_LIB_PATH="$BUILD_DIR/lib/lib.a"

      ar rcs \
        "$STATIC_LIB_PATH" \
        "${LIB_OBJECT_FILES[@]}"

      LINK_LIBS+=("$STATIC_LIB_PATH")
      ;;

    dynamic)
      DYNAMIC_LIB_PATH="$BUILD_DIR/lib/lib.dylib"

      clang \
        -dynamiclib \
        "${LIB_OBJECT_FILES[@]}" \
        -o "$DYNAMIC_LIB_PATH"

      LINK_LIBS+=("$DYNAMIC_LIB_PATH")
      ;;
  esac
fi


#
# link
#

clang \
  "${OBJECT_FILES[@]}" \
  "${LINK_LIBS[@]}" \
  -o "$BUILD_DIR/main"

echo " ✅ link success!"
echo "================= BUILD END $TARGET_DIR ================="


#
# run
#

if [[ "$AUTO_RUN" == true ]]; then
  "$BUILD_DIR/main"
fi