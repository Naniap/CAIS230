#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;


double computeAvg(int count, int array[]);
string concatenate(string start, int count, int array[]);
const int NUM_STUDENTS = 7;

class Student
{
private:
	string name;
	int project[7];
	int exam[3];
	int quiz[10];
	double projectAvg;
	double examAvg;
	double quizAvg;
	int final;
	double average;
	string grade;
public: Student();
		void get_student_scores();
		void compute_student_stats();
		void determine_student_grade();
		void display_student_name_gpa_grade();
		double student_average();
		void displayInfo();
};
class Course
{
private:
	Student student[NUM_STUDENTS];
	int index_of_highest;
	int index_of_lowest;
public:
	Course();
	~Course();
	void get_grades();
	void evaluate_class();
	void determine_index_of_highest_lowest();
	void display_highest();
	void display_lowest();
	void display_stats();
};

int main() {
	fstream outs;
	outs.open("students.txt", ios::out);
	outs.close();
	//clears file at runtime
	Course course;
	course.get_grades();
	course.evaluate_class();
	course.determine_index_of_highest_lowest();
	course.display_highest();
	course.display_lowest();
	course.display_stats();
	system("PAUSE");
	return 0;
}

Student::Student() {
	name = "";
	fill(exam, exam + 3, 0);
	fill(project, project + 7, 0);
	fill(quiz, quiz + 10, 0);
	final = 0;
	projectAvg = 0;
	examAvg = 0;
	quizAvg = 0;
	average = 0;
	grade = "";
}

void Student::get_student_scores() {
	cout << "Enter name: ";
	getline(cin, name);
	for (int i = 0; i < 7; i++) {
		cout << "Enter a project grade: ";
		cin >> project[i];
	}
	for (int i = 0; i < 3; i++) {
		cout << "Enter an exam grade: ";
		cin >> exam[i];
	}
	for (int i = 0; i < 10; i++) {
		cout << "Enter a quiz grade: ";
		cin >> quiz[i];
	}
	cout << "Enter final exam: ";
	cin >> final;
	cin.ignore();
}
void Student::displayInfo() {
	cout << fixed << setprecision(1);
	string projectGrades = concatenate("Projects: ", 7, project);
	string examGrades = concatenate("Exams: ", 3, exam);
	string quizGrades = concatenate("Quizzes: ", 10, quiz);
	cout << projectGrades << endl;
	cout << examGrades << endl;
	cout << quizGrades << endl;
	cout << "Final: " << final << endl;
	cout << "Average: " << average << endl;
	cout << "Letter grade: " << grade << endl;
}
void Student::compute_student_stats() {
	examAvg = computeAvg(3, exam);
	projectAvg = computeAvg(7, project);
	quizAvg = computeAvg(10, quiz);
	average = (((examAvg / 100.0) * .45) + ((projectAvg / 100.0) * .25) + ((quizAvg / 100.0) * .10) + ((final / 100.0) * .20)) * 100.0;
}
void Student::determine_student_grade() {
	int gradeInt = static_cast<int>(average);
	if (gradeInt >= 93)
		grade = "A";
	else if (gradeInt >= 89)
		grade = "A-";
	else if (gradeInt >= 87)
		grade = "B+";
	else if (gradeInt >= 83)
		grade = "B";
	else if (gradeInt >= 79)
		grade = "B-";
	else if (gradeInt >= 77)
		grade = "C+";
	else if (gradeInt >= 73)
		grade = "C";
	else if (gradeInt >= 69)
		grade = "C-";
	else if (gradeInt >= 67)
		grade = "D+";
	else if (gradeInt >= 63)
		grade = 'D';
	else if (gradeInt >= 57)
		grade = "D-";
	else
		grade = "F";
}
double Student::student_average() {
	return average;
}
void Student::display_student_name_gpa_grade() {
	fstream outs;
	outs.open("students.txt", ios::out | ios::app);
	outs << fixed << setprecision(2);
	cout << fixed << setprecision(2);
	outs << name << " Average: " << average << "%" << " Grade: " << grade << endl;
	cout << name << " Average: " << average << "%" << " Grade: " << grade << endl;
	outs.close();
}
Course::Course() {
	index_of_highest = 0;
	index_of_lowest = 0;
}
Course::~Course() {
	cout << "Memory being reallocated to heap.\n";
	system("PAUSE");
}
void Course::get_grades() {
	for (int i = 0; i < NUM_STUDENTS; i++) {
		student[i].get_student_scores();
	}
}
void Course::evaluate_class() {
	for (int i = 0; i < NUM_STUDENTS; i++) {
		student[i].compute_student_stats();
		student[i].determine_student_grade();
	}
}
void Course::determine_index_of_highest_lowest() {
	int num = 0;
	for (int i = 0; i < NUM_STUDENTS; i++) {
		if (student[i].student_average() > num) {
			num = student[i].student_average();
			index_of_highest = i;
		}
	}
	num = INT_MAX;
	for (int i = 0; i < NUM_STUDENTS; i++) {
		if (student[i].student_average() < num) {
			index_of_lowest = i;
			num = student[i].student_average();
		}
	}
}
void Course::display_highest() {
	fstream outs;
	outs.open("students.txt", ios::out | ios::app);
	outs << "Highest grade: ";
	outs.close();
	cout << "Highest grade: ";
	student[index_of_highest].display_student_name_gpa_grade();
}
void Course::display_lowest() {
	fstream outs;
	outs.open("students.txt", ios::out | ios::app);
	outs << "Lowest grade: ";
	outs.close();
	cout << "Lowest grade: ";
	student[index_of_lowest].display_student_name_gpa_grade();
	outs.open("students.txt", ios::out | ios::app);
	outs << endl;
	outs.close();
	cout << endl;
}
void Course::display_stats() {
	fstream outs;
	outs.open("students.txt", ios::out | ios::app);
	outs << "Grade evaluation summary: " << endl;
	cout << "Grade evaluation summary: " << endl;
	for (int i = 0; i < NUM_STUDENTS; i++) {
		student[i].display_student_name_gpa_grade();
	}
	outs.close();
}
double computeAvg(int count, int array[]) {
	double sum = 0;
	for (int i = 0; i < count; i++) {
		sum += array[i];
	}
	return sum / count;
}
string concatenate(string start, int count, int array[]) {
	for (int i = 0; i < count; i++) {
		start += to_string(array[i]);
		start += i == (count - 1) ? "" : ", ";
	}
	return start;
}