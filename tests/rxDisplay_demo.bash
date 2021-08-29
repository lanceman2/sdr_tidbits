#!/bin/bash

set -euo pipefail
set -x

# Go to the directory there this script is.
cd $(dirname ${BASH_SOURCE[0]})

# ./8bitsToEachFloat < /dev/urandom | hexdump -v

make


./8bitsToEachFloat < /dev/urandom | grrun ./scope.py &


airspyhf_rx -r stdout | grrun ./scope.py &

# needed for osc
export LD_LIBRARY_PATH=/usr/local/lib

set +e

deviceID="$(iio_info -S |\
 grep serial | awk '{print $9}' | sed -e 's/\[//g' -e 's/\]//g')"

# This osc program is very buggy.  This seems to fix letting it run
rm -f ${HOME}/.osc_profile.ini

osc -u $deviceID &

wait

