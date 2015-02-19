#!/bin/bash

for f in *.3ds;
do
    name=${f%\.*}
    newname=${name}.bin
    echo "Generating bin for $f..."
    3ds2bin $f $newname
done