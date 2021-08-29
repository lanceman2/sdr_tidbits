#!/bin/bash

set -euo pipefail
set -x

# Go to the directory there this script is.
cd $(dirname ${BASH_SOURCE[0]})

# needed for osc
export LD_LIBRARY_PATH=/usr/local/lib

set +e

deviceID="$(iio_info -S |\
 grep serial | awk '{print $9}' | sed -e 's/\[//g' -e 's/\]//g')"

# This osc program is very buggy.  This seems stop osc from crashing.
rm -f ${HOME}/.osc_profile.ini

osc -u $deviceID 

