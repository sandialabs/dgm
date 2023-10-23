#!/bin/bash
./cleanup ; env DGM_COLOR_OUTPUT=1 ./run.csh ; cat heat.ocs
./cleanup ; env DGM_COLOR_OUTPUT=1 ./run_rol.sh ; cat heat.ocs
