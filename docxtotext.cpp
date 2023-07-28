#include <iostream>
#include <locale>
#include <codecvt>
#include "DTT/dtt.h"

using namespace std;

int wmain(int argc, wchar_t* argv[])
{
	if (argc <= 1)
	{
		wcout << L"Usage:" << endl << L"docxtotext  <DOCX-file>" << std::endl << L"where <DOCX-file> is the path to docx file.\nOutput is the file with same name and .txt extension"<<endl;
		return 1;
	}

	std::wstring path(argv[1]);
	return dtt(path);
}