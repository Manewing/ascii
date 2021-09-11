#!/bin/bash

set -eu -o pipefail

function report() {
  if ! [ $? -eq 0 ]; then
    echo "FAILURE" >&2
  else
    echo "SUCCESS" >&2
  fi
}
trap report EXIT

function checkref() {
  REF=$1
  shift
  TEMP=$(mktemp)
  "$ASCII" $@ > "$TEMP"
  echo "ascii $@ == $REF"
  diff "$TEMP" "$REF"
}

SCRIPTDIR="$(dirname "$0")"
REPOROOT="$(realpath "$SCRIPTDIR"/..)"

REFDIR="$SCRIPTDIR"

ASCII="$SCRIPTDIR/../ascii"
if ! [ -f $ASCII ]; then
  echo "$ASCII not build" >&2
  exit 1
fi

checkref "$REFDIR/ref.txt"
checkref "$REFDIR/ref_255.txt" 255
checkref "$REFDIR/ref_50_80.txt" 50 80
checkref "$REFDIR/ref_char.txt" -c @