#include<bits/stdc++.h>
using namespace std;

void expandKey(string &key, int len)
{
    string temp = key;
    int loop = len-key.size(),k=0;
    while(loop--)
    key+=temp[(k++)%temp.size()];
}

void encrypt(string &cipher, string plain, string key)
{
    for(int i=0; i<plain.size(); i++)
    {
        cipher+=(plain[i]+key[i])%26+'A';
    }
}

void decrypt(string cipher, string &decrypted, string key)
{
    for(int i=0; i<cipher.size(); i++)
    {
        decrypted+=(cipher[i]-key[i]+26)%26+'A';
    }
}

int main()
{
    string key, plain, cipher,decrypted;
    cin>>key>>plain;
    int len = plain.size();
    expandKey(key, len);
    
    encrypt(cipher, plain, key);
    
    cout<<cipher<<endl;

    decrypt(cipher, decrypted, key);
    cout<<decrypted<<endl;
    
    return 0;
}