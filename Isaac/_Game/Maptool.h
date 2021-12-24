#pragma once

// TilemapTool
enum class TileTypes { CLIFF, DOOR, ROAD, WALL, NOTHINGNESS };
enum class SampleTileTypes { BASEMENT, CAVE, CELLAR, DEPTH, NONE };

typedef struct tagSampleTile
{
	RECT						rc = {};
	int							frameX = 0;
	int							frameY = 0;
} SAMPLE_TILE_INFO;

typedef struct tagTile
{
	RECT						rc = {};
	int							frameX = 0;
	int							frameY = 0;
	TileTypes					terrain = TileTypes::WALL;
} TILE_INFO;

#define TILE_SIZE				40
#define	TILE_COLUMN				32
#define TILE_ROW				20
#define BASEMENT_TILE_ROW		80
#define CAVE_TILE_ROW			120
#define CELLAR_TILE_ROW			80
#define DEPTH_TILE_ROW			60
#define SAMPLE_TILE_SIZE		14
#define SAMPLE_TILE_COLUMN		33
#define SAMPLE_TILE_ROW			20

inline void SetTerrain(TILE_INFO* rc, int index)
{
	// WALL로 설정
	if (0 <= rc->frameX && rc->frameX < 32)
	{
		for (int r = 0; r < index; ++r)
		{
			if (0 + (r * TILE_ROW) <= rc->frameY && rc->frameY < (r + 1) * TILE_ROW)
			{
				rc->terrain = TileTypes::WALL;
			}
		}
	}
	// DOOR로 설정/상/하
	if (15 <= rc->frameX && rc->frameX < 17)
	{
		for (int r = 0; r < index; ++r)
		{
			if (1 + (r * TILE_ROW) <= rc->frameY && rc->frameY < 3 + (r * TILE_ROW))
			{
				rc->terrain = TileTypes::DOOR;
			}
			if (17 + (r * TILE_ROW) <= rc->frameY && rc->frameY < ((r + 1) * TILE_ROW) - 1)
			{
				rc->terrain = TileTypes::DOOR;
			}
		}
	}
	// DOOR로 설정/좌/우
	if (1 <= rc->frameX && rc->frameX < 31)
	{
		for (int r = 0; r < index; ++r)
		{
			if (9 + (r * TILE_ROW) <= rc->frameY && rc->frameY < 11 + (r * TILE_ROW))
			{
				rc->terrain = TileTypes::DOOR;
			}
		}
	}
	// ROAD로 설정
	if (3 <= rc->frameX && rc->frameX < 29)
	{
		for (int r = 0; r < index; ++r)
		{
			if (3 + (r * TILE_ROW) <= rc->frameY && rc->frameY < 17 + (r * TILE_ROW))
			{
				rc->terrain = TileTypes::ROAD;
			}
		}
	}
	if (rc->frameX == 32 && rc->frameY == 0)
	{
		rc->terrain = TileTypes::ROAD;
	}

	// 빈 공간
	if (rc->frameX == 32)
	{
		for (int r = 0; r < index; ++r)
		{
			if (0 < rc->frameY && rc->frameY < (r + 1) * TILE_ROW)
			{
				rc->terrain = TileTypes::NOTHINGNESS;
			}
		}
	}
}

// EnemyTool
typedef struct storeNormalMonsterInfo
{
	NormalMonsterTypes					sampleType = NormalMonsterTypes::NONE;
	POINTFLOAT							pos = {};
} STORE_NORMAL_MONSTER_INFO;