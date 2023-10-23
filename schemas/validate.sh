#!/bin/bash
export PYTHONPATH=$DGM_DIST/schemas/validictory

# This way does not read $ref files from other sources as far as I can tell.
# ./validate.py input.json 

# This way we can sort of concatinate a bunch of json files together automatically.
$DGM_DIST/schemas/validate $1  $DGM_DIST/schemas/dgm.v4.json $DGM_DIST/schemas/Slice.json $DGM_DIST/schemas/Trapezodial.json 




