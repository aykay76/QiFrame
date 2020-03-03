#include "stdafx.h"
#include "fontmanager.h"

std::map<FontKey, HFONT> FontManager::m_fonts;

FontManager::FontManager()
{
}

HFONT FontManager::getFont(wchar_t* family, float size)
{
	FontKey key;
	
	key.family = family;
	key.size = size;

	if (m_fonts.find(key) == m_fonts.end())
	{
		CFont font;
		font.CreatePointFont(size * 10.0f, family);
		m_fonts[key] = (HFONT)font.Detach();
	}

	return (HFONT)m_fonts[key];
}

bool operator<(const FontKey& lhs, const FontKey&rhs)
{
	return lhs.family < rhs.family || lhs.size < rhs.size;
}