#pragma once

#include <map>
#include <string>
#include <gdiplus.h>

class ImageManager
{
public:
	ImageManager(void);
public:
	~ImageManager(void);

public:
	static Gdiplus::Bitmap* loadImage(std::wstring filename);
	static Gdiplus::Bitmap* getImage(std::wstring name);
	static void clear();

protected:
	static std::map<std::wstring, Gdiplus::Bitmap*> m_images;
};
