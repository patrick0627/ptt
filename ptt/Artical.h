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
	vector<string> messages; // 可字首就包含推噓辨別 1推 2噓 3(->)留言
};