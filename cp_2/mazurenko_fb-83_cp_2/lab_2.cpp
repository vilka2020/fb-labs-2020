#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

string text_string; // ����� ��� ������ ������ � ����� � �����
string encrypted_text; // �����, � ��� ���� ������������ ������������ �����
string key; // �����, ��� ������ ������� ���� ����������
string alphabet = "��������������������������������";
string temp_1[33][2];

string ReadText(string FilePath)
{
    cout << '\n' << "���������� ������ � ��������� �����..." << '\n';
    // ������� ���� ��� ������ � ������� ������
    ifstream text_file(FilePath);
    // ���� ���� ������� �������
    if (text_file.is_open())
    {
        // stringstream - �� ����, ���������� �� cin, ����� ���� ���� �������� � �������� ���� �����
        stringstream string_stream;
        // rdbuf() - ��������� ������ ������ (����������� ����� �������� ���� ���� ����� ��� �������� �������)
        // ������� ������ ������ rdbuf() ����� � ����� ������ - string_stream
        string_stream << text_file.rdbuf();
        // �������� ���� ����� � ���� ������ ����� text_string
        text_string = string_stream.str();
        text_file.close();
        cout << '\n' << "���������� ������ ������ ������!" << '\n';
    }
    return text_string;
}

// ��������� ������ � ���������� ���� � �����
void AlphaNumeration()
{
    for (int i = 0; i < 33; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0) temp_1[i][j] = alphabet[i];
            else temp_1[i][j] = to_string(i);
        }
    }
}

// ������� ��� ���������� ������ ������ ³������
// ��������� - �������� ����� �� ����
string VigenereCipher()
{
    AlphaNumeration();
    cout << '\n' << "���������� ������ ������ ³������..." << '\n';
    int key_length = key.length(); // ������� �����
    int n = text_string.length(); // ������� ������

    string** temp_2 = new string*[n];
    for (int i = 0; i < n; i++)
    {
        temp_2[i] = new string[2];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 33; j++)
        {
            if (text_string[i] == alphabet[j])
            {
                temp_2[i][0] = text_string[i];
                temp_2[i][1] = temp_1[j][1];
                //if (j < 10) cout << temp_2[i][0] << "  " << temp_2[i][1] << '\n';
                //else cout << temp_2[i][0] << " " << temp_2[i][1] << '\n';
            }
        }
    }

    string** temp_3 = new string*[key_length];
    for (int i = 0; i < key_length; i++)
    {
        temp_3[i] = new string[2];
    }
    for (int i = 0; i < key_length; i++)
    {
        for (int j = 0; j < 33; j++)
        {
            if (key[i] == alphabet[j])
            {
                temp_3[i][0] = key[i];
                temp_3[i][1] = temp_1[j][1];
                //if (j < 10) cout << temp_3[i][0] << "  " << temp_3[i][1] << '\n';
                //else cout << temp_3[i][0] << " " << temp_3[i][1] << '\n';
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        encrypted_text += alphabet[(stoi(temp_2[i][1]) + stoi(temp_3[i % key_length][1])) % 33];
    }

    ofstream out;
    out.open("C:\\Users\\OKSI\\Desktop\\proga\\words_encrypted.txt");
    if (out.is_open())
    {
        out << "����: " << key << '\n' << "������������ �����:" << '\n';
        for (int i = 0; i < encrypted_text.length(); i++)
        {
            out << encrypted_text[i];
        }
    }
    out.close();

    for (int k = 0; k < n; k++)
    {
        delete []temp_2[k];
    }
    delete []temp_2;

    for (int k = 0; k < key_length; k++)
    {
        delete []temp_3[k];
    }
    delete []temp_3;

    cout << '\n' << "���������� ������� ������!" << '\n';

    return encrypted_text;
}

void IndexText()
{
    int n = text_string.length();
    double N = 0;
    double sum_N = 0;
    string temp_alphabet = alphabet;

    for (int j = 0; j < 33; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (text_string[i] == temp_alphabet[j]) N++;
        }
        if (N > 1) sum_N = sum_N + N*(N - 1);
        else sum_N = sum_N + 0;
        N = 0;
    }

    double I = 1/((double)n*((double)n - 1)) * (double)sum_N;

    ofstream out;
    out.open("C:\\Users\\OKSI\\Desktop\\proga\\results_index_1.txt");
    if (out.is_open())
    {
        out << "������ ���������� ��� ��������� ������: " << I << '\n';
    }
    out.close();
}

void IndexEncrypted()
{
    int n = encrypted_text.length();
    double N = 0;
    double sum_N = 0;
    string temp_alphabet = alphabet;

    for (int j = 0; j < 33; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (encrypted_text[i] == temp_alphabet[j]) N++;
        }
        if (N > 1) sum_N = sum_N + N*(N - 1);
        else sum_N = sum_N + 0;
        N = 0;
    }

    double I = 1/((double)n*((double)n - 1)) * (double)sum_N;

    ofstream out;
    out.open("C:\\Users\\OKSI\\Desktop\\proga\\results_index_2.txt");
    if (out.is_open())
    {
        out << "����: " << key << '\n';
        out << "������ ���������� ��� ����������� ������: " << I << '\n';
    }
    out.close();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << '\n' << "���� �����, ������ �������� ����� ��� ���������� (����������� ����): ";
    cin >> key;
    ReadText("C:\\Users\\OKSI\\Desktop\\proga\\words.txt");
    VigenereCipher();
    IndexText();
    IndexEncrypted();
    return 0;
}
