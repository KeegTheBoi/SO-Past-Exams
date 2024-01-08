#!/bin/bash
cut -d ' ' -f 1-10 prova.txt | tr ' \t' '\n' | egrep -c "^int$"


