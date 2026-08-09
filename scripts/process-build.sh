#!/bin/bash

set -e
shopt -s nullglob

#
# args
#

if [[ $# -lt 1 ]]; then
  echo "Usage:"
  echo "  ./build.sh <target_dir> [--run] [--debug] [--clean] [--lib=static|dynamic]"
  exit 1
fi

TARGET_DIR="$1"
shift

AUTO_RUN=false
LIB_TYPE=""
OPT="-O0"
DEBUG_FLAG=""
CLEAN=false

while [[ $# -gt 0 ]]; do
  case "$1" in
    --run)
      AUTO_RUN=true
      ;;

    --debug)
      DEBUG_FLAG="-g"
      ;;

    --clean)
      CLEAN=true
      ;;

    --lib=static)
      LIB_TYPE="static"
      ;;

    --lib=dynamic)
      LIB_TYPE="dynamic"
      ;;

      *)
      echo "❌ unknown option: $1"
      echo "Usage:"
      echo "  ./build.sh <target_dir> [--run] [--debug] [--clean] [--lib=static|dynamic]"
      exit 1
      ;;
  esac

  shift
done


#
# path (루트 build/ 폴더로 고정)
#

SOURCE_DIR="src/$TARGET_DIR"
LIB_DIR="$SOURCE_DIR/lib"
BUILD_DIR="build" # 👈 기존 "$SOURCE_DIR/build"에서 프로젝트 최상위 "build"로 변경!

echo "================= BUILD START $TARGET_DIR ================="

if [[ "$CLEAN" == true ]]; then
  if [[ -d "$BUILD_DIR" ]]; then
    echo " 🧹 remove build directory: $BUILD_DIR"
    rm -rf "$BUILD_DIR"
  fi
fi

mkdir -p "$BUILD_DIR"

echo " ✅ create build directory: $BUILD_DIR"


#
# compile main sources
#

OBJECT_FILES=()

for SOURCE in "$SOURCE_DIR"/*.c; do
  NAME="$(basename "$SOURCE" .c)"

  PREPROCESSED="$BUILD_DIR/$NAME.i"
  ASSEMBLY="$BUILD_DIR/$NAME.s"
  OBJECT="$BUILD_DIR/$NAME.o"

  echo " 🔨 compile: $SOURCE"

  #
  # preprocess
  #

  clang \
    -std=c23 \
    -E \
    "$SOURCE" \
    -o "$PREPROCESSED"

  #
  # compile -> assembly
  #

  clang \
    -std=c23 \
    $OPT \
    $DEBUG_FLAG \
    -S \
    "$PREPROCESSED" \
    -o "$ASSEMBLY"

  #
  # assemble -> object
  #

  clang \
    -c \
    "$ASSEMBLY" \
    -o "$OBJECT"

  OBJECT_FILES+=("$OBJECT")
done


#
# print objects
#

echo
echo "---- objects ----"

for OBJECT in "${OBJECT_FILES[@]}"; do
  echo " 📦 $OBJECT"
done


#
# library
#

LINK_LIBS=()

if [[ -n "$LIB_TYPE" ]]; then
  echo
  echo "---- library ($LIB_TYPE) ----"

  LIB_SOURCES=("$LIB_DIR"/*.c)

  if ((${#LIB_SOURCES[@]} == 0)); then
    echo " ⚠️ no library sources found"
    echo "    $LIB_DIR/*.c"
    echo "    skip library build"
  else
    LIB_BUILD_DIR="$BUILD_DIR/lib"

    mkdir -p "$LIB_BUILD_DIR"

    LIB_OBJECT_FILES=()

    #
    # compile library sources
    #

    for LIB_SOURCE in "${LIB_SOURCES[@]}"; do
      NAME="$(basename "$LIB_SOURCE" .c)"
      OBJECT="$LIB_BUILD_DIR/$NAME.o"

      echo " 🔨 compile library: $LIB_SOURCE"

      clang \
        -std=c23 \
        $OPT \
        $DEBUG_FLAG \
        -c \
        "$LIB_SOURCE" \
        -o "$OBJECT"

      LIB_OBJECT_FILES+=("$OBJECT")
    done


    #
    # create library
    #

    case "$LIB_TYPE" in
      static)
        LIB_PATH="$LIB_BUILD_DIR/lib.a"

        echo " 📚 create static library: $LIB_PATH"

        ar \
          rcs \
          "$LIB_PATH" \
          "${LIB_OBJECT_FILES[@]}"

        LINK_LIBS+=("$LIB_PATH")
        ;;

      dynamic)
        LIB_PATH="$LIB_BUILD_DIR/lib.dylib"

        echo " 📚 create dynamic library: $LIB_PATH"

        clang \
          -dynamiclib \
          "${LIB_OBJECT_FILES[@]}" \
          -o "$LIB_PATH"

        LINK_LIBS+=("$LIB_PATH")
        ;;
    esac
  fi
fi


#
# link
#

echo
echo "---- link ----"

clang \
  $DEBUG_FLAG \
  "${OBJECT_FILES[@]}" \
  "${LINK_LIBS[@]}" \
  -o "$BUILD_DIR/main"

echo " ✅ link success: $BUILD_DIR/main"

echo
echo "================= BUILD END $TARGET_DIR ================="


#
# run
#

if [[ "$AUTO_RUN" == true ]]; then
  echo
  echo "---- run ----"

  "$BUILD_DIR/main"
fi