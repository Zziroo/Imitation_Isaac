#include "MainConfig.h"
#include "ImageManager.h"
#include "Image.h"

void ImageManager::Init()
{

}

void ImageManager::Release()
{
	for (it = mapImages.begin(); it != mapImages.end(); ) 
	{
		SAFE_RELEASE(it->second);
		it = mapImages.erase(it);
	}
	mapImages.clear();
}

void ImageManager::AddImage(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (FindImage(fileName)) { return; }

	img = new Image;
	if (FAILED(img->Init(fileName, width, height, isTrans, transColor))) 
	{
		SAFE_RELEASE(img);
		return;
	}

	mapImages.insert(make_pair(fileName, img));
}

void ImageManager::AddImage(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (FindImage(fileName)) { return; }

	img = new Image;
	if (FAILED(img->Init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor))) 
	{
		SAFE_RELEASE(img);
		return;
	}

	mapImages.insert(make_pair(fileName, img));
}

Image* ImageManager::FindImage(const char* fileName)
{
	it = mapImages.find(fileName);
	if (it == mapImages.end()) { return nullptr; }
	return it->second;
}

void ImageManager::DeleteImage(const char* fileName)
{
	it = mapImages.find(fileName);
	if (it == mapImages.end()) { return; }
	//Image �����Ҵ� ����
	SAFE_RELEASE(it->second);
	//�ʿ��� ��� ����
	mapImages.erase(it);
}
