#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int numCourses;
    cout << "Enter the number of courses: ";
    cin >> numCourses;

    float totalCredits = 0;
    float totalGradePoints = 0;

    // Array to store course-wise data
    float grades[numCourses], credits[numCourses];

    for (int i = 0; i < numCourses; ++i) {
        cout << "\nCourse " << i + 1 << ":\n";
        cout << "Enter grade: ";
        cin >> grades[i];
        cout << "Enter credit hours: ";
        cin >> credits[i];

        totalCredits += credits[i];
        totalGradePoints += grades[i] * credits[i];
    }

    // Calculate semester GPA
    float semesterGPA = totalGradePoints / totalCredits;

    // Input previous CGPA data
    float previousCGPA, previousCredits;
    cout << "\nEnter your previous CGPA: ";
    cin >> previousCGPA;
    cout << "Enter your total previous credit hours: ";
    cin >> previousCredits;

    // Compute updated CGPA
    float updatedCGPA = (previousCGPA * previousCredits + totalGradePoints) / (previousCredits + totalCredits);

    // Output results
    cout << fixed << setprecision(2);
    cout << "\n--- Course Details ---\n";
    for (int i = 0; i < numCourses; ++i) {
        cout << "Course " << i + 1 << ": Grade = " << grades[i]
             << ", Credit Hours = " << credits[i] << endl;
    }

    cout << "\nSemester GPA: " << semesterGPA;
    cout << "\nUpdated CGPA: " << updatedCGPA << endl;

    return 0;
}
