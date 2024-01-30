#!/bin/bash

#flag -d ottiene le sole directory
#flag -t ordina in base all'ultima modifica
ls -dt $(find /usr/include/ -type d -name "*a*") | head -1
