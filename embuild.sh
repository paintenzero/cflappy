#!/bin/bash
EMBUILD_DIR=embuild
if [ ! -d "$EMBUILD_DIR" ]; then
    mkdir embuild
fi

PRELOAD_IMAGES=`ls images/`
PRELOAD_ARG=""
for file in $PRELOAD_IMAGES
do
    PRELOAD_ARG="--preload-file images/$file $PRELOAD_ARG"
done

emcc background.c bird.c endgamescreen.c readyscreen.c startscreen.c walls.c sdlutils.c game.c main.c $PRELOAD_ARG -o ${EMBUILD_DIR}/flappy.html
exit 0
