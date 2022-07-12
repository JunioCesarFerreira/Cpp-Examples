#include <stdio.h>
#include <conio.h>
#include <string.h>

#include "GenericList.hpp"

// Test Program
main()
{
	GenericList<char> chrListTest;
	const char* pchr = "Testando esse role...\n";
	printf(pchr);
	
	chrListTest.addRange(pchr, strlen(pchr));
	
	printf(chrListTest.toArray(0));
	
	chrListTest.insertAt(0, '*');
		
	printf(chrListTest.toArray(0));
	
	chrListTest.insertAt(9, '|');
	
	printf(chrListTest.toArray(0));
	
	chrListTest.removeLast();
	chrListTest.insertAt(100, '!');
	chrListTest.add('\n');
	
	printf(chrListTest.toArray(0));
	
	chrListTest.changeValue(9, '$');
	
	printf(chrListTest.toArray(0));
		
	chrListTest.reverse();
	
	printf(chrListTest.toArray(0));
	
	chrListTest.sort();
	
	printf(chrListTest.toArray(0));
	
	chrListTest.clear();
	
	printf("\n\n");
	
	chrListTest.addRange("7F93A42DE", 9);
	chrListTest.addRange("61C08B5", 7);
		
	printf("%s\n", chrListTest.toArray(0));
		
	printf("operator overload chrListTest[%d]=%c\r\n", 7, chrListTest[7]);
	
	chrListTest.sort();
	
	printf("%s\n", chrListTest.toArray(0));
	
	printf("operator overload chrListTest[%d]=%c\r\n", 7, chrListTest[7]);
	chrListTest[7] = 'G';
	
	printf("%s\n", chrListTest.toArray(0));
	
	int setA[11] = { 5, 23, 1, 21, 14, 7, 16, 3, 53, 25, 2 };
	int setB[13] = { 7, 98, 3, 14, 4, 5, 88, 9, 29, 1, 17, 23, 0 };
	
	GenericList<int> A;
	GenericList<int> B;
	A.addRange(setA, 11);
	B.addRange(setB, 13);
	
	printf("\nlist A: ");
	for (uint8_t i=0; i<A.count(); i++) printf("%d ", A[i]);
	printf("\n\nlist B: ");
	for (uint8_t i=0; i<B.count(); i++) printf("%d ", B[i]);
	
	GenericList<int> I = GenericList<int>::intersection(A,B);
	printf("\n\nI(A,B)= ");
	for (uint8_t i=0; i<I.count(); i++) printf("%d ", I[i]);
	
	getch();
}
