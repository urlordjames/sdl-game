# sdl-game
An SDL2 game written in c++.

# dependancies

## NixOS/Nix
```sh
nix-shell
```

## Debian/Ubuntu
```sh
sudo apt-get update
sudo apt-get install build-essential cmake libsdl2-*
```

## Windows
https://stackoverflow.com/a/44347594 may work, haven't tested though.

# building
```sh
cmake .
make
```

# docker image
it exists I guess
```sh
docker build -t sdlbuild .
docker run --rm -it sdlbuild /bin/bash
```
