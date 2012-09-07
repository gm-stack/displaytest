#!/bin/bash
gcc main.c -std=c99 -o displaytest `pkg-config sdl --static --libs --cflags`
