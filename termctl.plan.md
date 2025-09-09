# implementation details on linux:

-   using `tcsetattr` on either `stdin (fd 0)` or `stdout (fd 1)` sets it for both

# features that could be implemented:

## get window size

linux / posix: ioctl (TIOCGWINSZ) | man 2 ioctl_tty

## disable echo

linux / posix: termios (ECHO) | man 3 termios

## canonical mode

linux / posix: termios (ICANON) | man 3 termios
