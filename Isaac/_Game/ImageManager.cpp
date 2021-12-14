#include "MainConfig.h"
#include "ImageManager.h"

#include "Image.h"

void ImageManager::Init()
{
	#pragma region BackGround
	GET_SINGLETON_IMAGE->AddImage("Image/BackGround/BackGround00.bmp", 1920, 1080);
	GET_SINGLETON_IMAGE->AddImage("Image/BackGround/BackGround01.bmp", 1920, 1080);
	GET_SINGLETON_IMAGE->AddImage("Image/BackGround/BackGround02.bmp", 853, 480);
	GET_SINGLETON_IMAGE->AddImage("Image/BackGround/Title.bmp", 1280, 6400, 1, 8);
	#pragma endregion
	#pragma region Isaac
	GET_SINGLETON_IMAGE->AddImage("Image/Character/Body.bmp", 540, 99, 10, 3, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Character/Head.bmp", 720, 75, 8, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Character/Hurt.bmp", 324, 99, 3, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Character/ItemPickUp.bmp", 74, 99, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Character/Jump.bmp", 360, 99, 4, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Character/Stat.bmp", 204, 198, 2, 2, true, MAGENTA);
	#pragma endregion
	#pragma region Weapon(Tear)
	GET_SINGLETON_IMAGE->AddImage("Image/Character/Weapon_Tear.bmp", 30, 30, 1, 1, true, MAGENTA);
	#pragma endregion
	#pragma region Tilemap/UI
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Close.bmp", 40, 40, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Index.bmp", 206, 120, 1, 2, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/List.bmp", 117, 60, 2, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Load.bmp", 60, 120, 1, 2, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Next.bmp", 42, 60, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Prev.bmp", 42, 60, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Save.bmp", 60, 120, 1, 2, true, MAGENTA);
	#pragma endregion
	#pragma region Tilemap/Letter
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Basement.bmp", 137, 20, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Cave.bmp", 65, 20, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Cellar.bmp", 97, 20, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Depth.bmp", 81, 20, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Enemy.bmp", 133, 30, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Exit.bmp", 82, 30, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Object.bmp", 150, 30, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Shop.bmp", 69, 20, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Tile.bmp", 80, 30, 1, 1, true, MAGENTA);
	#pragma endregion
	#pragma region Tilemap/Tile
	// Basement
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Basement.bmp", 462, 1120, 33, 80, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Basement00.bmp", 462, 280, 33, 20, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Basement01.bmp", 462, 280, 33, 20, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Basement02.bmp", 462, 280, 33, 20, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Basement03.bmp", 462, 280, 33, 20, true, MAGENTA);
	// Cave
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Cave.bmp", 462, 1680, 33, 120, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Cave00.bmp", 462, 280, 33, 20, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Cave01.bmp", 462, 280, 33, 20, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Cave02.bmp", 462, 280, 33, 20, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Cave03.bmp", 462, 280, 33, 20, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Cave04.bmp", 462, 280, 33, 20, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Cave05.bmp", 462, 280, 33, 20, true, MAGENTA);
	// Cellar
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Cellar.bmp", 462, 1120, 33, 80, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Cellar00.bmp", 462, 280, 33, 20, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Cellar01.bmp", 462, 280, 33, 20, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Cellar02.bmp", 462, 280, 33, 20, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Cellar03.bmp", 462, 280, 33, 20, true, MAGENTA);
	// Depth
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Depth.bmp", 462, 840, 33, 60, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Depth00.bmp", 462, 280, 33, 20, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Depth01.bmp", 462, 280, 33, 20, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Depth02.bmp", 462, 280, 33, 20, true, MAGENTA);
	// Nothingness
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Nothingness.bmp", 462, 280, 33, 20, true, MAGENTA);
	#pragma endregion
	#pragma region Door
	GET_SINGLETON_IMAGE->AddImage("Image/Door/Boss_Room_Door.bmp", 1008, 504, 4, 2, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Door/Curse_Room_Door.bmp", 784, 196, 4, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Door/Item_Room_Door.bmp", 784, 588, 4, 3, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Door/Normal_Room_Door.bmp", 784, 588, 4, 3, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Door/Satan_Room_Door.bmp", 768, 192, 4, 1, true, MAGENTA);
	#pragma endregion
	#pragma region Unused
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Sample_Image.bmp", 1280, 800);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/On_Off.bmp", 60, 60, 1, 2, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/UI/Revert.bmp", 61, 60, 1, 1, true, MAGENTA);
	#pragma endregion
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