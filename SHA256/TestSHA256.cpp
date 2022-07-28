#include <iostream>
#include <cstring>

#include "sha256.h"
 
using std::string;
using std::cout;
using std::endl;

string conv_sha256(string input); 
 
// Test
int main()
{
    string input = "Texto a ser convertido.";
    
    string output = conv_sha256(input);
 
    cout << "SHA256\r\ninput: "<< input << "\r\noutput: " << output << endl;
    return 0;
}
 
string conv_sha256(string input)
{
    unsigned char digest[SHA256::DIGEST_SIZE];
    memset(digest,0,SHA256::DIGEST_SIZE);
 
    SHA256 sha256 = SHA256();
    sha256.init();
    sha256.update((unsigned char*)input.c_str(), input.length());
    sha256.final(digest);
 
    char buf[2*SHA256::DIGEST_SIZE+1];
    buf[2*SHA256::DIGEST_SIZE] = 0;
    for (int i = 0; i < SHA256::DIGEST_SIZE; i++)
	{
		sprintf(buf+i*2, "%02x", digest[i]);
	} 
    return string(buf);
}
