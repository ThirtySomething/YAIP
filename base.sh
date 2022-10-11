#!/usr/bin/env bash

PATH_SCRIPT=$(realpath "$0")
DIR_BASE=$(dirname "${PATH_SCRIPT}")
CLASSPATH=${DIR_BASE}:${DIR_BASE}/vendor/antlr4.jar/antlr-4.10.1-complete.jar:${CLASSPATH}

export DIR_BASE
export CLASSPATH
