#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#include "GenericList.hpp"

void printComment(const char* text) // Firulas para console ficar bonito.
{
	static const char* cmd = "powershell write-host -fore Green ";
	unsigned int len = strlen(cmd)+strlen(text);
	char* tmp = new char[len]; 
	strcpy(tmp, cmd);
	strcat(tmp, text);
	system(tmp);
	delete[] tmp;
	printf("\n");
}

void printValue(const char* text)
{
	printf("\t%s\n\n", text);
}

// Test Program
main()
{
	GenericList<char> chrListTest;
	const char* pchr = "the quick brown fox jumps over the lazy dog.";
	
	system("color 0E");
	
	printComment("Test text:");
	printValue(pchr);
	
	printComment("Test addRange:");
	chrListTest.addRange(pchr, strlen(pchr));
	printValue(chrListTest.toArray(0));
	
	printComment("Test insertAt:");
	chrListTest.insertAt(0, '*');
	printValue(chrListTest.toArray(0));
	
	printComment("Test insertAt:");
	chrListTest.insertAt(40, 'k');
	chrListTest.insertAt(40, 'c');
	chrListTest.insertAt(40, 'a');
	chrListTest.insertAt(40, 'l');
	chrListTest.insertAt(40, 'b');
	chrListTest.insertAt(40, ' ');
	printValue(chrListTest.toArray(0));
	
	printComment("Test removeAt insertAt overflow add:");
	chrListTest.removeLast();
	chrListTest.insertAt(100, '!');
	chrListTest.add('*');
	printValue(chrListTest.toArray(0));
	
	printComment("Test changeValue:");
	chrListTest.changeValue(1, 'T');	
	printValue(chrListTest.toArray(0));
		
	printComment("Test reverse:");
	chrListTest.reverse();	
	printValue(chrListTest.toArray(0));
	
	printComment("Test sort:");
	chrListTest.sort();
	printValue(chrListTest.toArray(0));
	
	printComment("Test clear.");
	chrListTest.clear();
		
	printComment("Test addRanges:");
	chrListTest.addRange("7F93A42DE", 9);
	printf("\t%s\n", chrListTest.toArray(0));
	chrListTest.addRange("61C08B5", 7);
	printValue(chrListTest.toArray(0));
		
	printComment("Test operator overload:");
	printf("\t%s\n", chrListTest.toArray(0));
	printf("\tchrListTest[%d]=%c\r\n", 7, chrListTest[7]);	
	chrListTest[7] = 'G';
	printf("\tchrListTest[%d]<-%c\r\n", 7, chrListTest[7]);
	printf("\t%s\n\n", chrListTest.toArray(0));
	
	printComment("Test intersection:");
	int setA[11] = { 5, 23, 1, 21, 14, 7, 16, 3, 53, 25, 2 };
	int setB[13] = { 42, 98, 3, 14, 4, 44, 88, 9, 29, 1, 17, 23, 53 };
	
	GenericList<int> A;
	GenericList<int> B;
	A.addRange(setA, 11);
	B.addRange(setB, 13);
	
	printf("\tlist A= { ");
	for (uint8_t i=0; i<A.count(); i++) printf("%d ", A[i]);
	printf("}\n\tlist B= { ");
	for (uint8_t i=0; i<B.count(); i++) printf("%d ", B[i]);
	
	GenericList<int> I = GenericList<int>::intersection(A,B);
	printf("}\n\tI(A,B)= { ");
	for (uint8_t i=0; i<I.count(); i++) printf("%d ", I[i]);
	
	printf("}\n\n");
	getch();
}
