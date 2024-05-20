#include<bits/stdc++.h>
using namespace std;

void encrypt(string &plainText, int key)
{
    for(int i=0; i<plainText.size(); i++)
    {
        if(isupper(plainText[i]))
        plainText[i] = ((plainText[i]-'A'+key)%26 + 'A');
        else
        plainText[i] = ((plainText[i]-'a'+key)%26 + 'a');
    }
}
void decrypt(string &plainText, int key)
{
    for(int i=0; i<plainText.size(); i++)
    {
        if(isupper(plainText[i]))
        plainText[i] = ((plainText[i]-'Z'-key)%26 + 'Z');
        else
        plainText[i] = ((plainText[i]-'z'-key)%26 + 'z');
    }
}

int main()
{
    string plainText;
    int key;
    cin>>plainText>>key;

    encrypt(plainText, key);
    cout<<"Encrypted cipher: "<<plainText<<endl;
    decrypt(plainText, key);
    cout<<"Decrypted cipher: "<<plainText<<endl;
    return 0;
}