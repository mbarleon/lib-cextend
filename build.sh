#!/usr/bin/env bash

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
    cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    if make -j"$(nproc)" cextended; then
        _success "compiled cextended"
        exit 0
    fi
    _error "compilation error" "failed to compile cextended"
}

function _debug()
{
    if ! { command -v cmake > /dev/null; } 2>&1; then
        _error "command 'cmake' not found" "please install 'cmake'"
    fi
    _success "command 'cmake' found, building..."
    mkdir -p build
    cd build || _error "mkdir failed"
    cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DENABLE_DEBUG=ON
    if make -j"$(nproc)" cextended; then
        _success "compiled cextended"
        exit 0
    fi
    _error "compilation error" "failed to compile cextended"
}

function _tests_run()
{
    if ! { command -v cmake > /dev/null; } 2>&1; then
        _error "command 'cmake' not found" "please install 'cmake'"
    fi
    _success "command 'cmake' found, building..."
    mkdir -p build
    cd build || _error "mkdir failed"
    cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
    if ! make -j"$(nproc)" unit_tests; then
        _error "unit tests compilation error" "failed to compile unit_tests"
    fi
    cd .. || _error "cd failed"
    if ! ./unit_tests; then
        _error "unit tests error" "unit tests failed!"
    fi
    _success "unit tests succeed!"
    if [ "$(uname -s)" == 'Darwin' ]; then
        xcrun llvm-profdata merge -sparse unit_tests-*.profraw -o unit_tests.profdata
        xcrun llvm-cov report ./unit_tests -instr-profile=unit_tests.profdata -ignore-filename-regex='.*/tests/.*' -enable-name-compression > code_coverage.txt
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
    rm -rf cextended unit_tests plugins code_coverage.txt unit_tests-*.profraw unit_tests.profdata \
    libs/libcextended.* vgcore* cmake-build-debug a.out
}

for args in "$@"
do
    case $args in
        -h|--help)
            cat << EOF
USAGE:
      $0    builds cextended project

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
