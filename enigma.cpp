#include <iostream>
#include <cstring>
#include<string>
using namespace std;

//char alpha[] = "FBCDKAGHIJELTNOPWRSMUVQXYZ";
char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char rotors[3][27] =
{
	"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
	"AJDKSIRUXBLHWTMCQGZNPYFVOE",
	"BDFHJLCPRTXVZNYEIWGAKMUSQO"
};
char reflector[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
char key[] = "HDW";


long mod26(long a)
{
	return (a % 26 + 26) % 26;
}

int li(char l)
{
	// Letter index
	return l - 'A';
}

int indexof(char* array, int find)
{
	return strchr(array, find) - array;
}

string crypt(const char *ct)
{
	// Sets initial permutation
	int L = li(key[0]);
	int M = li(key[1]);
	int R = li(key[2]);

	string output="";

	for (int x = 0; x < strlen(ct); x++) {
		int ct_letter = li(ct[x]);

		// Step right rotor on every iteration
		R = mod26(R + 1);

		// Pass through rotors
		char a = rotors[2][mod26(R + ct_letter)];
		char b = rotors[1][mod26(M + li(a) - R)];
		char c = rotors[0][mod26(L + li(b) - M)];

		// Pass through reflector
		char ref = reflector[mod26(li(c) - L)];

		// Inverse rotor pass
		int d = mod26(indexof(rotors[0], alpha[mod26(li(ref) + L)]) - L);
		int e = mod26(indexof(rotors[1], alpha[mod26(d + M)]) - M);
		char f = alpha[mod26(indexof(rotors[2], alpha[mod26(e + R)]) - R)];

		output += f;
	}
	cout << output<<endl;
	return output;
}

int main()
{
	string input = "";
	while (cin >> input) {
		char *st1 = const_cast<char *>(input.c_str());
		crypt(st1);
	}
	system("pause");
	return 0;
}