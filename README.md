# Student Marks Management System
Overview
This project is a simple C++ program that manages student data, including coursework and final exam marks. The program reads data from a file, calculates grades, allows updating of marks, and provides various statistics such as average marks, pass rate, and the highest scorer.

Features
Read Student Data from File:

The program reads student IDs, coursework marks, and final exam marks from a text file, skipping any header line or blank lines.
Update Student Marks:

Users can update the coursework and final exam marks for a student by providing the student's ID.
Calculate Grades:

Grades are calculated based on the sum of coursework and final exam marks:
A for total marks >= 90
B for total marks >= 80
C for total marks >= 70
D for total marks >= 60
F for total marks < 60
Print Student Details:

A well-formatted table displaying all students with their ID, coursework marks, final exam marks, and grades.
Statistics:

Average Marks: Calculates and displays the average marks of all students.
Pass Rate: Calculates and displays the percentage of students who passed (grades other than F).
Highest Scorer: Displays the full details of the student with the highest total marks.
File Structure
studentData.txt: The input file containing student data in the format: ID CourseworkMark FinalExamMark.

main.cpp: The C++ source file that implements the program logic.
