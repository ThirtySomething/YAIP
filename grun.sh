#!/usr/bin/env bash

PATH_SCRIPT=$(realpath "$0")
DIR_BASE=$(dirname "${PATH_SCRIPT}")

source ${DIR_BASE}/base.sh

java org.antlr.v4.gui.TestRig "$@"