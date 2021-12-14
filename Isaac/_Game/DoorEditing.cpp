#include "MainConfig.h"
#include "DoorEditing.h"

#include "Image.h"
#include "RoomEditing.h"

void DoorEditing::Init()
{
	roomIndex = new RoomEditing;
	roomIndex->Init();
	// Stage01의 Size를 받기
	_stageSize = roomIndex->GetStageSize();
	// StartPoint를 받기
	_startPoint = roomIndex->GetStartPoint();
	// Stage Size만큼 resize 하고
	stage01Index.resize(_stageSize);
	for (size_t i = 0; i < stage01Index.size(); ++i)
	{
		stage01Index[i].resize(_stageSize);
		for (size_t j = 0; j < stage01Index[i].size(); ++j)
		{
			stage01Index[i][j] = roomIndex->GetStage()[i][j];
		}
	}
	// Room Size만큼 resize하고
	roomInfo.resize(_stageSize);
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		roomInfo[i].resize(_stageSize);
		for (size_t j = 0; j < roomInfo[i].size(); ++j)
		{
			// Room의 정보를 가져오기
			roomInfo[i][j] = roomIndex->GetRoomType()[i][j];
		}
	}

	// 각각의 Room마다 DOOR_INFO를 저장할 이중벡터 초기화
	door.resize(_stageSize);
	for (size_t i = 0; i < door.size(); ++i)
	{
		door[i].resize(_stageSize);
		for (size_t j = 0; j < door[i].size(); ++j)
		{
			// Door의 Size
			objectSize = 80.0f;
			//UP
			door[i][j][0].img = nullptr;
			door[i][j][0].doorState = DoorStates::CLOSED;								// Door의 상태
			door[i][j][0].doorDir = ObjectDir::UP;										// Door의 방향
			door[i][j][0].pos.x = 640.0f;												// terrain frameX 16
			door[i][j][0].pos.y = 80.0f;												// terrain frameY 2
			door[i][j][0].shape = {
				(LONG)(door[i][j][0].pos.x - (objectSize * DEVIDE_HALF)),				// shape.left
				(LONG)(door[i][j][0].pos.y - (objectSize * DEVIDE_HALF) - 40),			// shape.top
				(LONG)(door[i][j][0].pos.x + (objectSize * DEVIDE_HALF)),				// shape.right
				(LONG)(door[i][j][0].pos.y + (objectSize * DEVIDE_HALF))				// shape.bottom
			};
			//DOWN
			door[i][j][1].img = nullptr;
			door[i][j][1].doorState = DoorStates::CLOSED;								// Door의 상태
			door[i][j][1].doorDir = ObjectDir::DOWN;									// Door의 방향
			door[i][j][1].pos.x = 640.0f;												// terrain frameX 16
			door[i][j][1].pos.y = 720.0f;												// terrain frameY 18
			door[i][j][1].shape = {
				(LONG)(door[i][j][1].pos.x - (objectSize * DEVIDE_HALF)),				// shape.left
				(LONG)(door[i][j][1].pos.y - (objectSize * DEVIDE_HALF)),				// shape.top
				(LONG)(door[i][j][1].pos.x + (objectSize * DEVIDE_HALF)),				// shape.right
				(LONG)(door[i][j][1].pos.y + (objectSize * DEVIDE_HALF) + 40)			// shape.bottom
			};
			//LEFT
			door[i][j][2].img = nullptr;
			door[i][j][2].doorState = DoorStates::CLOSED;								// Door의 상태
			door[i][j][2].doorDir = ObjectDir::LEFT;									// Door의 방향
			door[i][j][2].pos.x = 80.0f;												// terrain frameX 2
			door[i][j][2].pos.y = 400.0f;												// terrain frameY 10
			door[i][j][2].shape = {
				(LONG)(door[i][j][2].pos.x - (objectSize * DEVIDE_HALF) - 40),			// shape.left
				(LONG)(door[i][j][2].pos.y - (objectSize * DEVIDE_HALF)),				// shape.top
				(LONG)(door[i][j][2].pos.x + (objectSize * DEVIDE_HALF)),				// shape.right
				(LONG)(door[i][j][2].pos.y + (objectSize * DEVIDE_HALF))				// shape.bottom
			};
			//RIGHT
			door[i][j][3].img = nullptr;
			door[i][j][3].doorState = DoorStates::CLOSED;								// Door의 상태
			door[i][j][3].doorDir = ObjectDir::RIGHT;									// Door의 방향
			door[i][j][3].pos.x = 1200.0f;												// terrain frameX 29
			door[i][j][3].pos.y = 400.0f;												// terrain frameY 10
			door[i][j][3].shape = {
				(LONG)(door[i][j][3].pos.x - (objectSize * DEVIDE_HALF)),				// shape.left
				(LONG)(door[i][j][3].pos.y - (objectSize * DEVIDE_HALF)),				// shape.top
				(LONG)(door[i][j][3].pos.x + (objectSize * DEVIDE_HALF) + 40),			// shape.right
				(LONG)(door[i][j][3].pos.y + (objectSize * DEVIDE_HALF))				// shape.bottom
			};
		}
	}

	// 통과했는지의 여부를 알기 위한 이중 벡터 초기화
	isTransitMap.resize(_stageSize);
	for (size_t i = 0; i < isTransitMap.size(); ++i)
	{
		isTransitMap[i].resize(_stageSize);
		for (size_t j = 0; j < isTransitMap[i].size(); ++j)
		{
			isTransitMap[i][j] = false;
		}
	}

	// 방문하면서 현재의 맵 기준 상, 하, 좌, 우 의 RoomType들을 판별해서 Image들을 저장
	StoreRoomType(_startPoint, _startPoint);
	// 특정 방들은 자기 방에 맞는 이미지를 가지게 함
	FixBossDoor();									// BossRoom
	FixCurseDoor();									// CurseRoom
	FixItemDoor();									// ItemRoom
	FixSatanDoor();									// SatanRoom

	// 현재 맵의 위치
	currLocateRow = _startPoint;
	currLocateColumn = _startPoint;
}

void DoorEditing::Release()
{
	SAFE_RELEASE(roomIndex);
}

void DoorEditing::Update()
{
#ifdef _DEBUG
	GameObject::Update();
#endif
	//// DoorState 마다 문의 이미지 변화
	//for (int i = 0; i < 4; ++i)
	//{
	//	if (door[currLocateRow][currLocateColumn][i].doorState == DoorStates::OPENED)
	//	{
	//		door[currLocateRow][currLocateColumn][i].img->SetCurrFrameY(0);
	//	}
	//	if (door[currLocateRow][currLocateColumn][i].img->GetMaxFrameY() > 1 && door[currLocateRow][currLocateColumn][i].doorState == DoorStates::CLOSED)
	//	{
	//		door[currLocateRow][currLocateColumn][i].img->SetCurrFrameY(1);
	//	}
	//	if (door[currLocateRow][currLocateColumn][i].img->GetMaxFrameY() > 2 && door[currLocateRow][currLocateColumn][i].doorState == DoorStates::LOCKED)
	//	{
	//		door[currLocateRow][currLocateColumn][i].img->SetCurrFrameY(2);
	//	}
	//}
	
	// 예시) 상,하,좌,우 키를 입력해서 맵을 바꿈.(문을 알아서 보여줘야함)
	if (Input::GetButtonDown(VK_UP))
	{
		--currLocateRow;
		if (currLocateRow < 0)
		{
			currLocateRow = 0;
		}
	}
	if (Input::GetButtonDown(VK_DOWN))
	{
		++currLocateRow;
		if (currLocateRow >= _stageSize)
		{
			currLocateRow = _stageSize - 1;
		}
	}
	if (Input::GetButtonDown(VK_LEFT))
	{
		--currLocateColumn;
		if (currLocateColumn < 0)
		{
			currLocateColumn = 0;
		}
	}
	if (Input::GetButtonDown(VK_RIGHT))
	{
		++currLocateColumn;
		if (currLocateColumn >= _stageSize)
		{
			currLocateColumn = _stageSize - 1;
		}
	}
}

void DoorEditing::Render(HDC hdc)
{
	if (door[currLocateRow][currLocateColumn][0].img != nullptr) door[currLocateRow][currLocateColumn][0].img->Render(hdc, door[currLocateRow][currLocateColumn][0].pos.x, door[currLocateRow][currLocateColumn][0].pos.y, 0, door[currLocateRow][currLocateColumn][0].img->GetCurrFrameY());
	if (door[currLocateRow][currLocateColumn][1].img != nullptr) door[currLocateRow][currLocateColumn][1].img->Render(hdc, door[currLocateRow][currLocateColumn][1].pos.x, door[currLocateRow][currLocateColumn][1].pos.y, 1, door[currLocateRow][currLocateColumn][1].img->GetCurrFrameY());
	if (door[currLocateRow][currLocateColumn][2].img != nullptr) door[currLocateRow][currLocateColumn][2].img->Render(hdc, door[currLocateRow][currLocateColumn][2].pos.x, door[currLocateRow][currLocateColumn][2].pos.y, 2, door[currLocateRow][currLocateColumn][2].img->GetCurrFrameY());
	if (door[currLocateRow][currLocateColumn][3].img != nullptr) door[currLocateRow][currLocateColumn][3].img->Render(hdc, door[currLocateRow][currLocateColumn][3].pos.x, door[currLocateRow][currLocateColumn][3].pos.y, 3, door[currLocateRow][currLocateColumn][3].img->GetCurrFrameY());

	// Debug
	GameObject::Update();
	GameObject::Render(hdc);
}

void DoorEditing::OnDebug(HDC hdc)
{
	if (debugMode)
	{
		Rectangle(hdc, door[currLocateRow][currLocateColumn][0].shape.left, door[currLocateRow][currLocateColumn][0].shape.top, door[currLocateRow][currLocateColumn][0].shape.right, door[currLocateRow][currLocateColumn][0].shape.bottom);
		Rectangle(hdc, door[currLocateRow][currLocateColumn][1].shape.left, door[currLocateRow][currLocateColumn][1].shape.top, door[currLocateRow][currLocateColumn][1].shape.right, door[currLocateRow][currLocateColumn][1].shape.bottom);
		Rectangle(hdc, door[currLocateRow][currLocateColumn][2].shape.left, door[currLocateRow][currLocateColumn][2].shape.top, door[currLocateRow][currLocateColumn][2].shape.right, door[currLocateRow][currLocateColumn][2].shape.bottom);
		Rectangle(hdc, door[currLocateRow][currLocateColumn][3].shape.left, door[currLocateRow][currLocateColumn][3].shape.top, door[currLocateRow][currLocateColumn][3].shape.right, door[currLocateRow][currLocateColumn][3].shape.bottom);
	}
}

void DoorEditing::FixBossDoor()
{
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		for (int j = 0; j < roomInfo[i].size(); ++j)
		{
			if (roomInfo[i][j] == RoomTypes::BOSS)
			{
				door[i][j][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
				door[i][j][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
				door[i][j][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
				door[i][j][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
			}
		}
	}
}

void DoorEditing::FixCurseDoor()
{
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		for (int j = 0; j < roomInfo[i].size(); ++j)
		{
			if (roomInfo[i][j] == RoomTypes::CURSE)
			{
				// 이미지 변경
				door[i][j][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
				door[i][j][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
				door[i][j][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
				door[i][j][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
				// 항상 열려 있음
				door[i][j][0].doorState = DoorStates::OPENED;
				door[i][j][1].doorState = DoorStates::OPENED;
				door[i][j][2].doorState = DoorStates::OPENED;
				door[i][j][3].doorState = DoorStates::OPENED;
			}
		}
	}
}

void DoorEditing::FixItemDoor()
{
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		for (int j = 0; j < roomInfo[i].size(); ++j)
		{
			if (roomInfo[i][j] == RoomTypes::ITEM)
			{
				door[i][j][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
				door[i][j][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
				door[i][j][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
				door[i][j][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
			}
		}
	}
}

void DoorEditing::FixSatanDoor()
{
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		for (int j = 0; j < roomInfo[i].size(); ++j)
		{
			if (roomInfo[i][j] == RoomTypes::SATAN)
			{
				door[i][j][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
				door[i][j][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
				door[i][j][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
				door[i][j][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
				// 항상 열려 있음
				door[i][j][0].doorState = DoorStates::OPENED;
				door[i][j][1].doorState = DoorStates::OPENED;
				door[i][j][2].doorState = DoorStates::OPENED;
				door[i][j][3].doorState = DoorStates::OPENED;
			}
		}
	}
}

void DoorEditing::IdentifyRoomType(int row, int column, int index)
{
	switch (roomInfo[row][column])
	{
	case RoomTypes::BOSS:
		door[row][column][index].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
		break;
	case RoomTypes::CURSE:
		door[row][column][index].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
		break;
	case RoomTypes::ITEM:
		door[row][column][index].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
		break;
	case RoomTypes::SATAN:
		door[row][column][index].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
		break;
	case RoomTypes::NORMAL:	case RoomTypes::PRIVATE: case RoomTypes::START:
		door[row][column][index].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
		break;
	default:
		break;
	}
}

void DoorEditing::StoreRoomType(int row, int column)
{
	int currRow = row;
	int currColumn = column;
	// 상, 하, 좌, 우 의 방으로 진입하기 위한 변수
	int topRow = row - 1;
	int bottomRow = row + 1;
	int leftColumn = column - 1;
	int rightColumn = column + 1;

	// 방을 기준으로 상, 하, 좌, 우 의 RoomTypes을 인식하여 Image 저장, 저장 할 때 특정 방들은 문이 항상 열려있다.
	// 상
	if (topRow >= 0)
	{
		switch (roomInfo[topRow][currColumn])
		{
		case RoomTypes::BOSS:
			door[currRow][currColumn][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
			break;
		case RoomTypes::CURSE:
			door[currRow][currColumn][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
			door[currRow][currColumn][0].doorState = DoorStates::OPENED;
			break;
		case RoomTypes::ITEM:
			door[currRow][currColumn][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
			door[currRow][currColumn][0].doorState = DoorStates::OPENED;
			break;
		case RoomTypes::NORMAL:	case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currRow][currColumn][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			break;
		default:
			break;
		}
	}
	// 하
	if (bottomRow < _stageSize)
	{
		switch (roomInfo[bottomRow][currColumn])
		{
		case RoomTypes::BOSS:
			door[currRow][currColumn][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
			break;
		case RoomTypes::CURSE:
			door[currRow][currColumn][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
			door[currRow][currColumn][1].doorState = DoorStates::OPENED;
			break;
		case RoomTypes::ITEM:
			door[currRow][currColumn][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
			door[currRow][currColumn][1].doorState = DoorStates::OPENED;
			break;
		case RoomTypes::NORMAL:	case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currRow][currColumn][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			break;
		default:
			break;
		}
	}
	// 좌
	if (leftColumn >= 0)
	{
		switch (roomInfo[currRow][leftColumn])
		{
		case RoomTypes::BOSS:
			door[currRow][currColumn][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
			break;
		case RoomTypes::CURSE:
			door[currRow][currColumn][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
			door[currRow][currColumn][2].doorState = DoorStates::OPENED;
			break;
		case RoomTypes::ITEM:
			door[currRow][currColumn][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
			door[currRow][currColumn][2].doorState = DoorStates::OPENED;
			break;
		case RoomTypes::NORMAL:	case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currRow][currColumn][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			break;
		default:
			break;
		}
	}
	// 우
	if (rightColumn < _stageSize)
	{
		switch (roomInfo[currRow][rightColumn])
		{
		case RoomTypes::BOSS:
			door[currRow][currColumn][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
			break;
		case RoomTypes::CURSE:
			door[currRow][currColumn][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
			door[currRow][currColumn][3].doorState = DoorStates::OPENED;
			break;
		case RoomTypes::ITEM:
			door[currRow][currColumn][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
			door[currRow][currColumn][3].doorState = DoorStates::OPENED;
			break;
		case RoomTypes::NORMAL:	case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currRow][currColumn][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			break;
		default:
			break;
		}
	}

	// 방문 확인
	isTransitMap[currRow][currColumn] = true;
	// 다음 맵으로 이동
	// 상
	if (topRow >= 0 && roomInfo[topRow][currColumn] != RoomTypes::NONE && isTransitMap[topRow][currColumn] == false)
	{
		StoreRoomType(topRow, currColumn);
	}
	// 하
	if (bottomRow < _stageSize && roomInfo[bottomRow][currColumn] != RoomTypes::NONE && isTransitMap[bottomRow][currColumn] == false)
	{
		StoreRoomType(bottomRow, currColumn);
	}
	// 좌
	if (leftColumn >= 0 && roomInfo[currRow][leftColumn] != RoomTypes::NONE && isTransitMap[currRow][leftColumn] == false)
	{
		StoreRoomType(currRow, leftColumn);
	}
	// 우
	if (rightColumn < _stageSize && roomInfo[currRow][rightColumn] != RoomTypes::NONE && isTransitMap[currRow][rightColumn] == false)
	{
		StoreRoomType(currRow, rightColumn);
	}
}
