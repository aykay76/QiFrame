#pragma once

#include <map>
#include <string>

class FontKey
{
public: 
	std::wstring family;
	float size;
};

class FontManager
{
public:
	FontManager();

public:
	static HFONT getFont(wchar_t* family, float size);

protected:
	static std::map<FontKey, HFONT> m_fonts;
};

bool operator<(const FontKey& lhs, const FontKey&rhs);
