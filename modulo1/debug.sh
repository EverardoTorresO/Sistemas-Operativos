#!/bin/bash
tmux splitw -h -p 50 "gdbserver :12345 ./modulo1.o"
tmux selectp -t 0
