#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<iomanip>
#include <cmath>


using namespace std;
void binary_number(string text);
void encrypt(string text);
void decrypt(string text);
string binary_represent(string text);

int main()
{
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++Welcome to the Baconian Cipher+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "This cipher description is : To encode a message, each letter of the plaintext is replaced by a group of five of the letters 'A' or 'B'\n";
    cout << "This replacement is a binary encoding\n";
    cout << "Do you want to\na)Encrypt\nb)decrypt\nc)exit\nchoose(a or b or c) : ";
    vector<char>choices{'a','b','c'};
    vector<char>available_letters;
    for(int i='A';i<='Z';i++)
    {
        available_letters.push_back(char(i));
    }
    available_letters.push_back(' ');
    char choice;
    cin >> choice;
    cout << endl;
    auto it =find(choices.begin(),choices.end(),choice);
    while(it==choices.end())
    {
        cout << "Invalid input\n";
        cout << "Do you want to\na)Encrypt\nb)decrypt\nc)exit\nchoose(a or b or c) : ";
        cin >> choice;
        cout << endl;
    }
     if(choice=='a')
     {
         cout << "Please enter the text you want to encrypt between A and Z only : ";
         string text;
         getline(cin,text);
         cout << endl;
         for(char i : text)
         {
             it = find(available_letters.begin(),available_letters.end(),i);
             while(it == available_letters.end())
             {
                 cout << "Invalid\n";
                 cout << "Please enter the text you want to encrypt between A and Z only : \n";
                 getline(cin,text);
             }
         }
         encrypt(text);
     }
//     else if (choice =='b')
//     {
//         cout << "Please enter the text you want to decrypt between a and b only : ";
//         string text;
//         cin >> text;
//         cout << endl;
//         decrypt(text);
//     }
//     else if (choice=='c')
//     {
//         return 0;
//     }


    return 0;
}

void encrypt(string text)
{
    cout << binary_represent(text);

}


string binary_represent(string text)
{

    int mask=0b11111;
    int result;
    string binary_representation="";
    for(char i : text)
    {
        if(i==' ')
        {
            continue;
        }
        result = (int(i)-1)&mask;
        for(int j =4 ; j >=0 ; j--)
        {
            binary_representation+=(to_string(result>>j&1));
        }
        binary_representation+=' ';
    }
    for(int i=0;i< binary_representation.size();i++)
    {
        if(binary_representation[i]=='0')
        {
            binary_representation[i]='a';
        }
        else if(binary_representation[i]=='1')
        {
            binary_representation[i]='b';
        }
    }
    return binary_representation;

}


