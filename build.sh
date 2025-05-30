#!/usr/bin/env bash

CMAKE_SOURCE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BOLD="\033[1m"
GREEN="\033[1;32m"
RED="\033[1;31m"
ILC="\033[3m"
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

function _all()
{
    if ! { command -v cmake > /dev/null; } 2>&1; then
        _error "command 'cmake' not found" "please install 'cmake'"
    fi
    _success "command 'cmake' found, building..."
    mkdir -p build
    cd build || _error "mkdir failed"
    cmake "${CMAKE_SOURCE_DIR}" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    if make -j"$(nproc)" cextend; then
        _success "compiled cextend"
        exit 0
    fi
    _error "compilation error" "failed to compile cextend"
}

function _debug()
{
    if ! { command -v cmake > /dev/null; } 2>&1; then
        _error "command 'cmake' not found" "please install 'cmake'"
    fi
    _success "command 'cmake' found, building..."
    mkdir -p build
    cd build || _error "mkdir failed"
    cmake "${CMAKE_SOURCE_DIR}" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCEXTEND_ENABLE_DEBUG=ON
    if make -j"$(nproc)" cextend; then
        _success "compiled cextend"
        exit 0
    fi
    _error "compilation error" "failed to compile cextend"
}

function _tests_run()
{
    if ! { command -v cmake > /dev/null; } 2>&1; then
        _error "command 'cmake' not found" "please install 'cmake'"
    fi
    _success "command 'cmake' found, building..."
    mkdir -p build
    cd build || _error "mkdir failed"
    cmake "${CMAKE_SOURCE_DIR}" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
    if ! make -j"$(nproc)" cextend_unit_tests; then
        _error "unit tests compilation error" "failed to compile cextend_unit_tests"
    fi
    cd .. || _error "cd failed"
    if ! ./cextend_unit_tests; then
        _error "unit tests error" "unit tests failed!"
    fi
    _success "unit tests succeed!"
    if [ "$(uname -s)" == 'Darwin' ]; then
        xcrun llvm-profdata merge -sparse cextend_unit_tests-*.profraw -o cextend_unit_tests.profdata
        xcrun llvm-cov report ./cextend_unit_tests -instr-profile=cextend_unit_tests.profdata -ignore-filename-regex='.*/tests/.*' -enable-name-compression > code_coverage.txt
    else
        gcovr -r . --exclude tests/ > code_coverage.txt
    fi
    cat code_coverage.txt
}

function _clean()
{
    rm -rf build
}

function _fclean()
{
    _clean
    rm -rf cextend cextend_unit_tests plugins code_coverage.txt cextend_unit_tests-*.profraw cextend_unit_tests.profdata \
    libs/libcextend.* vgcore* cmake-build-debug a.out
}

for args in "$@"
do
    case $args in
        -h|--help)
            cat << EOF
USAGE:
    $0    builds cextend project

ARGUMENTS:
    $0 [-h|--help]    displays this message
    $0 [-d|--debug]   debug flags compilation
    $0 [-c|--clean]   clean the project
    $0 [-f|--fclean]  fclean the project
    $0 [-t|--tests]   run unit tests
EOF
        exit 0
        ;;
    -c|--clean)
        _clean
        exit 0
        ;;
    -f|--fclean)
        _fclean
        exit 0
        ;;
    -d|--debug)
        _debug
        ;;
    -t|--tests)
        _tests_run
        exit 0
        ;;
    -r|--re)
        _fclean
        _all
        ;;
    *)
        _error "Invalid arguments: " "$args"
    esac
done

_all
