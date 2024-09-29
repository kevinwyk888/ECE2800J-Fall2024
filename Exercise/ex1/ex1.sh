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

cp assignment1.txt ../reports
mv assignment2.txt renamed_assignment.txt
mv renamed_assignment.txt ../reports

cd ..
mkdir exams
cd exams
touch exam1.txt 
touch exam2.txt
cd ..
cp -r exams assignments
cp -r exams reports

rm -r exams
ls -l > directory_info.txt
diff reports/assignment1.txt reports/renamed_assignment.txt > content_comparison.txt