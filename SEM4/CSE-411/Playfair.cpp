#include<bits/stdc++.h>
using namespace std;

string removeDup(const string &temp)
{
    string res;
    for(auto ch : temp)
    {
        if(isalpha(ch) && res.find(ch)==string::npos)
        {
            res+=toupper(ch);
        }
    }
    return res;
}

void makeMat(char mat[5][5], const string &key)
{
    string temp = removeDup(key +"ABCDEFGHIKLMNOPQRSTUVWXYZ");
    int x = 0;

    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        mat[i][j] = temp[x++];
    }
}

void getPos(const char mat[5][5], char temp, int &row, int &col)
{
    if(temp=='J')
    temp = 'I';

    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            if(mat[i][j]==temp)
            {
                row = i;
                col = j;
                return;
            }
        }
    }
}

string encrypt(const char mat[5][5], char temp1, char temp2)
{
    int row1,row2,col1,col2;
    getPos(mat, temp1, row1, col1);
    getPos(mat, temp2, row2, col2);

    if(row1==row2)
    {
        return string(1,mat[row1][(col1+1)%5]) + mat[row1][(col2+1)%5];
    }
    else if(col1==col2)
    {
        return string(1,mat[(row1+1)%5][col1]) + mat[(row2+1)%5][col2];
    }
    else
    {
        return string(1, mat[row1][col2]) + mat[row2][col1];
    }
}

int main()
{
    string plain, cipher, key;
    cout<<"Enter key and plaintext:"<<endl;
    cin>>key>>plain;
    char mat[5][5];
    makeMat(mat, key);

    for(int i=0; i<plain.size(); i+=2)
    {
        char temp1 = plain[i];
        char temp2 = (i+1<plain.size()&&plain[i]!=plain[i+1])?plain[i+1]:'X';
        cipher+=encrypt(mat, temp1, temp2);
    }
    cout<<"Encrypted cipher: "<<cipher;
    return 0;
}
