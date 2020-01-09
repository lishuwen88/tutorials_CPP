//Appending the data to a file using fstream class and modes ios::app 
 
#include<iostream>
#include<fstream>

using namespace std;

int main()
{
int size =50;

char str[size] = "Best wishes for all your endeavours!";
char ch;


//Creating an output stream to append new data to a file
fstream fstream_ob;


//Opening a file named File.txt to append new content at its end, using the mode - ios::app
fstream_ob.open("File.txt", ios::app);


//Appending a char array value to the end of the file
fstream_ob<< str << "\n";


//closing the output stream after completing the write operation on the file
fstream_ob.close();

return 0;
}
