#include <stdio.h>
#include <conio.h>
#include <strings.h>
#include <inttypes.h>

// references: https://www.ime.usp.br/~pf/algoritmos/apend/unicode.html
//             https://www.utf8-chartable.de/unicode-utf8-table.pl
//             https://bjoern.hoehrmann.de/utf-8/decoder/dfa/

size_t fromUtf8ToIso88591(char* str_utf8, char* str_ext_ascii)
{
	if (str_utf8==NULL) return 0;
	size_t input_length = strlen(str_utf8);
	size_t index_ext_ascii = 0;
    //Convert the UTF-8 string to ISO 8859-1
	for (size_t i=0; i<input_length; i++)
	{
		uint8_t t_byte = (uint8_t)str_utf8[i];
		if (t_byte <= 0x7F)
		{
			str_ext_ascii[index_ext_ascii] = str_utf8[i];
			index_ext_ascii++;
		}
		else if (t_byte == 0xC3)
		{
			i++;
			t_byte = (uint8_t)str_utf8[i];
			if (t_byte > 0x7F)
			{
				str_ext_ascii[index_ext_ascii] = (char)(t_byte+0x40);
				index_ext_ascii++;
			}
		}
		else if (t_byte == 0xC2)
		{
			i++;
			t_byte = (uint8_t)str_utf8[i];
			if (t_byte > 0x7F)
			{
				str_ext_ascii[index_ext_ascii] = (char)(t_byte);
				index_ext_ascii++;
			}
		}
	}
	str_ext_ascii[index_ext_ascii] = 0;
	return index_ext_ascii;
}

int fromIso88591toUtf8(char *isoString, char *utfString)
{
    uint32_t i = 0;
    uint32_t utfLength = 0;
 
    //Calculate the length of the UTF-8 string
    while (isoString[i] != '\0')
    {
        if (isoString[i] <= 0x7F) utfLength++;
        else utfLength += 2;
        i++;
    }
 
    if (utfLength == 0) return 0;
     
    //Convert the ISO 8859-1 string to UTF-8
    i = 0;
    utfLength = 0;
    while (isoString[i] != '\0')
    {
        if ((uint8_t)isoString[i] <= 0x7F)
        {
            utfString[utfLength] = isoString[i];
            utfLength++;
        }
        else
        {            
        	uint8_t tmp = isoString[i] & 0x06;
        	if (tmp-0x40 > 0x7F) tmp=3;
        	else tmp=2;
            utfString[utfLength] = 0xC0 | tmp;
            
            utfString[utfLength + 1] = 0x80 | (isoString[i] & 0x7F);
            
            utfLength += 2;
        }
        i++;
    }
 
    utfString[utfLength] = '\0';
 
    return utfLength;
}

void printBytes(char* ptr, size_t len)
{
	for (size_t i=0; i<len; i++)
	{
		printf("0x%x ", (uint8_t)ptr[i]);
	}
	printf("\r\n");
}

#define ASCII_LENGTH 256
#define UTF8_LENGTH  383

main()
{
	char all_extended_ascii[ASCII_LENGTH];
	char utf8_str[UTF8_LENGTH];
	
	for (uint16_t i=0; i<ASCII_LENGTH-1; i++)
	{
		all_extended_ascii[i]=(char)(i+1);
	}
	all_extended_ascii[ASCII_LENGTH-1]=0;
		
	printf("\nTest: From ISO-8859-1 to UTF-8\n\n");
	int len = fromIso88591toUtf8(all_extended_ascii, utf8_str);
	
	printf("input ASCII ISO-8859-1:\n");
	printBytes(all_extended_ascii, ASCII_LENGTH);
	printf("\noutput UTF-8:\n", utf8_str);
	printBytes(utf8_str, len);
	
		
	printf("\nTest: From UTF-8 to ISO-8859-1\n\n");
	len = fromUtf8ToIso88591(utf8_str, all_extended_ascii);
	
	printf("pullback:\n");
	printBytes(all_extended_ascii, len);
		
	bool assertFail = false;
	for (uint16_t i=1; i<255; i++)
	{
		if ((char)(i+1)!=all_extended_ascii[i])
		{
			assertFail=true;
			break;
		}
	}
	if (assertFail) printf("\r\nassert fail\n");
	else printf("\r\nassert OK\n");
	
	getch();
}
