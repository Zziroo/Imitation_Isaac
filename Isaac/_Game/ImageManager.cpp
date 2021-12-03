#include "MainConfig.h"
#include "ImageManager.h"

#include "Image.h"

void ImageManager::Init()
{
	// BackGround
	GET_SINGLETON_IMAGE->AddImage("Image/BackGround/BackGround_Black.bmp", 1920, 1080);
	GET_SINGLETON_IMAGE->AddImage("Image/BackGround/Title.bmp", 1280, 6400, 1, 8);

	// Isaac
	GET_SINGLETON_IMAGE->AddImage("Image/Character/Body.bmp", 540, 99, 10, 3, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Character/Head.bmp", 720, 75, 8, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Character/Hurt.bmp", 324, 99, 3, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Character/ItemPickUp.bmp", 74, 99, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Character/Jump.bmp", 360, 99, 4, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Character/Stat.bmp", 204, 198, 2, 2, true, MAGENTA);

	// Weapon(Tear)
	GET_SINGLETON_IMAGE->AddImage("Image/Character/Weapon_Tear.bmp", 30, 30, 1, 1, true, MAGENTA);

	// Tilemap/UI
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Index.bmp", 206, 120, 1, 2, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Load.bmp", 121, 60, 2, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Save.bmp", 121, 60, 2, 1, true, MAGENTA);
	// Tilemap/Letter
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Enemy.bmp", 133, 30, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Exit.bmp", 82, 30, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Object.bmp", 150, 30, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Tile.bmp", 80, 30, 1, 1, true, MAGENTA);

	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Next.bmp", 55, 80, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/On_Off.bmp", 60, 60, 1, 2, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Prev.bmp", 55, 80, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Revert.bmp", 61, 60, 1, 1, true, MAGENTA);
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
	if (FindImage(fileName)) 
	{ 
		return; 
	}

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
	if (FindImage(fileName)) 
	{ 
		return;
	}

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
	if (it == mapImages.end()) 
	{ 
		return nullptr;
	}

	return it->second;
}

void ImageManager::DeleteImage(const char* fileName)
{
	it = mapImages.find(fileName);
	if (it == mapImages.end()) 
	{ 
		return;
	}

	// Image 동적할당 해제
	SAFE_RELEASE(it->second);
	// 맵에서 노드 삭제
	mapImages.erase(it);
}
