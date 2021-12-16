#include "MainConfig.h"
#include "DoorEditing.h"

#include "Image.h"
#include "RoomEditing.h"

void DoorEditing::Release()
{
	SAFE_RELEASE(roomIndex);
}

void DoorEditing::Update()
{
#ifdef _DEBUG
	GameObject::Update();
#endif
	// DoorState 마다 문의 이미지 변화
	for (int i = 0; i < 4; ++i)
	{
		if (door[currLocatedRow][currLocatedColumn][i].img != nullptr)
		{
			if (door[currLocatedRow][currLocatedColumn][i].doorState == DoorStates::OPENED)
			{
				door[currLocatedRow][currLocatedColumn][i].img->SetCurrFrameY(0);
			}
			if (door[currLocatedRow][currLocatedColumn][i].img->GetMaxFrameY() >= 1 && door[currLocatedRow][currLocatedColumn][i].doorState == DoorStates::CLOSED)
			{
				door[currLocatedRow][currLocatedColumn][i].img->SetCurrFrameY(1);
			}
			if (door[currLocatedRow][currLocatedColumn][i].img->GetMaxFrameY() >= 2 && door[currLocatedRow][currLocatedColumn][i].doorState == DoorStates::LOCKED)
			{
				door[currLocatedRow][currLocatedColumn][i].img->SetCurrFrameY(2);
			}
		}
	}
	#pragma region SampleChangeDoorState
	// 예시) 키입력을 했을 때 해당 맵의 문을 OPENED 상태로 변화
	if (Input::GetButtonDown('O') )
	{
		for (int i = 0; i < 4; ++i)
		{
			if (door[currLocatedRow][currLocatedColumn][i].img != nullptr)
			{
				door[currLocatedRow][currLocatedColumn][i].doorState = DoorStates::OPENED;
			}
		}
	}
	if (Input::GetButtonDown('C'))
	{
		door[currLocatedRow][currLocatedColumn][0].doorState = DoorStates::CLOSED;
		door[currLocatedRow][currLocatedColumn][1].doorState = DoorStates::CLOSED;
		door[currLocatedRow][currLocatedColumn][2].doorState = DoorStates::CLOSED;
		door[currLocatedRow][currLocatedColumn][3].doorState = DoorStates::CLOSED;
	}
	#pragma endregion
	// DoorStates::OPENED 이고, 이미지가 있다면 shape을 작게 만든다.
	// 상
	if (door[currLocatedRow][currLocatedColumn][0].doorState == DoorStates::OPENED && door[currLocatedRow][currLocatedColumn][0].img != nullptr)
	{
		objectSize = 10.0f;
		door[currLocatedRow][currLocatedColumn][0].shape = {
			(LONG)(door[currLocatedRow][currLocatedColumn][0].pos.x - (objectSize * DEVIDE_HALF)),				// shape.left
			(LONG)(door[currLocatedRow][currLocatedColumn][0].pos.y - (objectSize * DEVIDE_HALF)),				// shape.top
			(LONG)(door[currLocatedRow][currLocatedColumn][0].pos.x + (objectSize * DEVIDE_HALF)),				// shape.right
			(LONG)(door[currLocatedRow][currLocatedColumn][0].pos.y + (objectSize * DEVIDE_HALF))				// shape.bottom
		};
	}
	// 하
	if (door[currLocatedRow][currLocatedColumn][1].doorState == DoorStates::OPENED && door[currLocatedRow][currLocatedColumn][1].img != nullptr)
	{
		objectSize = 10.0f;
		door[currLocatedRow][currLocatedColumn][1].shape = {
			(LONG)(door[currLocatedRow][currLocatedColumn][1].pos.x - (objectSize * DEVIDE_HALF)),				// shape.left
			(LONG)(door[currLocatedRow][currLocatedColumn][1].pos.y - (objectSize * DEVIDE_HALF)),				// shape.top
			(LONG)(door[currLocatedRow][currLocatedColumn][1].pos.x + (objectSize * DEVIDE_HALF)),				// shape.right
			(LONG)(door[currLocatedRow][currLocatedColumn][1].pos.y + (objectSize * DEVIDE_HALF))				// shape.bottom
		};
	}
	// 좌
	if (door[currLocatedRow][currLocatedColumn][2].doorState == DoorStates::OPENED && door[currLocatedRow][currLocatedColumn][2].img != nullptr)
	{
		objectSize = 10.0f;
		door[currLocatedRow][currLocatedColumn][2].shape = {
			(LONG)(door[currLocatedRow][currLocatedColumn][2].pos.x - (objectSize * DEVIDE_HALF)),				// shape.left
			(LONG)(door[currLocatedRow][currLocatedColumn][2].pos.y - (objectSize * DEVIDE_HALF) - 15),			// shape.top
			(LONG)(door[currLocatedRow][currLocatedColumn][2].pos.x + (objectSize * DEVIDE_HALF)),				// shape.right
			(LONG)(door[currLocatedRow][currLocatedColumn][2].pos.y + (objectSize * DEVIDE_HALF) + 15)			// shape.bottom
		};
	}
	// 우
	if (door[currLocatedRow][currLocatedColumn][3].doorState == DoorStates::OPENED && door[currLocatedRow][currLocatedColumn][3].img != nullptr)
	{
		objectSize = 10.0f;
		door[currLocatedRow][currLocatedColumn][3].shape = {
			(LONG)(door[currLocatedRow][currLocatedColumn][3].pos.x - (objectSize * DEVIDE_HALF)),				// shape.left
			(LONG)(door[currLocatedRow][currLocatedColumn][3].pos.y - (objectSize * DEVIDE_HALF) - 15),			// shape.top
			(LONG)(door[currLocatedRow][currLocatedColumn][3].pos.x + (objectSize * DEVIDE_HALF)),				// shape.right
			(LONG)(door[currLocatedRow][currLocatedColumn][3].pos.y + (objectSize * DEVIDE_HALF) + 15)			// shape.bottom
		};
	}
	#pragma region SampleChangeMap
	// 예시) 상,하,좌,우 키를 입력해서 맵을 바꿈.(문을 알아서 보여줘야함)
	if (Input::GetButtonDown(VK_UP))
	{
		int nextUpRow = currLocatedRow - 1;
		if (nextUpRow >= 0 && roomInfo[nextUpRow][currLocatedColumn] != RoomTypes::NONE)
		{
			--currLocatedRow;
		}
		if (currLocatedRow < 0)
		{
			currLocatedRow = 0;
		}
	}
	if (Input::GetButtonDown(VK_DOWN))
	{
		int nextDownRow = currLocatedRow + 1;
		if (nextDownRow < _stageSize && roomInfo[nextDownRow][currLocatedColumn] != RoomTypes::NONE)
		{
			++currLocatedRow;
		}
		if (currLocatedRow >= _stageSize)
		{
			currLocatedRow = _stageSize - 1;
		}
	}
	if (Input::GetButtonDown(VK_LEFT))
	{
		int nextLeftColumn = currLocatedColumn - 1;
		if (nextLeftColumn >= 0 && roomInfo[currLocatedRow][nextLeftColumn] != RoomTypes::NONE)
		{
			--currLocatedColumn;
		}
		if (currLocatedColumn < 0)
		{
			currLocatedColumn = 0;
		}
	}
	if (Input::GetButtonDown(VK_RIGHT))
	{
		int nextRightColumn = currLocatedColumn + 1;
		if (nextRightColumn < _stageSize && roomInfo[currLocatedRow][nextRightColumn] != RoomTypes::NONE)
		{
			++currLocatedColumn;
		}
		if (currLocatedColumn >= _stageSize)
		{
			currLocatedColumn = _stageSize - 1;
		}
	}
	#pragma endregion
}

void DoorEditing::Render(HDC hdc)
{
	// 상
	if (door[currLocatedRow][currLocatedColumn][0].img != nullptr) 
	{
		switch (door[currLocatedRow][currLocatedColumn][0].roomType)
		{
		case RoomTypes::BOSS: 
			door[currLocatedRow][currLocatedColumn][0].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][0].pos.x, (INT)door[currLocatedRow][currLocatedColumn][0].pos.y + 5, 0, door[currLocatedRow][currLocatedColumn][0].img->GetCurrFrameY());
			break;
		case RoomTypes::CURSE: case RoomTypes::ITEM: case RoomTypes::NORMAL: case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currLocatedRow][currLocatedColumn][0].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][0].pos.x, (INT)door[currLocatedRow][currLocatedColumn][0].pos.y, 0, door[currLocatedRow][currLocatedColumn][0].img->GetCurrFrameY());
			break;
		case RoomTypes::SATAN:
			door[currLocatedRow][currLocatedColumn][0].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][0].pos.x, (INT)door[currLocatedRow][currLocatedColumn][0].pos.y - 13, 0, door[currLocatedRow][currLocatedColumn][0].img->GetCurrFrameY());
			break;
		default:
			break;
		}
	}
	// 하
	if (door[currLocatedRow][currLocatedColumn][1].img != nullptr) 
	{
		switch (door[currLocatedRow][currLocatedColumn][1].roomType)
		{
		case RoomTypes::BOSS:
			door[currLocatedRow][currLocatedColumn][1].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][1].pos.x, (INT)door[currLocatedRow][currLocatedColumn][1].pos.y - 5, 1, door[currLocatedRow][currLocatedColumn][1].img->GetCurrFrameY());
			break;
		case RoomTypes::CURSE: case RoomTypes::ITEM: case RoomTypes::NORMAL: case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currLocatedRow][currLocatedColumn][1].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][1].pos.x, (INT)door[currLocatedRow][currLocatedColumn][1].pos.y, 1, door[currLocatedRow][currLocatedColumn][1].img->GetCurrFrameY());
			break;
		case RoomTypes::SATAN:
			door[currLocatedRow][currLocatedColumn][1].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][1].pos.x, (INT)door[currLocatedRow][currLocatedColumn][1].pos.y + 13, 1, door[currLocatedRow][currLocatedColumn][1].img->GetCurrFrameY());
			break;
		default:
			break;
		}
	}
	// 좌
	if (door[currLocatedRow][currLocatedColumn][2].img != nullptr) 
	{
		switch (door[currLocatedRow][currLocatedColumn][2].roomType)
		{
		case RoomTypes::BOSS:
			door[currLocatedRow][currLocatedColumn][2].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][2].pos.x + 15, (INT)door[currLocatedRow][currLocatedColumn][2].pos.y, 2, door[currLocatedRow][currLocatedColumn][2].img->GetCurrFrameY());
		break; case RoomTypes::CURSE: case RoomTypes::ITEM: case RoomTypes::NORMAL: case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currLocatedRow][currLocatedColumn][2].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][2].pos.x + 10, (INT)door[currLocatedRow][currLocatedColumn][2].pos.y, 2, door[currLocatedRow][currLocatedColumn][2].img->GetCurrFrameY());
			break;
		case RoomTypes::SATAN:
			door[currLocatedRow][currLocatedColumn][2].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][2].pos.x, (INT)door[currLocatedRow][currLocatedColumn][2].pos.y, 2, door[currLocatedRow][currLocatedColumn][2].img->GetCurrFrameY());
			break;
		default:
			break;
		}
	}
	// 우
	if (door[currLocatedRow][currLocatedColumn][3].img != nullptr) 
	{
		switch (door[currLocatedRow][currLocatedColumn][3].roomType)
		{
		case RoomTypes::BOSS:
			door[currLocatedRow][currLocatedColumn][3].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][3].pos.x - 15, (INT)door[currLocatedRow][currLocatedColumn][3].pos.y, 3, door[currLocatedRow][currLocatedColumn][3].img->GetCurrFrameY());
		break; 
		case RoomTypes::CURSE: case RoomTypes::ITEM: case RoomTypes::NORMAL: case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currLocatedRow][currLocatedColumn][3].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][3].pos.x - 10, (INT)door[currLocatedRow][currLocatedColumn][3].pos.y, 3, door[currLocatedRow][currLocatedColumn][3].img->GetCurrFrameY());
			break;
		case RoomTypes::SATAN:
			door[currLocatedRow][currLocatedColumn][3].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][3].pos.x, (INT)door[currLocatedRow][currLocatedColumn][3].pos.y, 3, door[currLocatedRow][currLocatedColumn][3].img->GetCurrFrameY());
			break;
		default:
			break;
		}
	}

	GameObject::Render(hdc);
}

void DoorEditing::OnDebug(HDC hdc)
{
	if (debugMode)
	{
		Rectangle(hdc, door[currLocatedRow][currLocatedColumn][0].shape.left, door[currLocatedRow][currLocatedColumn][0].shape.top, door[currLocatedRow][currLocatedColumn][0].shape.right, door[currLocatedRow][currLocatedColumn][0].shape.bottom);
		Rectangle(hdc, door[currLocatedRow][currLocatedColumn][1].shape.left, door[currLocatedRow][currLocatedColumn][1].shape.top, door[currLocatedRow][currLocatedColumn][1].shape.right, door[currLocatedRow][currLocatedColumn][1].shape.bottom);
		Rectangle(hdc, door[currLocatedRow][currLocatedColumn][2].shape.left, door[currLocatedRow][currLocatedColumn][2].shape.top, door[currLocatedRow][currLocatedColumn][2].shape.right, door[currLocatedRow][currLocatedColumn][2].shape.bottom);
		Rectangle(hdc, door[currLocatedRow][currLocatedColumn][3].shape.left, door[currLocatedRow][currLocatedColumn][3].shape.top, door[currLocatedRow][currLocatedColumn][3].shape.right, door[currLocatedRow][currLocatedColumn][3].shape.bottom);
	}
}

void DoorEditing::FixBossDoor()
{
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		for (size_t j = 0; j < roomInfo[i].size(); ++j)
		{
			if (roomInfo[i][j] == RoomTypes::BOSS)
			{
				int topRow = (INT)(i - 1);
				int bottomRow = (INT)(i + 1);
				int leftColumn = (INT)(j - 1);
				int rightColumn = (INT)(j + 1);
				// 이미지 변경, 사방향 전부 BossDoor
				if (topRow >= 0 && roomInfo[topRow][j] != RoomTypes::NONE)
				{
					door[i][j][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
					door[i][j][0].roomType = RoomTypes::BOSS;
				}
				if (bottomRow < _stageSize && roomInfo[bottomRow][j] != RoomTypes::NONE)
				{
					door[i][j][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
					door[i][j][1].roomType = RoomTypes::BOSS;
				}
				if (leftColumn >= 0 && roomInfo[i][leftColumn] != RoomTypes::NONE)
				{
					door[i][j][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
					door[i][j][2].roomType = RoomTypes::BOSS;

				}
				if (rightColumn < _stageSize && roomInfo[i][rightColumn] != RoomTypes::NONE)
				{
					door[i][j][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
					door[i][j][3].roomType = RoomTypes::BOSS;
				}
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
				int topRow = (INT)(i - 1);
				int bottomRow = (INT)(i + 1);
				int leftColumn = (INT)(j - 1);
				int rightColumn = (INT)(j + 1);
				// 이미지 변경, 항상 열려있음, 사방향 전부 BossDoor
				if (topRow >= 0 && roomInfo[topRow][j] != RoomTypes::NONE)
				{
					door[i][j][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
					door[i][j][0].doorState = DoorStates::OPENED;
					door[i][j][0].roomType = RoomTypes::CURSE;
				}
				if (bottomRow < _stageSize && roomInfo[bottomRow][j] != RoomTypes::NONE)
				{
					door[i][j][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
					door[i][j][1].doorState = DoorStates::OPENED;
					door[i][j][1].roomType = RoomTypes::CURSE;
				}
				if (leftColumn >= 0 && roomInfo[i][leftColumn] != RoomTypes::NONE)
				{
					door[i][j][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
					door[i][j][2].doorState = DoorStates::OPENED;
					door[i][j][2].roomType = RoomTypes::CURSE;
				}
				if (rightColumn < _stageSize && roomInfo[i][rightColumn] != RoomTypes::NONE)
				{
					door[i][j][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
					door[i][j][3].doorState = DoorStates::OPENED;
					door[i][j][3].roomType = RoomTypes::CURSE;
				}
			}
		}
	}
}

void DoorEditing::FixItemDoor()
{
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		for (size_t j = 0; j < roomInfo[i].size(); ++j)
		{
			if (roomInfo[i][j] == RoomTypes::ITEM)
			{
				int topRow = (INT)(i - 1);
				int bottomRow = (INT)(i + 1);
				int leftColumn = (INT)(j - 1);
				int rightColumn = (INT)(j + 1);
				// 이미지 변경, 사방향 전부 BossDoor
				if (topRow >= 0 && roomInfo[topRow][j] != RoomTypes::NONE)
				{
					door[i][j][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
					door[i][j][0].doorState = DoorStates::OPENED;
					door[i][j][0].roomType = RoomTypes::ITEM;
				}
				if (bottomRow < _stageSize && roomInfo[bottomRow][j] != RoomTypes::NONE)
				{
					door[i][j][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
					door[i][j][1].doorState = DoorStates::OPENED;
					door[i][j][1].roomType = RoomTypes::ITEM;
				}
				if (leftColumn >= 0 && roomInfo[i][leftColumn] != RoomTypes::NONE)
				{
					door[i][j][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
					door[i][j][2].doorState = DoorStates::OPENED;
					door[i][j][2].roomType = RoomTypes::ITEM;
				}
				if (rightColumn < _stageSize && roomInfo[i][rightColumn] != RoomTypes::NONE)
				{
					door[i][j][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
					door[i][j][3].doorState = DoorStates::OPENED;
					door[i][j][3].roomType = RoomTypes::ITEM;
				}
			}
		}
	}
}

void DoorEditing::FixPrivateDoor()
{
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		for (int j = 0; j < roomInfo[i].size(); ++j)
		{
			if (roomInfo[i][j] == RoomTypes::PRIVATE)
			{
				door[i][j][0].doorState = DoorStates::OPENED;
				door[i][j][1].doorState = DoorStates::OPENED;
				door[i][j][2].doorState = DoorStates::OPENED;
				door[i][j][3].doorState = DoorStates::OPENED;
			}
		}
	}
}

void DoorEditing::FixSatanDoor()
{
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		for (size_t j = 0; j < roomInfo[i].size(); ++j)
		{
			if (roomInfo[i][j] == RoomTypes::SATAN)
			{
				int topRow = (INT)(i - 1);
				int bottomRow = (INT)(i + 1);
				int leftColumn = (INT)(j - 1);
				int rightColumn = (INT)(j + 1);
				// 이미지 변경, 항상 열려있음, 사방향 전부 BossDoor
				if (topRow >= 0 && roomInfo[topRow][j] != RoomTypes::NONE)
				{
					door[i][j][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
					door[i][j][0].doorState = DoorStates::OPENED;
					door[i][j][0].roomType = RoomTypes::SATAN;
				}
				if (bottomRow < _stageSize && roomInfo[bottomRow][j] != RoomTypes::NONE)
				{
					door[i][j][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
					door[i][j][1].doorState = DoorStates::OPENED;
					door[i][j][1].roomType = RoomTypes::SATAN;
				}
				if (leftColumn >= 0 && roomInfo[i][leftColumn] != RoomTypes::NONE)
				{
					door[i][j][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
					door[i][j][2].doorState = DoorStates::OPENED;
					door[i][j][2].roomType = RoomTypes::SATAN;
				}
				if (rightColumn < _stageSize && roomInfo[i][rightColumn] != RoomTypes::NONE)
				{
					door[i][j][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
					door[i][j][3].doorState = DoorStates::OPENED;
					door[i][j][3].roomType = RoomTypes::SATAN;
				}
			}
		}
	}
}

void DoorEditing::FixStartDoor()
{
	door[currLocatedRow][currLocatedColumn][0].doorState = DoorStates::OPENED;
	door[currLocatedRow][currLocatedColumn][1].doorState = DoorStates::OPENED;
	door[currLocatedRow][currLocatedColumn][2].doorState = DoorStates::OPENED;
	door[currLocatedRow][currLocatedColumn][3].doorState = DoorStates::OPENED;
}

void DoorEditing::Init(int stageNum)
{
	roomIndex = new RoomEditing;
	roomIndex->Init(stageNum);
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
			door[i][j][0].roomType = RoomTypes::NONE;									// Door의 방향

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
			door[i][j][1].roomType = RoomTypes::NONE;									// Door의 방향

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
			door[i][j][2].roomType = RoomTypes::NONE;									// Door의 방향

			door[i][j][2].pos.x = 80.0f;												// terrain frameX 2
			door[i][j][2].pos.y = 400.0f;												// terrain frameY 10
			door[i][j][2].shape = {
				(LONG)(door[i][j][2].pos.x - (objectSize * DEVIDE_HALF)),				// shape.left
				(LONG)(door[i][j][2].pos.y - (objectSize * DEVIDE_HALF)),				// shape.top
				(LONG)(door[i][j][2].pos.x + (objectSize * DEVIDE_HALF)),				// shape.right
				(LONG)(door[i][j][2].pos.y + (objectSize * DEVIDE_HALF))				// shape.bottom
			};
			//RIGHT
			door[i][j][3].img = nullptr;
			door[i][j][3].doorState = DoorStates::CLOSED;								// Door의 상태
			door[i][j][3].doorDir = ObjectDir::RIGHT;									// Door의 방향
			door[i][j][3].roomType = RoomTypes::NONE;									// Door의 방향

			door[i][j][3].pos.x = 1200.0f;												// terrain frameX 29
			door[i][j][3].pos.y = 400.0f;												// terrain frameY 10
			door[i][j][3].shape = {
				(LONG)(door[i][j][3].pos.x - (objectSize * DEVIDE_HALF) + 17),			// shape.left
				(LONG)(door[i][j][3].pos.y - (objectSize * DEVIDE_HALF)),				// shape.top
				(LONG)(door[i][j][3].pos.x + (objectSize * DEVIDE_HALF)),				// shape.right
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

	// 현재 맵의 위치
	currLocatedRow = _startPoint;
	currLocatedColumn = _startPoint;

	// 특정 방들은 자기 방에 맞는 이미지를 가지게 함
	FixBossDoor();									// BossRoom
	FixCurseDoor();									// CurseRoom
	FixItemDoor();									// ItemRoom
	FixSatanDoor();									// SatanRoom
	// 특정 방들은 안의 모든 문이 열려있다.
	FixPrivateDoor();
	FixStartDoor();

	// DoorState에 따른 이미지 프레임 초기화
	for (size_t i = 0; i < door.size(); ++i)
	{
		for (size_t j = 0; j < door[i].size(); ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				if (door[i][j][k].img != nullptr)
				{
					if (door[i][j][k].doorState == DoorStates::OPENED)
					{
						door[i][j][k].img->SetCurrFrameY(0);
					}
					if (door[i][j][k].img->GetMaxFrameY() >= 1 && door[i][j][k].doorState == DoorStates::CLOSED)
					{
						door[i][j][k].img->SetCurrFrameY(1);
					}
					if (door[i][j][k].img->GetMaxFrameY() >= 2 && door[i][j][k].doorState == DoorStates::LOCKED)
					{
						door[i][j][k].img->SetCurrFrameY(2);
					}
				}
			}
		}
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

	// 방을 기준으로 상, 하, 좌, 우 의 RoomTypes을 인식하여 Image 저장, 저장 할 때 특정 방들은 문이 항상 열려있거나 잠겨있다.
	// 상
	if (topRow >= 0)
	{
		switch (roomInfo[topRow][currColumn])
		{
		case RoomTypes::BOSS:
			door[currRow][currColumn][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
			door[currRow][currColumn][0].roomType = RoomTypes::BOSS;
			break;
		case RoomTypes::CURSE:
			door[currRow][currColumn][0].doorState = DoorStates::OPENED;
			door[currRow][currColumn][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
			door[currRow][currColumn][0].roomType = RoomTypes::CURSE;
			break;
		case RoomTypes::ITEM:
			door[currRow][currColumn][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
			door[currRow][currColumn][0].roomType = RoomTypes::ITEM;
			break;
		case RoomTypes::NORMAL:
			door[currRow][currColumn][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][0].roomType = RoomTypes::NORMAL;
			break;
		case RoomTypes::PRIVATE:
			door[currRow][currColumn][0].doorState = DoorStates::CLOSED;
			door[currRow][currColumn][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][0].roomType = RoomTypes::PRIVATE;
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][0].doorState = DoorStates::OPENED;
			door[currRow][currColumn][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
			door[currRow][currColumn][0].roomType = RoomTypes::SATAN;
			break;
		case RoomTypes::START:
			door[currRow][currColumn][0].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][0].roomType = RoomTypes::START;
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
			door[currRow][currColumn][1].roomType = RoomTypes::BOSS;
			break;
		case RoomTypes::CURSE:
			door[currRow][currColumn][1].doorState = DoorStates::OPENED;
			door[currRow][currColumn][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
			door[currRow][currColumn][1].roomType = RoomTypes::CURSE;
			break;
		case RoomTypes::ITEM:
			door[currRow][currColumn][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
			door[currRow][currColumn][1].roomType = RoomTypes::ITEM;
			break;
		case RoomTypes::NORMAL:
			door[currRow][currColumn][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][1].roomType = RoomTypes::NORMAL;
			break;
		case RoomTypes::PRIVATE:
			door[currRow][currColumn][1].doorState = DoorStates::CLOSED;
			door[currRow][currColumn][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][1].roomType = RoomTypes::PRIVATE;
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][1].doorState = DoorStates::OPENED;
			door[currRow][currColumn][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
			door[currRow][currColumn][1].roomType = RoomTypes::SATAN;
			break;
		case RoomTypes::START:
			door[currRow][currColumn][1].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][1].roomType = RoomTypes::START;
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
			door[currRow][currColumn][2].roomType = RoomTypes::BOSS;
			break;
		case RoomTypes::CURSE:
			door[currRow][currColumn][2].doorState = DoorStates::OPENED;
			door[currRow][currColumn][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
			door[currRow][currColumn][2].roomType = RoomTypes::CURSE;
			break;
		case RoomTypes::ITEM:
			door[currRow][currColumn][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
			door[currRow][currColumn][2].roomType = RoomTypes::ITEM;
			break;
		case RoomTypes::NORMAL:
			door[currRow][currColumn][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][2].roomType = RoomTypes::NORMAL;
			break;
		case RoomTypes::PRIVATE:
			door[currRow][currColumn][2].doorState = DoorStates::CLOSED;
			door[currRow][currColumn][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][2].roomType = RoomTypes::PRIVATE;
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][2].doorState = DoorStates::OPENED;
			door[currRow][currColumn][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
			door[currRow][currColumn][2].roomType = RoomTypes::SATAN;
			break;
		case RoomTypes::START:
			door[currRow][currColumn][2].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][2].roomType = RoomTypes::START;
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
			door[currRow][currColumn][3].roomType = RoomTypes::BOSS;
			break;
		case RoomTypes::CURSE:
			door[currRow][currColumn][3].doorState = DoorStates::OPENED;
			door[currRow][currColumn][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
			door[currRow][currColumn][3].roomType = RoomTypes::CURSE;
			break;
		case RoomTypes::ITEM:
			door[currRow][currColumn][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
			door[currRow][currColumn][3].roomType = RoomTypes::ITEM;
			break;
		case RoomTypes::NORMAL:
			door[currRow][currColumn][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][3].roomType = RoomTypes::NORMAL;
			break;
		case RoomTypes::PRIVATE:
			door[currRow][currColumn][3].doorState = DoorStates::CLOSED;
			door[currRow][currColumn][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][3].roomType = RoomTypes::PRIVATE;
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][3].doorState = DoorStates::OPENED;
			door[currRow][currColumn][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
			door[currRow][currColumn][3].roomType = RoomTypes::SATAN;
			break;
		case RoomTypes::START:
			door[currRow][currColumn][3].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][3].roomType = RoomTypes::START;
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
