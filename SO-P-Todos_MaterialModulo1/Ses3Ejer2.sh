#!/bin/bash
#Actividad 3

count=0

while [ $count -lt $1 ]; do
  let count=count+1
  let i=54*3
done

echo $count
