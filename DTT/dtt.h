#ifndef DTT_H
#define DTT_H
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>
#include <locale>
#include "zip_file.h"

#pragma warning(disable:4996)// MSVC _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING);

inline std::vector<std::wstring> extractTextInsideTags(const std::wstring& content, const std::wstring& tag)
{
	std::vector<std::wstring> results;
	std::wstring startTag = L"<" + tag;
	std::wstring endTag = L"</" + tag + L">";

	size_t pos = 0;
	while ((pos = content.find(startTag, pos)) != std::wstring::npos)
	{
		if (content[pos + startTag.size()] != L' ' && content[pos + startTag.size()] != L'>' && content[pos + startTag.size()] != L'/')
		{
			pos += startTag.size();
			continue;
		}
		size_t start = content.find(L'>', pos) + 1;
		size_t end = content.find(endTag, start);
		if (end == std::wstring::npos)
			break;

		std::wstring current = content.substr(start, end - start);
		if (!current.empty() && std::find(results.begin(), results.end(), current) == results.end())
			results.push_back(current);

		pos = end;
	}

	return results;
}

inline int dtt(const std::filesystem::path& fp)
{
	std::wstring fnm = fp.stem().wstring();
	std::wstring tp = fp.parent_path().wstring();
	std::wstring pathTXT = tp + L"\\" + fnm + L".txt";

	try
	{
		zip_file archive(fp.string());
		if (!archive.has_file("word/document.xml"))
			return 1;

		std::string data = archive.read("word/document.xml");
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::wstring wdata = converter.from_bytes(data);
		std::vector<std::wstring> texts = extractTextInsideTags(wdata, L"w:t");

		std::wstring vdata;
		for (const auto& item : texts)
			vdata += item + L"\n";

		std::wofstream writer(pathTXT, std::ios::out | std::ios::trunc);
		if (!writer.is_open())
			return false;
		std::locale locRS("sr_RS.UTF-8");
		writer.imbue(locRS);
		writer << vdata;
		writer.close();

		return 0;
	}
	catch (const std::exception& ex)
	{
		std::wcout << "Error occurred: " << ex.what() << std::endl;
		return 1;
	}

	return 1;
}


#endif // DTT_H


