//Writing a class object to a file using ofstream class and mode ios::out

#include<iostream>
#include<fstream>

using namespace std;

class A
{
private:
char name[40];
int age;
float height;
char gender;

public:
void putdata();
void getdata();
};


//Defining the function putdata() to enter the values of data members of an object.
void A :: putdata()
{
cout<<"Enter the name : ";
cin.getline(name,40);
cout<<"Enter the age : ";
cin>>age;
cout<<"Enter the height : ";
cin>>height;
cout<<"Enter the gender : ";
cin>>gender;
}

//Defining the function getdata() to read the values of data members of an object.
void A :: getdata()
{
cout<<"The name is : " << name << "\n";
cout<<"The age is : " << age << "\n";
cout<<"The height is : " << height << "\n";
cout<<"The gender is : " << gender << "\n";
}


int main()
{
//Creating an output stream
ofstream ofstream_ob;


//Calling the open function to write an object to a file
ofstream_ob.open("File9.txt", ios::out);


//Creating an object of A class
A ob1;


//Calling the putdata() function
ob1.putdata();


//Calling the write() function to write an object to a file.
ofstream_ob.write( (char *) & ob1, sizeof(ob1));


cout<<"Congrats! Your object is successfully written to the file \n";


//Closing the output stream
ofstream_ob.close();


//Creating an input stream
ifstream ifstream_ob;


//Calling the open function to read an object from a file
ifstream_ob.open("File11.txt", ios::in);


//Creating an empty object of A class
A ob2;

cout<<"\nReading the object from a file : \n";


//Calling the read() function to read an object from a file and transfer its content to an empty object
ifstream_ob.read( (char *) & ob2, sizeof(ob2));


//Calling the getdata() function
ob2.getdata();


//Closing the input stream
ifstream_ob.close();

return 0;
}
