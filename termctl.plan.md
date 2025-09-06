# implementation details on linux:

-   using `tcsetattr` on either `stdin (fd 1)` or `stdout (fd 0)` sets it for both

# features that could be implemented:

## get window size

linux / posix: ioctl (TIOCGWINSZ) | man 2 ioctl_tty

## disable echo

linux / posix: termios (ECHO) | man 3 termios
