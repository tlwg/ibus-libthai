#!/bin/sh

set -x

autopoint -f
aclocal
autoheader
automake --add-missing
autoconf -f

