#pragma once
#include<iostream>
#include<vector>

using namespace std;

class Artical
{
public:
	Artical() {}

	void editIntent() {}
	void editMassage() {}
private:
	string path;
	string title;
	vector<string> intent;
	vector<string> messages; // �i�r���N�]�t���N��O 1�� 2�N 3(->)�d��
};