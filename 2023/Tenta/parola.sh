#!/bin/bash
seq 1 4 | xargs -n ./lettera.sh | tr -d '\n'