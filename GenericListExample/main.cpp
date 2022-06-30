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
	
	chrListTest.sort();
	
	printf("%s\n", chrListTest.toArray(0));
	
	getch();
}
