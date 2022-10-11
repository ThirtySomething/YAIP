#!/usr/bin/env bash

PATH_SCRIPT=$(realpath "$0")
DIR_BASE=$(dirname "${PATH_SCRIPT}")

GRAMMAR=$1
if [[ -f ${GRAMMAR} ]]; then
    echo Create code from [${GRAMMAR}]
    source "${DIR_BASE}/antlr4.sh" -Dlanguage=Cpp -o "${DIR_BASE}/src/generated" -encoding UTF8 -no-listener -visitor "${GRAMMAR}"
else
    echo Grammar file [${GRAMMAR}] does not exist.
fi
