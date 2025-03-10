# Set terminal to raw mode
stty raw

# Connect to the server using socat
socat -,raw,echo=0 TCP:127.0.0.1:3000

# After exiting socat, reset terminal settings to sane defaults
stty sane
