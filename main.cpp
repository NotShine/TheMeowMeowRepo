#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

struct Student {
    std::string id;
    float courseworkMark;
    float finalExamMark;
};



char calculateGrade(float courseworkMark, float finalExamMark) {
    float totalMark = courseworkMark  + finalExamMark ;
    if (totalMark >= 60) return 'A';
    else if (totalMark >= 50) return 'B';
    else if (totalMark >= 40) return 'C';
    else if (totalMark >= 30) return 'D';
    else return 'F';
}


void toUpperCase(std::string &str) {
    for (char &c : str) {
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }
    }
}

void updateStudentMarks(Student students[], int count) {
    std::string id;
    std::cout << "Enter the student ID to update: ";
    std::cin >> id;

    // Convert input ID to uppercase
    toUpperCase(id);

    bool found = false;
    bool match = false;

    for (int i = 0; i < count; i++) {
        std::string currentId = students[i].id;
        // Convert current student ID to uppercase
        toUpperCase(currentId);

        if (id.length() == currentId.length()) {
            match = true;
            for (int j = 0; j < id.length(); j++) {
                // Compare characters directly by checking both possible cases
                if (id[j] != currentId[j]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                found = true;
                std::cout << "Enter new coursework mark: ";
                std::cin >> students[i].courseworkMark;
                std::cout << "Enter new final exam mark: ";
                std::cin >> students[i].finalExamMark;
                std::cout << "Marks updated successfully.\n";
                break;
            }
        }
    }

    if (!found) {
        std::cout << "Student ID not found.\n";
    }
}

void printStudentDetails(const Student students[], int count) {
    std::cout << std::setw(10) << "ID"
              << std::setw(15) << "Coursework"
              << std::setw(15) << "Final Exam"
              << std::setw(10) << "Grade" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    for (int i = 0; i < count; i++) {
        char grade = calculateGrade(students[i].courseworkMark, students[i].finalExamMark);
        std::cout << std::setw(10) << students[i].id
                  << std::setw(15) << students[i].courseworkMark
                  << std::setw(15) << students[i].finalExamMark
                  << std::setw(10) << grade << std::endl;
    }
}

float calculateAverageMark(const Student students[], int count) {
    float totalMarks = 0.0f;
    for (int i = 0; i < count; i++) {
        totalMarks += students[i].courseworkMark  + students[i].finalExamMark ;
    }
    return totalMarks / count;
}

float calculatePassRate(const Student students[], int count) {
    int passCount = 0;
    for (int i = 0; i < count; i++) {
        if (calculateGrade(students[i].courseworkMark, students[i].finalExamMark) != 'F') {
            passCount++;
        }
    }
    return (static_cast<float>(passCount) / count) * 100;
}

Student findHighestScorer(const Student students[], int count) {
    int highestIndex = 0;
    float highestMark = students[0].courseworkMark  + students[0].finalExamMark ;

    for (int i = 1; i < count; i++) {
        float currentMark = students[i].courseworkMark  + students[i].finalExamMark ;
        if (currentMark > highestMark) {
            highestMark = currentMark;
            highestIndex = i;
        }
    }

    return students[highestIndex];
}

void skipHeader(std::ifstream &file) {
    std::string headerLine;
    std::getline(file, headerLine);
}

int main() {
    const int MAX_STUDENTS = 100;
    Student students[MAX_STUDENTS];
    int count = 0;

    std::ifstream inputFile("studentData.txt");

    if (inputFile.is_open()) {
        skipHeader(inputFile);  // Skip the header line

        std::string line;
        while (std::getline(inputFile, line)) {
            // Skip empty lines
            if (line.empty()) {
                continue;
            }

            // Read and parse the non-empty line
            std::stringstream ss(line);
            ss >> students[count].id >> students[count].courseworkMark >> students[count].finalExamMark;

            count++;
            if (count >= MAX_STUDENTS) break;
        }
        inputFile.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    int choice;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Update Student Marks\n";
        std::cout << "2. Print Student Details\n";
        std::cout << "3. Calculate Average Marks\n";
        std::cout << "4. Calculate Pass Rate\n";
        std::cout << "5. Display Highest Scorer\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                updateStudentMarks(students, count);
                break;
            case 2:
                printStudentDetails(students, count);
                break;
            case 3: {
                float averageMark = calculateAverageMark(students, count);
                std::cout << "Average Marks: " << std::fixed << std::setprecision(2) << averageMark << std::endl;
                break;
            }
            case 4: {
                float passRate = calculatePassRate(students, count);
                std::cout << "Pass Rate: " << std::fixed << std::setprecision(2) << passRate << "%" << std::endl;
                break;
            }
            case 5: {
                Student highestScorer = findHighestScorer(students, count);
                char grade = calculateGrade(highestScorer.courseworkMark, highestScorer.finalExamMark);
                std::cout << "Highest Scorer:\n";
                std::cout << "ID: " << highestScorer.id 
                          << ", Coursework Mark: " << highestScorer.courseworkMark 
                          << ", Final Exam Mark: " << highestScorer.finalExamMark 
                          << ", Grade: " << grade << std::endl;
                break;
            }
            case 6:
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Please enter a valid option." << std::endl;
                break;
        }
    } while (choice != 6);

    return 0;
}
