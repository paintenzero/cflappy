cflappy
=======

FlappyBird clone on ANSI C and SDL

Building
========

It can be built with cmake tools, just clone this repository, create build folder anywhere and execute
`cmake <path to cloned repo>`
and then
`make`

For example:

`git clone https://github.com/paintenzero/cflappy.git cflappy
cd cflappy
mkdir build
cd build
cmake ..
make
./cflappy`

Dependencies
============

Needs developer versions of SDL, SDL-image and SDL-gfx. In ubuntu you can install them with command:
`sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-gfx1.2-dev`

Building with Emscripten
========================

Build [emscripten](https://github.com/kripken/emscripten/wiki), then run `embuild.sh`. Application will be built in embuild folder.

Demo
====
[Emsripten](https://github.com/kripken/emscripten/wiki) built demo can be found [here](http://bit.ly/emflappy).

Credits
=======
Thanks to *Dong Nguyen* for original version of [Flappy Bird](http://en.wikipedia.org/wiki/Flappy_Bird)

Thanks to *[Hetal](http://lanica.co/author/hetal/)* for [graphics](http://lanica.co/flappy-clone/)
