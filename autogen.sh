#!/bin/sh -ex

#libtoolize --force &> /dev/null
aclocal
autoheader
automake --add-missing --no-force
autoconf
exec ./configure $@

# COPYRIGHT --
#
# This file is part of libkdtree++, a C++ template KD-Tree sorting container.
# libkdtree++ is (c) 2004 Martin F. Krafft <krafft@ailab.ch>
# and distributed under the terms of the Artistic Licence.
# See the ./COPYING file in the source tree root for more information.
#
# THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES
# OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
