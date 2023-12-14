#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <C:\Users\thoma\VS\Project2\ProjectTwo\ProjectTwo\BinaryTree.cpp>

using namespace std;

/**
 * Display the bid information to the console (std::out)
 *
 * @param string filepath to csv file AND pointer to binary search tree object
 */
 void loadCourses(string filePath, BinarySearchTree* bt) {

	ifstream input_file;											//declare and open csv file from path
	input_file.open(filePath, ios::in);

	if (!input_file.is_open()) {
		throw runtime_error("Error File not Opened Correctly");
	}


	string id, name, temp, line;			//declare temporary variables

	vector<string> preReqs;							
	bool firstLine = true;
	


	while (getline(input_file, line)) {			//while file has content,  store line to line variable
		stringstream ss(line);							//split line into strings seperated by comma
		string item;



		getline(ss, id, ',');							//if first line from file we remove UTF-8 Byte Order Mark from data
		if (firstLine) {
			id.erase(0, 3);
			firstLine = false;
		}
		getline(ss, name, ',');							//parse course id, name, and preReqs from file


		if (name == "" || id == "") {
			throw runtime_error("Error Invalid input name and id no show");
		}
		while (getline(ss, temp, ',')) {
			preReqs.push_back(temp);
		}

		vector<string> preReqsCopy = preReqs;

		bt->Insert(id, name, preReqsCopy);				//insertData to final data structure

		preReqs.clear();								//clear temp variables
	}
}
 /**
 * Prints prompt to request user input
 *
 * 
 */
void printPrompt() {
	printf("\n\nOption 1: Load courses\n");
	printf("Option 2: Print courses\n");
	printf("Option 3: Search for course\n");
	printf("Option 9: End Program\n");
}
/**
 * Prints all course information to output
 *
 * @param Course* pointer to course struct
 */
void printCourse(Course* course) {
	if (course == nullptr) {
		printf("Error course not found");
	}
	else {
		printf("\nCourse ID: %s \n     Course Name: %s", course->courseID.c_str(), course->courseName.c_str()); //print course ID and name
		printf("\n     Course Prerequisites: \n");

		for (const auto& element : course->preReqs) {	//print all prerequisites
			;printf("          %s", element.c_str());
		}
	}

}


int main() {
	//declare variables and data structure
	string path;				
	BinarySearchTree bt;
	char userResponse = '0';
	bool coursesLoaded = false;


	//request file path from user
	printf("Welcome to the program! Please enter the path to the desired csv file:\n");		
	cin >> path;

	
	//begin program loop
	while (userResponse != '9') {
		printPrompt();					//prompt and recieve user input
		cin >> userResponse;

		switch (userResponse) {			//switch user input

		case '1':						//if user input is 1: load data to data structure
			loadCourses(path, &bt);
			coursesLoaded = true;
			break;
		case '2':

			if (coursesLoaded) { bt.InOrder();}								//if userInput = 2 and courses are loaded print all courses in data structure
			else { printf("Error: please load courses first..."); }
			break;
		case '3':															//if userInput = 3 and courses are loaded prompt for course ID and use data structures search method
			if (coursesLoaded) {													//print course using printCourse function
				string courseId;													
				printf("Please enter courseID to be searched for: \n");					
				cin >> courseId;
				printCourse(bt.Search(courseId));
			}
			else {
				printf("Error: please load courses first...");
			}
			break;
		case '9':															//if user input is 9 break loop
			break;
		default:															//if invalid input request input again
			
			printf("Error: invalid Input Try again\n ");
			cin >> userResponse;
			break;
		}
		
	}
	printf("Thanks!! goodbye!!");


	
	

}