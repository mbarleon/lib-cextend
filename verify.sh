#!/usr/bin/env bash

GREEN="\033[1;32m"
RED="\033[1;31m"
ILC="\033[3m"
ORG="\033[1;33m"
RST="\033[0m"

function _error()
{
    echo -e "${RED}${BOLD}[❌] ERROR:\n${RST}\t$1\n\t${ILC}\"$2\"${RST}"
    exit 84
}

function _success()
{
    echo -e "${GREEN}[✅] SUCCESS:\t${RST} ${ILC}$1${RST}"
}

function _info()
{
    echo -e "${ORG}[🚧] RUNNING:\t${RST} ${ILC}$1${RST}"
}

set -e

BUILD_DIR="."
CLANG_TIDY_BIN="clang-tidy"
CLANG_TIDY_OPTIONS="-p=${BUILD_DIR}"
SOURCE_FILES=$(find src include -type f \( -name '*.cpp' -o -name '*.c' -o -name '*.h' -o -name '*.hpp' \))

if ! { command -v ${CLANG_TIDY_BIN} > /dev/null; } 2>&1; then
    _error "command '${CLANG_TIDY_BIN}' not found" "please install '${CLANG_TIDY_BIN}'"
fi

_success "Running clang-tidy on source files" "${SOURCE_FILES}"

FAILED=0

for FILE in $SOURCE_FILES; do
    _info "Checking $FILE"
    $CLANG_TIDY_BIN "$FILE" $CLANG_TIDY_OPTIONS || FAILED=1
done

if [ "$FAILED" -ne 0 ]; then
    _error "clang-tidy failed" "clang-tidy found issues 😢"
fi

_success "clang-tidy" "passed with no issues"
