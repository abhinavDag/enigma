#include <bits/stdc++.h>
using namespace std;

/* DOCUMENTATION
In this code, I want to actually not write the enigma function in main(), rather, I want to make a function called
enigma which calls some other functions like rotorOne, rotorTwo, rotorThree, reflector, plugboard etc

I want to make the code as neat and understandable as possible so compartmentalize as far as possible.
*/

//FUNCTION PROTOTYPES
string enigma (	int firstRotor,int secondRotor,int thirdRotor,
		char firstIP   ,char secondIP   ,char thirdIP,
		char firstRS   ,char secondRS   ,char thirdRS,
		bool plugBoard,char reflectorType,string plainText);

char rotor(int rotorNumber,char input,char currentPosition, char ringSetting);
char reflector(char type,char input);
char plugboard(char input);

char rotation(char input);

int index(char input,vector <char> vec);
int circularIndex(int input);

//FUNCTION PROTOTYPES--

//CONSTANTS

vector <char> alphabet {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

vector <char> map1     {'e','k','m','f','l','g','d','q','v','z','n','t','o','w','y','h','x','u','s','p','a','i','b','r','c','j'};
vector <char> map2     {'a','j','d','k','s','i','r','u','x','b','l','h','w','t','m','c','q','g','z','n','p','y','f','v','o','e'};
vector <char> map3     {'b','d','f','h','j','l','c','p','r','t','x','v','z','n','y','e','i','w','g','a','k','m','u','s','q','o'};
vector <char> map4     {'e','s','o','v','p','z','j','a','y','q','u','i','r','h','x','l','n','f','t','g','k','d','c','m','w','b'};
vector <char> map5     {'v','z','b','r','g','i','t','y','u','p','s','d','n','h','l','x','a','w','m','j','q','o','f','e','c','k'};

vector <char> map1rev  {'u','w','y','g','a','d','f','p','v','z','b','e','c','k','m','t','h','x','s','l','r','i','n','q','o','j'};
vector <char> map2rev  {'a','j','p','c','z','w','r','l','f','b','d','k','o','t','y','u','q','g','e','n','h','x','m','i','v','s'};
vector <char> map3rev  {'t','a','g','b','p','c','s','d','q','e','u','f','v','n','z','h','y','i','x','j','w','l','r','k','o','m'};
vector <char> map4rev  {'h','z','w','v','a','r','t','n','l','g','u','p','x','q','c','e','j','m','b','s','k','d','y','o','i','f'};
vector <char> map5rev  {'q','c','y','l','x','w','e','n','f','t','z','o','s','m','v','j','u','d','k','g','i','a','r','p','h','b'};

vector <char> ukwbMap {'y','r','u','h','q','s','l','d','p','x','n','g','o','k','m','i','e','b','f','z','c','w','v','j','a','t'};
vector <char> ukwcMap {'f','v','p','j','i','a','o','y','e','d','r','z','x','w','g','c','t','k','u','q','s','b','n','m','h','l'};
vector <vector <char>> reflectorMaps{ukwbMap,ukwcMap}; 
vector <vector <char>> plugs {{'a','f'},{'q','l'}};
vector <vector <char>> rotorMaps{map1,map2,map3,map4,map5,map1rev,map2rev,map3rev,map4rev,map5rev};

vector <char> turnOverPoint {'r','f','w','k','a'};


//CONSTANTS--

int main()
{
	cout << enigma(3,2,1,'a','d','p','a','a','a',false,'b',"abhinavdaggubelli0sravanipriya") << endl;
	return 0;
}

//FUNCTION DEFINITIONS



//rotor()
char rotor(int rotorNumber,char input,char currentPosition, char ringSetting)
{
	char output {};
	
	//creates vector called "mapping"
	vector <char> mapping{};
	for(unsigned i {}; i < rotorMaps[rotorNumber - 1].size() ; i++ )
	{
		mapping.push_back(rotorMaps[rotorNumber -1 ][i]);
	}

	//defines increment variable
	int increment { index(currentPosition,alphabet) - index(ringSetting,alphabet) };
	
	//these pieces of code will determine index of output alphabet and store in "goesToAlphabet"
	int goesToMapping {index(input,alphabet) + increment};
	if(goesToMapping > 25){goesToMapping -= 26;}
	else if(goesToMapping < 0){goesToMapping += 26;}
	
	int goesToAlphabet {index(mapping[goesToMapping],alphabet) - increment};
	if(goesToAlphabet > 25){goesToAlphabet -= 26;}
	else if(goesToAlphabet < 0){goesToAlphabet += 26;}
	
	output = alphabet[goesToAlphabet];
	return output;
}
//rotor()--



//reflector
char reflector(char type,char input) 
{
	unsigned i {};
	if(type == 'b'){ i=0; }
	if(type == 'c'){ i=1; }
	
	vector <char> base {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};	
	
	vector <char> reflect {};
	for(unsigned j {}; j < reflectorMaps[i].size(); j++)
	{
		reflect.push_back(reflectorMaps[i][j]);
	}
	
	char output {};
        output = reflect[index(input,base)];
	return output;

}
//reflector--



//plugboard
char plugboard(char input)
{
	for(size_t i {}; i < plugs.size(); i++)
	{
		for(size_t j {}; j < 2; j++)
		{
			if(plugs[i][j] == input)
			{
				return plugs[i][1-j];
			}
		}
	}
	return input;
}
//plugboard--



//enigma
string enigma ( int firstRotor,int secondRotor,int thirdRotor,
                char firstIP   ,char secondIP   ,char thirdIP,
                char firstRS   ,char secondRS   ,char thirdRS,
                bool plugBoard,char reflectorType,string plainText)
{
	//initializing the positions to use inside the enigma
	char thirdPos {thirdIP};
	char secondPos {secondIP};
	char firstPos {firstIP};
	bool doubleStep {false};
	
	string cipherText {};
	
	for(unsigned plainIndex {};plainIndex < plainText.length();plainIndex++)
	{
		char inputChar { (plainText[plainIndex]) };
		inputChar = tolower(inputChar);

		if(index(inputChar,alphabet) != 9999)	
		{
			thirdPos=rotation(thirdPos);
			if( thirdPos == turnOverPoint[thirdRotor-1] or doubleStep )
			{
				secondPos=rotation(secondPos);
			}
			if( doubleStep )
			{
				firstPos=rotation(firstPos);
				doubleStep = false;
			}
			if(rotation(secondPos) == turnOverPoint[secondRotor-1]){doubleStep = true;}
			
			char outputChar {inputChar};
			
			if(plugBoard){ outputChar = plugboard(outputChar); }
			
			outputChar = rotor(thirdRotor,  outputChar, thirdPos,  thirdRS);
			outputChar = rotor(secondRotor, outputChar, secondPos, secondRS);
			outputChar = rotor(firstRotor,  outputChar, firstPos,  firstRS);
			
			outputChar = reflector(reflectorType, outputChar);
			
			outputChar = rotor(firstRotor+5,  outputChar, firstPos,  firstRS);
			outputChar = rotor(secondRotor+5, outputChar, secondPos, secondRS);
			outputChar = rotor(thirdRotor+5,  outputChar, thirdPos,  thirdRS);	

			if(plugBoard){ outputChar = plugboard(outputChar); }

			cipherText += outputChar;
		}
		else{cipherText += inputChar;}
	}		
	return cipherText;
}		
//enigma--



//rotation
char rotation(char input)
{
	return alphabet[circularIndex(index(input,alphabet)+1)];
}
//rotation--



//index()
int index(char input,vector <char> vec)
{
	long unsigned index {vec.size()};
	for(size_t i {} ; i < vec.size() ; i++)
	{
		if(vec[i] == input)
		{
			index = i;
			break;
		}
	}

	if(index == vec.size()){return 9999;}
	else{return index;}
}
//index()--



//circularIndex
int circularIndex(int input)
{
	int output {input};
	if(output > 25){output -= 26;}
        else if(output < 0){output += 26;}
	return output;
}
//circularIndex--



//FUNCTION DEFINITIONS--
