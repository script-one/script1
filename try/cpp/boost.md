# boost

## Install

* 安裝 -- https://www.boost.org/doc/libs/1_49_0/more/getting_started/windows.html

The first thing many people want to know is, “how do I build Boost?” The good news is that often, there's nothing to build.

Nothing to Build?

Most Boost libraries are header-only: they consist entirely of header files containing templates and inline functions, and require no separately-compiled library binaries or special treatment when linking.

The only Boost libraries that must be built separately are:

Boost.Filesystem
Boost.GraphParallel
Boost.IOStreams
Boost.MPI
Boost.ProgramOptions
Boost.Python (see the Boost.Python build documentation before building and installing it)
Boost.Regex
Boost.Serialization
Boost.Signals
Boost.System
Boost.Thread
Boost.Wave

