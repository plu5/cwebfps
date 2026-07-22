# cwebfps
Currently it's just a green screen

Basic FPS game attempt for the web with [raylib](https://github.com/raysan5/raylib)

## Contents
1. [Cloning](#cloning)
1. [Building (Web)](#building-web)
1. [Hosting online](#hosting-online)

## Cloning
```sh
git clone --recurse-submodules --shallow-submodules https://github.com/plu5/cwebfps.git
```

## Building (Web)
1. Install emscripten if you don't have it already. `emcc` and `emar` need to be in PATH.
2. Build raylib:
   ```sh
   cd raylib/src
   emcc -c rcore.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
   emcc -c rshapes.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
   emcc -c rtextures.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
   emcc -c rtext.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
   emcc -c rmodels.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
   emcc -c raudio.c -Os -Wall -DPLATFORM_WEB
   emar rcs libraylib.a rcore.o rshapes.o rtextures.o rtext.o rmodels.o raudio.o
   ```
3. Build the game:
   ```sh
   cd ../..
   make -C cwebfps
   ```
4. Host the game:
   ```sh
   cd cwebfps
   python -m http.server
   ```
5. It will be on http://127.0.0.1:8000/ on the same machine, or localip:8000 on other machines in the local network, where localip is the local ip of the device you're hosting on (`ip address` on Arch, and on other operating systems `ifconfig` or `ipconfig`).

## Hosting online
After building, upload the files `index.html`, `index.js`, `index.wasm`, `index.data`
