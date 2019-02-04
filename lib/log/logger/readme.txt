logger

Summary:
This is a multi-level logger which can output to file or standard output.

Due to it's compactness, ease of use and flexibility, this has been used as part
of a number of projects, some of which were quite large.

The use of C for this project was mainly because its inception was as part of a
much larger C project however it was also written with compactness and
efficiency in mind.

Indentation and different log levels are supported.

How it works:
A logger handle can be initialized for use. This can be passed on to logging
functions used throughout a project. When a null (0 valued pointer) is assigned
to a logger handle, all logging functions will do nothing.

During initialization, one may define to output to a file, to standard out, or
both.

One of several pre-defined log levels may be specified during initialization of
a logger handle.

Logging functions will take in a logger handle, a log level parameter and a log
message. If the log level parameter specified in logging functions is equal to
or of lower level than that of the handle, then the message will be displayed.

An indentation count stores the number of indentations which are set by indent
and outdent functions called on the logger handle.

How to use:
1: Assign 0 to a loghdl or void*.
2: Use logging functions as defined in the header file to log to the handle.
3: When uninitialized, the logging functions will safely do nothing. They may
   even be optimized out by the compiler.
4: Create the handle by calling createLoggerHandle. This takes three parameters:
   a) filename: is an output file name for all logging (can be set to null)
   b) level: the log level of the handle - any logs below or equal to this level
      will be displayed.
   c) std: 1 to support output to standard out or 0 otherwise.
5: Use logindent and logoutdent to increase/decrease the indentation
   respectively.
6: When finished, call destroyLoggerHandle.
7: Log levels are in this order:
      logsilent
      logminimal
      lognormal
      logmore
      logfull


Thanks

Duncan Camilleri
