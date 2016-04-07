#!/bin/bash
echo "Enter the path to the location you would like the files saved: " 
read -e FILEPATH
echo "You entered $FILEPATH"
cp ~/Desktop/*.sh "$FILEPATH"

