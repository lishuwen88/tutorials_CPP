#include <iostream>
#include <fstream>

int main(){
	// Using the ofstream class to create a file and to open output stream to the file, write content to it
	std::ofstream ofstream_ob("File2.txt", std::ios::out);

	int i;
	std::cout << "Enter an int: ";
	std::cin >> i;

	//Writing an int value to the file
	ofstream_ob<< i << "\n";

	char ch;
	std::cout << "Enter a char value: ";
	std::cin >> ch;

	// Writing a char value to the file
	ofstream_ob<< ch << "\n";

	float f;
	std::cout << "Enter a float value: ";
	std::cin >> f;

	// Writing a float value to the file
	ofstream_ob<<f <<"\n";

	char newline_chr;
	std::cin.get(newline_chr);

	char arr[40];
	std::cout << "Enter the content of char array: ";
	std::cin.getline(arr,40);
	std::cout << arr <<"\n";

	// Writing a char array to the file
	ofstream_ob<< arr << "\n";

	std::string str;
	std::cout << "Enter the content of a string: ";
	std::getline(std::cin, str);

	// Writing the string to the file
	ofstream_ob << str << "\n";

	// Closing the output stream after completing the write operation on the file
	ofstream_ob.close();

	return 0;
}
