#include "MainConfig.h"
#include "ImageManager.h"

#include "Image.h"

void ImageManager::Init()
{
	// Title BackGround
	GETSINGLETON_IMAGE->AddImage("Image/BackGround/BackGround_Black.bmp", 1920, 1080);
	GETSINGLETON_IMAGE->AddImage("Image/BackGround/Title.bmp", 1280, 6400, 1, 8);

	// Isaac
	GETSINGLETON_IMAGE->AddImage("Image/Character/Body.bmp", 540, 99, 10, 3, true, MAGENTA);
	GETSINGLETON_IMAGE->AddImage("Image/Character/Head.bmp", 720, 75, 8, 1, true, MAGENTA);
	GETSINGLETON_IMAGE->AddImage("Image/Character/Hurt.bmp", 324, 99, 3, 1, true, MAGENTA);
	GETSINGLETON_IMAGE->AddImage("Image/Character/ItemPickUp.bmp", 74, 99, 1, 1, true, MAGENTA);
	GETSINGLETON_IMAGE->AddImage("Image/Character/Jump.bmp", 360, 99, 4, 1, true, MAGENTA);
	GETSINGLETON_IMAGE->AddImage("Image/Character/Stat.bmp", 204, 198, 2, 2, true, MAGENTA);

	// Weapon(Tear)
	GETSINGLETON_IMAGE->AddImage("Image/Character/Weapon_Tear.bmp", 30, 30, 1, 1, true, MAGENTA);

	// Tilemap/GUI
	GETSINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Index_00.bmp", 121, 120, 1, 1, true, MAGENTA);
	GETSINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Index_01.bmp", 412, 120, 1, 1, true, MAGENTA);
	GETSINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Left.bmp", 55, 80, 1, 1, true, MAGENTA);
	GETSINGLETON_IMAGE->AddImage("Image/Tilemap/UI/List.bmp", 157, 80, 2, 1, true, MAGENTA);
	GETSINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Load.bmp", 202, 100, 2, 1, true, MAGENTA);
	GETSINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Right.bmp", 55, 80, 1, 1, true, MAGENTA);
	GETSINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Save.bmp", 204, 112, 2, 1, true, MAGENTA);

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
	//Image 동적할당 해제
	SAFE_RELEASE(it->second);
	//맵에서 노드 삭제
	mapImages.erase(it);
}
