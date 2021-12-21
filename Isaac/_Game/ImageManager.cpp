#include "MainConfig.h"
#include "MainConfig.h"
#include "ImageManager.h"

#include "Image.h"

void ImageManager::Init()
{
	#pragma region BackGround
	GET_SINGLETON_IMAGE->AddImage("Image/BackGround/BackGround00.bmp", 1920, 1080);
	GET_SINGLETON_IMAGE->AddImage("Image/BackGround/BackGround01.bmp", 1920, 1080);
	GET_SINGLETON_IMAGE->AddImage("Image/BackGround/BackGround02.bmp", 853, 480);
	GET_SINGLETON_IMAGE->AddImage("Image/BackGround/BackGround04.bmp", 580, 580);
	GET_SINGLETON_IMAGE->AddImage("Image/BackGround/Title.bmp", 1280, 6400, 1, 8);
	GET_SINGLETON_IMAGE->AddImage("Image/BackGround/SampleImage.bmp", 1280, 800, 1, 1, true, MAGENTA);
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
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Curse.bmp", 83, 20, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Depth.bmp", 81, 20, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Enemy.bmp", 133, 30, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Exit.bmp", 82, 30, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Item.bmp", 59, 20, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Normal.bmp", 107, 20, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Letter/Obstacle.bmp", 150, 21, 1, 1, true, MAGENTA);
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
	// Info
	GET_SINGLETON_IMAGE->AddImage("Image/Tilemap/Tile/Info.bmp", 900, 268, 1, 1, true, MAGENTA);
	#pragma endregion
	#pragma region Door
	GET_SINGLETON_IMAGE->AddImage("Image/Door/Boss_Room_Door.bmp", 640, 320, 4, 2, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Door/Curse_Room_Door.bmp", 640, 160, 4, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Door/Item_Room_Door.bmp", 640, 480, 4, 3, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Door/Normal_Room_Door.bmp", 640, 480, 4, 3, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Door/Satan_Room_Door.bmp", 640, 160, 4, 1, true, MAGENTA);
	#pragma endregion
	#pragma region Minimap
	GET_SINGLETON_IMAGE->AddImage("Image/Minimap/MinimapBackGround00.bmp", 159, 141, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Minimap/MinimapBackGround01.bmp", 147, 129, 1, 1, true, MAGENTA);
	// Site
	GET_SINGLETON_IMAGE->AddImage("Image/Minimap/AroundedSite.bmp", 27, 24, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Minimap/LocatedSite.bmp", 27, 24, 1, 1, true, MAGENTA);
	// Icon
	GET_SINGLETON_IMAGE->AddImage("Image/Minimap/BossIcon.bmp", 16, 15, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Minimap/CurseIcon.bmp", 15, 15, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Minimap/ItemIcon.bmp", 16, 15, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Minimap/PrivateIcon.bmp", 14, 15, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Minimap/SatanIcon.bmp", 14, 15, 1, 1, true, MAGENTA);
	#pragma endregion
	#pragma region Obstacle
	GET_SINGLETON_IMAGE->AddImage("Image/Obstacle/Bonfire.bmp", 588, 645, 7, 5, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Obstacle/Brick.bmp", 80, 80, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Obstacle/DDong.bmp", 336, 84, 4, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Obstacle/ItemStand.bmp", 82, 63, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Obstacle/Jar.bmp", 84, 81, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Obstacle/Obstacle.bmp", 483, 483, 3, 3, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Obstacle/Slider.bmp", 278, 139, 2, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Obstacle/SpiderWeb.bmp", 75, 78, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Obstacle/Stone.bmp", 101, 107, 1, 1, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Obstacle/Thorn.bmp", 80, 80, 1, 1, true, MAGENTA);
	#pragma endregion
#pragma region Monster
	GET_SINGLETON_IMAGE->AddImage("Image/Monster/Attack_Fly.bmp", 42, 128, 1, 4, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Monster/Fly.bmp", 42, 64, 1, 2, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Monster/Pooter_Attack.bmp", 128, 256, 2, 4, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Monster/Pooter_Dead.bmp", 128, 512, 2, 8, true, MAGENTA);
	GET_SINGLETON_IMAGE->AddImage("Image/Monster/Pooter_Idle.bmp", 128, 256, 2, 4, true, MAGENTA);
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