#include "stdafx.h"
#include "ImageManager.h"

using namespace Gdiplus;

std::map<std::wstring, Bitmap*> ImageManager::m_images;

ImageManager::ImageManager(void)
{
}

ImageManager::~ImageManager(void)
{
}

Bitmap* ImageManager::loadImage(std::wstring filename)
{
	std::wstring name = filename;
	name = name.substr(0, name.find('.'));

	Bitmap* bmp = new Bitmap(filename.c_str());
	m_images[name] = bmp;

	return bmp;
}

Bitmap* ImageManager::getImage(std::wstring name)
{
	if (m_images.find(name) == m_images.end()) return NULL;
	else return m_images[name];
}

void ImageManager::clear()
{
	std::map<std::wstring, Bitmap *>::iterator it = m_images.begin();
	while (it != m_images.end())
	{
		delete it->second;
		++it;
	}

	m_images.clear();
}