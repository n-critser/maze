#!/usr/bin/bash

RECT=rectangle.png
LINE=line.png
HEIGHT=350
WIDTH=265
arrow_head="l -15,-5  +5,+5  -5,+5  +15,-5 z"
ARR_PNG=arrow_horizontal.png
convert -size ${HEIGHT}x${WIDTH}  xc:skyblue -fill white -stroke black \
        -draw "rectangle 20,10 80,50" \
        ${RECT}

convert -size ${HEIGHT}x${WIDTH} xc:lightblue \
        -fill white -stroke black -draw "line 95,35 195,155" \
        ${LINE}




convert -size 100x60 xc: -draw 'line 80,50 145,50' \
        -draw "stroke blue fill skyblue path 'M 145,50  $arrow_head' " \
        ${ARR_PNG}


convert ${LINE} ${RECT} ${ARR_PNG}  -composite \
        -draw 'fill red   circle    25,80  25,98' \
        -draw 'fill green circle    75,80  75,98' \
        -draw 'fill blue  circle   125,80 125,98' \
        class_connect.png

rm ${ARR_PNG}
