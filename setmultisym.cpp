#include <iostream>
#include <string>

int main(){
	
	//const char sym1[10] = "abcdef";
	//const char sym2[10] = "oilngas";
	//const char sym3[10] = "rubbers";
	
	const char sym1[] = "abcdef";
	const char sym2[] = "oilngas";
	const char sym3[] = "rubbers";

	const char *symlist[10];

	symlist[0] = sym1;
	symlist[1] = sym2;
	symlist[2] = sym3;
	symlist[3] = NULL;

	for (int i=0; symlist[i] != NULL; i++) 
		printf("%s\n", symlist[i]);
		//std::cout << symlist[i] << "\n";
/*	
	char *names[] = { "superman", "batman", "whatever", NULL };
	for (int i=0; symlist[i] != NULL; i++) 
		printf("%s\n", symlist[i]);
*/
	std::string str = "Tutorialspoint";
	char c[str.size() + 1];
	str.copy(c, str.size() + 1);
	c[str.size()] = '\0';
	std::cout << c << '\n';
	
	
	return 0;
}

