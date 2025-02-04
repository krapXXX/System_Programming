#define _CRT_SECURE_NO_WARNINGS
#define _UNICODE
#include <iostream>
#include <tchar.h>

using namespace std;

/*1.  Пользователь вводит строку. Проверить, является ли эта строка палиндромом.*/
/*void isPalindrome(const _TCHAR* str)
{
    int len = _tcslen(str);

    for (int i = 0; i < len / 2; i++)
    {
        if (str[i] != str[len - i - 1])
        {
            wcout << str << L" is not a palindrome." << endl;
            return;
        }
    }
    wcout << str << L" is a palindrome." << endl;
}

void main() {

    _TCHAR word1[15] = _TEXT("12321");
    _TCHAR word2[15] = _TEXT("12345");

    isPalindrome(word1);
    isPalindrome(word2);

    system("pause");
}*/

/*2.   Подсчитать количество слов во введенном предложении.*/
/*int countWords(const _TCHAR* str) {
    int len = _tcslen(str);
    int counter = 0;
    bool word = false;

    for (int i = 0; i < len; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            if (!word) {
                counter++;
                word = true;
            }
        }
        else {
            word = false;
        }
    }
    return counter;
}

void main()
{
    _TCHAR phrase[200] = _TEXT("I love dancing");

    int wordCount = countWords(phrase);

    wcout << L"Amount of words: " << wordCount << endl;

    system("pause");
}*/

/*3.  Пользователь вводит текст, строку для поиска и строку для замены.
Реализовать поиск в тексте заданной строки и замены ее на заданную подстроку.*/
/*int changeWords(const _TCHAR* phrase, const _TCHAR* search, const _TCHAR* change)
{
    _TCHAR buffer[500];

    int phraseLen = _tcslen(phrase);
    int searchLen = _tcslen(search);
    int changeLen = _tcslen(change);

    int index = 0;

    for (int i = 0; i < phraseLen; i++)
    {
        bool found = true;
        for (int j = 0; j < searchLen; j++)
        {
            if (phrase[i + j] != search[j])
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            for (int j = 0; j < changeLen; j++)
            {
                buffer[index++] = change[j];
            }
            i += searchLen - 1;
        }
        else
        {
            buffer[index++] = phrase[i];
        }
    }

    buffer[index] = '\0';

    wcout << L"Updated phrase: " << buffer << endl;
}

void main()
{
    _TCHAR phrase[200] = _TEXT("I love dancing and making little videos");
    _TCHAR search[10] = _TEXT("dancing");
    _TCHAR change[10] = _TEXT("singing");

    wcout << L"Initial phrase: " << phrase<<endl;
    wcout << L"Search: " << search<<endl;
    wcout << L"Change to: " << change<<endl;

    changeWords(phrase, search, change);


    system("pause");
}*/


int countWordsVowels(const TCHAR* str)
{
    int len = _tcslen(str);
    const TCHAR vowels[] = _T("аеёиоуэюяАЕЁИОУЭЮЯ");
    int vlen = _tcslen(vowels);
    int counter = 0;

    for (int i = 0; i < len; i++)
    {
        if (str[i + 1] == _T(' '))
        {
            for (int j = 0; j < vlen; j++)
            {
                if (str[i] == vowels[j])
                {
                    counter++;
                    break;
                }
            }
        }
    }

    return counter;
}

void main()
{
    _TCHAR phrase[200] = _TEXT("Я люблю свою маму");

    int wordCount = countWordsVowels(phrase);

    wcout << L"Amount of words that end with a vowel: " << wordCount << endl;

    system("pause");
}