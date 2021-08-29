#!/bin/bash

set -ex


qb_tag=0.2

qb_url=https://raw.githubusercontent.com/lanceman2/quickbuild/\
$qb_tag/quickbuild.make

qb_sha512sum=d72c983ea6e308312be9b2e2503c754840c98b7d78\
f3b37c64c45d84fc844e0b4773e33ad3addf8267d84ccc626ae0\
afb41530f46769f6584da279c7fd4519e3

if [ ! -e quickbuild.make ] ; then
    wget -O quickbuild.make --no-check-certificate $qb_url
fi


if ! echo "$qb_sha512sum  quickbuild.make" | sha512sum -c ; then
    mv quickbuild.make xxx_quickbuild.make_HASH_FAIL
    set +x
    echo "$0 Failed"
    exit 1
fi


[ -f config.make ] || cp config.make.example config.make


set +x
echo "$0 Success"
