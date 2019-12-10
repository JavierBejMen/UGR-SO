#!/bin/bash
# Actividad 1.1
# decompress files
7z x ~/Documents/UGR/SO/Fedora14-x86-root_fs.gz -o/tmp/
7z x ~/Documents/UGR/SO/kernel32-3.0.4.gz -o/tmp/

# launch os
cd /tmp
chmod 777 kernel32-3.0.4 Fedora14-x86-root_fs mem=1024m
./kernel32-3.0.4 ubda=./Fedora14-x86-root_fs mem=1024m
