#!/bin/bash

mkdir Coursework
cd Coursework
mkdir assignments
mkdir reports

cd assignments
touch assignment1.txt
touch assignment2.txt
echo "This is assignment 1." > assignment1.txt
echo "This is assignment 2." > assignment2.txt

cp assignment2.txt ../reports