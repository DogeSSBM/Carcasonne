#!/bin/bash
printf "\033c"
serverLibs="-lSDL2 -lSDL2_net -lm"
clientLibs="-lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_net -lm"
flags="-Winline"
gcc ./Server/main.c $serverLibs $flags -o ./server
gcc ./Client/main.c $clientLibs $flags -o ./client
