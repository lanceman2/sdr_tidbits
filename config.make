# The file defines possible make configuration variables.
#
# This make file is used when building/installing using the quickbuild
# build system to build/install.
#
# We try to keep similar make variables in the GNU autotools build method.
#
# The optionally built files are automatically added based on running
# programs like 'pkg-config' in the quickbuild makefiles (Makefile) to see
# if dependences are available.


# We really want there to be very little to configure in this file:

PREFIX = /usr/local/encap/sdr_tidbits-0.0

# Set CPPFLAGS for debug build options:
#
#
# SPEW_LEVEL_* controls macros in lib/debug.h, if it exists
#
# The following may be defined; defining them turns on the following CPP
# macro functions that are in debug.h and debug.c.
#
#
# DEBUG             -->  DASSERT()
#
# SPEW_LEVEL_DEBUG  -->  DSPEW() INFO() NOTICE() WARN() ERROR()
# SPEW_LEVEL_INFO   -->  INFO() NOTICE() WARN() ERROR()
# SPEW_LEVEL_NOTICE -->  NOTICE() WARN() ERROR()
# SPEW_LEVEL_WARN   -->  WARN() ERROR()
# SPEW_LEVEL_ERROR  -->  ERROR()
#
# always on is      -->  ASSERT()


# Example:
#CPPFLAGS := -DSPEW_LEVEL_NOTICE
CPPFLAGS := -DDEBUG -DSPEW_LEVEL_DEBUG


# C compiler option flags
CFLAGS := -g -Wall -Werror

# C++ compiler option flags
CXXFLAGS := -g -Wall -Werror
