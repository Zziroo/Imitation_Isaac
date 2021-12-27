#include "stdafx.h"
#include "AStar.h"

#include <queue>

#define INF				1e9
#define IMPASSABLE_ROAD 1e3

void AStar::Init()
{
	ComposeMap();
}

void AStar::Release()
{
}

void AStar::Update()
{
	GiveStartPos();
	GiveTargetPos();

	if (LocatedInside(target))
	{
		DoAstar(start, target);
	}
}

void AStar::Render(HDC hdc)
{
}

void AStar::OnDebug(HDC hdc)
{
}

void AStar::ComposeMap()
{
	// Map 구성
	// 1. 전체 Map을 움직일수 없는 위치로 지정
	map.resize(TILE_ROW);
	for (int r = 0; r < TILE_ROW; ++r)
	{
		map[r].resize(TILE_COLUMN);
		for (int c = 0; c < TILE_COLUMN; ++c)
		{
			map[r][c] = IMPASSABLE_ROAD;
		}
	}

	// 2. 움직일 수 있는 위치를 0으로 지정
	for (int r = 3; r < 18; ++r)
	{
		for (int c = 3; c < 29; ++c)
		{
			map[r][c] = 0;
		}
	}

	// 3. 만약 장애물에 영향을 받는다면 추가할 것
}

void AStar::DoAstar(Pos start, Pos end)
{
	vector<vector<int>> f;
	for (int i = 0; i < TILE_ROW; ++i)
	{
		f.emplace_back(TILE_COLUMN, INF);
	}
	
	f[start.Y][start.X] = 0;

	Pos path[TILE_ROW][TILE_COLUMN];
	path[start.Y][start.X] = start;

	priority_queue<pair<int, Pos>> pq;
	pq.emplace(0, start);

	int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	int dy[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	float dg[] = { 10.0f, diagonalWeight, 10.0f, diagonalWeight, 10.0f, diagonalWeight, 10.0f, diagonalWeight };

	int pathIndex = 0;

	while (pq.empty() == false)
	{
		int w = -pq.top().first;
		Pos pos = pq.top().second;
		++pathIndex;
		pq.pop();

		if (f[pos.Y][pos.X] < w)
		{
			continue;
		}

		if (pos == end)
		{
			break;
		}

		for (int i = 0; i < 8; ++i)
		{
			int nx = dx[i] + pos.X;
			int ny = dy[i] + pos.Y;

			if (nx < OUT_OF_STAGE || nx >= TILE_COLUMN || ny < OUT_OF_STAGE || ny >= TILE_ROW)
			{
				continue;
			}

			if (!(map[ny][nx] == 0 || map[ny][nx] == 3))
			{
				continue;
			}

			float nf = dg[i] + Heuristic({ nx, ny }, end);

			if (f[ny][nx] > nf)
			{
				f[ny][nx] = nf;

				path[ny][nx] = pos;

				pq.emplace(-f[ny][nx], Pos{ nx, ny });
			}
		}
	}
	
	Pos curr = end;
	while (curr != start)
	{
		map[curr.Y][curr.X] = pathIndex;
		--pathIndex;
		curr = path[curr.Y][curr.X];
	}
}

void AStar::GiveStartPos()
{
	start.X = (INT)(startPos.x / TILE_SIZE);
	start.Y = (INT)(startPos.y / TILE_SIZE);

	map[start.Y][start.X] = 1;
}

void AStar::GiveTargetPos()
{
	target.X = (INT)(targetPos.x / TILE_SIZE);
	target.Y = (INT)(targetPos.y / TILE_SIZE);

	map[target.Y][target.X] = 3;
}

float AStar::Heuristic(Pos a, Pos b)
{
	return abs((FLOAT)(a.X - b.X)) + abs((FLOAT)(a.Y - b.Y));
}

bool AStar::LocatedInside(Pos target)
{
	if (2 < target.X || target.X < 29 || 2 < target.Y || target.Y < 17)
	{
		return true;
	}
	else
	{
		return false;
	}
}
