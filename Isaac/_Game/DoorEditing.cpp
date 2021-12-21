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
	// DoorState ���� ���� �̹��� ��ȭ
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
#ifdef _DEBUG
	#pragma region SampleChangeDoorState
	// ����) Ű�Է��� ���� �� �ش� ���� ���� OPENED ���·� ��ȭ
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
		door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].doorState = DoorStates::CLOSED;
		door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].doorState = DoorStates::CLOSED;
		door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].doorState = DoorStates::CLOSED;
		door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].doorState = DoorStates::CLOSED;
	}
	#pragma endregion
#endif
	// DoorStates::OPENED �̰�, �̹����� �ִٸ� shape�� �۰� �����.
	// ��
	if (door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].doorState == DoorStates::OPENED && door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].img != nullptr)
	{
		objectSize = 10.0f;
		door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].shape = {
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].pos.x - (objectSize * DEVIDE_HALF)),							// shape.left
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].pos.y - (objectSize * DEVIDE_HALF)),							// shape.top
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].pos.x + (objectSize * DEVIDE_HALF)),							// shape.right
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].pos.y + (objectSize * DEVIDE_HALF))							// shape.bottom
		};
	}
	// ��
	if (door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].doorState == DoorStates::OPENED && door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].img != nullptr)
	{
		objectSize = 10.0f;
		door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].shape = {
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].pos.x - (objectSize * DEVIDE_HALF)),							// shape.left
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].pos.y - (objectSize * DEVIDE_HALF)),							// shape.top
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].pos.x + (objectSize * DEVIDE_HALF)),							// shape.right
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].pos.y + (objectSize * DEVIDE_HALF))							// shape.bottom
		};
	}
	// ��
	if (door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].doorState == DoorStates::OPENED && door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].img != nullptr)
	{
		objectSize = 10.0f;
		door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].shape = {
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].pos.x - (objectSize * DEVIDE_HALF)),							// shape.left
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].pos.y - (objectSize * DEVIDE_HALF) - ADJUST_SIZE_15),		// shape.top
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].pos.x + (objectSize * DEVIDE_HALF)),							// shape.right
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].pos.y + (objectSize * DEVIDE_HALF) + ADJUST_SIZE_15)			// shape.bottom
		};
	}
	// ��
	if (door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].doorState == DoorStates::OPENED && door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].img != nullptr)
	{
		objectSize = 10.0f;
		door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].shape = {
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].pos.x - (objectSize * DEVIDE_HALF)),						// shape.left
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].pos.y - (objectSize * DEVIDE_HALF) - ADJUST_SIZE_15),		// shape.top
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].pos.x + (objectSize * DEVIDE_HALF)),						// shape.right
			(LONG)(door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].pos.y + (objectSize * DEVIDE_HALF) + ADJUST_SIZE_15)		// shape.bottom
		};
	}
	#pragma region SampleChangeMap
	// ����) ��,��,��,�� Ű�� �Է��ؼ� ���� �ٲ�.(���� �˾Ƽ� ���������)
	if (Input::GetButtonDown(VK_UP))
	{
		int nextUpRow = currLocatedRow - 1;
		if (nextUpRow >= OUT_OF_STAGE && roomInfo[nextUpRow][currLocatedColumn] != RoomTypes::NONE)
		{
			--currLocatedRow;
		}
		if (currLocatedRow < OUT_OF_STAGE)
		{
			currLocatedRow = OUT_OF_STAGE;
		}
	}
	if (Input::GetButtonDown(VK_DOWN))
	{
		int nextDownRow = currLocatedRow + 1;
		if (nextDownRow < stageSize && roomInfo[nextDownRow][currLocatedColumn] != RoomTypes::NONE)
		{
			++currLocatedRow;
		}
		if (currLocatedRow >= stageSize)
		{
			currLocatedRow = stageSize - 1;
		}
	}
	if (Input::GetButtonDown(VK_LEFT))
	{
		int nextLeftColumn = currLocatedColumn - 1;
		if (nextLeftColumn >= OUT_OF_STAGE && roomInfo[currLocatedRow][nextLeftColumn] != RoomTypes::NONE)
		{
			--currLocatedColumn;
		}
		if (currLocatedColumn < OUT_OF_STAGE)
		{
			currLocatedColumn = OUT_OF_STAGE;
		}
	}
	if (Input::GetButtonDown(VK_RIGHT))
	{
		int nextRightColumn = currLocatedColumn + 1;
		if (nextRightColumn < stageSize && roomInfo[currLocatedRow][nextRightColumn] != RoomTypes::NONE)
		{
			++currLocatedColumn;
		}
		if (currLocatedColumn >= stageSize)
		{
			currLocatedColumn = stageSize - 1;
		}
	}
	#pragma endregion
}

void DoorEditing::Render(HDC hdc)
{
	// ��
	if (door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].img != nullptr)
	{
		switch (door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].roomType)
		{
		case RoomTypes::BOSS: 
			door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].pos.x, (INT)door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].pos.y + 5, DOOR_UPSTATE, door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].img->GetCurrFrameY());
			break;
		case RoomTypes::CURSE: case RoomTypes::ITEM: case RoomTypes::NORMAL: case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].pos.x, (INT)door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].pos.y, DOOR_UPSTATE, door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].img->GetCurrFrameY());
			break;
		case RoomTypes::SATAN:
			door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].pos.x, (INT)door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].pos.y - 13, DOOR_UPSTATE, door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].img->GetCurrFrameY());
			break;
		default:
			break;
		}
	}
	// ��
	if (door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].img != nullptr) 
	{
		switch (door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].roomType)
		{
		case RoomTypes::BOSS:
			door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].pos.x, (INT)door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].pos.y - 5, DOOR_DOWNSTATE, door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].img->GetCurrFrameY());
			break;
		case RoomTypes::CURSE: case RoomTypes::ITEM: case RoomTypes::NORMAL: case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].pos.x, (INT)door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].pos.y, DOOR_DOWNSTATE, door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].img->GetCurrFrameY());
			break;
		case RoomTypes::SATAN:
			door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].pos.x, (INT)door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].pos.y + 13, DOOR_DOWNSTATE, door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].img->GetCurrFrameY());
			break;
		default:
			break;
		}
	}
	// ��
	if (door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].img != nullptr) 
	{
		switch (door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].roomType)
		{
		case RoomTypes::BOSS:
			door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].pos.x + 15, (INT)door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].pos.y, DOOR_LEFTSTATE, door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].img->GetCurrFrameY());
		break; case RoomTypes::CURSE: case RoomTypes::ITEM: case RoomTypes::NORMAL: case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].pos.x + 10, (INT)door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].pos.y, DOOR_LEFTSTATE, door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].img->GetCurrFrameY());
			break;
		case RoomTypes::SATAN:
			door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].pos.x, (INT)door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].pos.y, DOOR_LEFTSTATE, door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].img->GetCurrFrameY());
			break;
		default:
			break;
		}
	}
	// ��
	if (door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].img != nullptr) 
	{
		switch (door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].roomType)
		{
		case RoomTypes::BOSS:
			door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].pos.x - 15, (INT)door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].pos.y, DOOR_RIGHTSTATE, door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].img->GetCurrFrameY());
		break; 
		case RoomTypes::CURSE: case RoomTypes::ITEM: case RoomTypes::NORMAL: case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].pos.x - 10, (INT)door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].pos.y, DOOR_RIGHTSTATE, door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].img->GetCurrFrameY());
			break;
		case RoomTypes::SATAN:
			door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].img->Render(hdc, (INT)door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].pos.x, (INT)door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].pos.y, DOOR_RIGHTSTATE, door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].img->GetCurrFrameY());
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
		Rectangle(hdc, door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].shape.left, door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].shape.top, door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].shape.right, door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].shape.bottom);
		Rectangle(hdc, door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].shape.left, door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].shape.top, door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].shape.right, door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].shape.bottom);
		Rectangle(hdc, door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].shape.left, door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].shape.top, door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].shape.right, door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].shape.bottom);
		Rectangle(hdc, door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].shape.left, door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].shape.top, door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].shape.right, door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].shape.bottom);
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
				// �̹��� ����, ����� ���� BossDoor
				if (topRow >= OUT_OF_STAGE && roomInfo[topRow][j] != RoomTypes::NONE)
				{
					door[i][j][DOOR_UPSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
					door[i][j][DOOR_UPSTATE].roomType = RoomTypes::BOSS;
				}
				if (bottomRow < stageSize && roomInfo[bottomRow][j] != RoomTypes::NONE)
				{
					door[i][j][DOOR_DOWNSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
					door[i][j][DOOR_DOWNSTATE].roomType = RoomTypes::BOSS;
				}
				if (leftColumn >= OUT_OF_STAGE && roomInfo[i][leftColumn] != RoomTypes::NONE)
				{
					door[i][j][DOOR_LEFTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
					door[i][j][DOOR_LEFTSTATE].roomType = RoomTypes::BOSS;

				}
				if (rightColumn < stageSize && roomInfo[i][rightColumn] != RoomTypes::NONE)
				{
					door[i][j][DOOR_RIGHTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
					door[i][j][DOOR_RIGHTSTATE].roomType = RoomTypes::BOSS;
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
				// �̹��� ����, �׻� ��������, ����� ���� CurseDoor
				if (topRow >= OUT_OF_STAGE && roomInfo[topRow][j] != RoomTypes::NONE)
				{
					door[i][j][DOOR_UPSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
					door[i][j][DOOR_UPSTATE].doorState = DoorStates::OPENED;
					door[i][j][DOOR_UPSTATE].roomType = RoomTypes::CURSE;
				}
				if (bottomRow < stageSize && roomInfo[bottomRow][j] != RoomTypes::NONE)
				{
					door[i][j][DOOR_DOWNSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
					door[i][j][DOOR_DOWNSTATE].doorState = DoorStates::OPENED;
					door[i][j][DOOR_DOWNSTATE].roomType = RoomTypes::CURSE;
				}
				if (leftColumn >= OUT_OF_STAGE && roomInfo[i][leftColumn] != RoomTypes::NONE)
				{
					door[i][j][DOOR_LEFTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
					door[i][j][DOOR_LEFTSTATE].doorState = DoorStates::OPENED;
					door[i][j][DOOR_LEFTSTATE].roomType = RoomTypes::CURSE;
				}
				if (rightColumn < stageSize && roomInfo[i][rightColumn] != RoomTypes::NONE)
				{
					door[i][j][DOOR_RIGHTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
					door[i][j][DOOR_RIGHTSTATE].doorState = DoorStates::OPENED;
					door[i][j][DOOR_RIGHTSTATE].roomType = RoomTypes::CURSE;
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
				// �̹��� ����, ����� ���� ItemDoor
				if (topRow >= OUT_OF_STAGE && roomInfo[topRow][j] != RoomTypes::NONE)
				{
					door[i][j][DOOR_UPSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
					door[i][j][DOOR_UPSTATE].doorState = DoorStates::OPENED;
					door[i][j][DOOR_UPSTATE].roomType = RoomTypes::ITEM;
				}
				if (bottomRow < stageSize && roomInfo[bottomRow][j] != RoomTypes::NONE)
				{
					door[i][j][DOOR_DOWNSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
					door[i][j][DOOR_DOWNSTATE].doorState = DoorStates::OPENED;
					door[i][j][DOOR_DOWNSTATE].roomType = RoomTypes::ITEM;
				}
				if (leftColumn >= OUT_OF_STAGE && roomInfo[i][leftColumn] != RoomTypes::NONE)
				{
					door[i][j][DOOR_LEFTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
					door[i][j][DOOR_LEFTSTATE].doorState = DoorStates::OPENED;
					door[i][j][DOOR_LEFTSTATE].roomType = RoomTypes::ITEM;
				}
				if (rightColumn < stageSize && roomInfo[i][rightColumn] != RoomTypes::NONE)
				{
					door[i][j][DOOR_RIGHTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
					door[i][j][DOOR_RIGHTSTATE].doorState = DoorStates::OPENED;
					door[i][j][DOOR_RIGHTSTATE].roomType = RoomTypes::ITEM;
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
				int topRow = (INT)(i - 1);
				int bottomRow = (INT)(i + 1);
				int leftColumn = (INT)(j - 1);
				int rightColumn = (INT)(j + 1);
				// ���� ���� �ִ��� Ȯ���Ͽ� ���� ����
				if (topRow >= OUT_OF_STAGE && roomInfo[topRow][j] != RoomTypes::NONE)
				{
					door[i][j][DOOR_UPSTATE].doorState = DoorStates::OPENED;
				}
				if (bottomRow < stageSize && roomInfo[bottomRow][j] != RoomTypes::NONE)
				{
					door[i][j][DOOR_DOWNSTATE].doorState = DoorStates::OPENED;
				}
				if (leftColumn >= OUT_OF_STAGE && roomInfo[i][leftColumn] != RoomTypes::NONE)
				{
					door[i][j][DOOR_LEFTSTATE].doorState = DoorStates::OPENED;
				}
				if (rightColumn < stageSize && roomInfo[i][rightColumn] != RoomTypes::NONE)
				{
					door[i][j][DOOR_RIGHTSTATE].doorState = DoorStates::OPENED;
				}
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
				// �̹��� ����, �׻� ��������, ����� ���� SatanDoor
				if (topRow >= OUT_OF_STAGE && roomInfo[topRow][j] != RoomTypes::NONE)
				{
					door[i][j][DOOR_UPSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
					door[i][j][DOOR_UPSTATE].doorState = DoorStates::OPENED;
					door[i][j][DOOR_UPSTATE].roomType = RoomTypes::SATAN;
				}
				if (bottomRow < stageSize && roomInfo[bottomRow][j] != RoomTypes::NONE)
				{
					door[i][j][DOOR_DOWNSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
					door[i][j][DOOR_DOWNSTATE].doorState = DoorStates::OPENED;
					door[i][j][DOOR_DOWNSTATE].roomType = RoomTypes::SATAN;
				}
				if (leftColumn >= OUT_OF_STAGE && roomInfo[i][leftColumn] != RoomTypes::NONE)
				{
					door[i][j][DOOR_LEFTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
					door[i][j][DOOR_LEFTSTATE].doorState = DoorStates::OPENED;
					door[i][j][DOOR_LEFTSTATE].roomType = RoomTypes::SATAN;
				}
				if (rightColumn < stageSize && roomInfo[i][rightColumn] != RoomTypes::NONE)
				{
					door[i][j][DOOR_RIGHTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
					door[i][j][DOOR_RIGHTSTATE].doorState = DoorStates::OPENED;
					door[i][j][DOOR_RIGHTSTATE].roomType = RoomTypes::SATAN;
				}
			}
		}
	}
}

void DoorEditing::FixStartDoor()
{
	int topRow = (INT)(currLocatedRow - 1);
	int bottomRow = (INT)(currLocatedRow + 1);
	int leftColumn = (INT)(currLocatedColumn - 1);
	int rightColumn = (INT)(currLocatedColumn + 1);
	// ���� ���� �ִ��� Ȯ���Ͽ� ���� ����
	if (topRow >= OUT_OF_STAGE && roomInfo[topRow][currLocatedColumn] != RoomTypes::NONE)
	{
		door[currLocatedRow][currLocatedColumn][DOOR_UPSTATE].doorState = DoorStates::OPENED;
	}
	if (bottomRow < stageSize && roomInfo[bottomRow][currLocatedColumn] != RoomTypes::NONE)
	{
		door[currLocatedRow][currLocatedColumn][DOOR_DOWNSTATE].doorState = DoorStates::OPENED;
	}
	if (leftColumn >= OUT_OF_STAGE && roomInfo[currLocatedRow][leftColumn] != RoomTypes::NONE)
	{
		door[currLocatedRow][currLocatedColumn][DOOR_LEFTSTATE].doorState = DoorStates::OPENED;
	}
	if (rightColumn < stageSize && roomInfo[currLocatedRow][rightColumn] != RoomTypes::NONE)
	{
		door[currLocatedRow][currLocatedColumn][DOOR_RIGHTSTATE].doorState = DoorStates::OPENED;
	}
}

void DoorEditing::Init(int stageNum)
{
	roomIndex = new RoomEditing;
	roomIndex->Init(stageNum);
	// Stage01�� Size�� �ޱ�
	stageSize = roomIndex->GetStageSize();
	// StartPoint�� �ޱ�
	startPoint = roomIndex->GetStartPoint();
	// Stage Size��ŭ resize �ϰ�
	stage01Index.resize(stageSize);
	for (size_t i = 0; i < stage01Index.size(); ++i)
	{
		stage01Index[i].resize(stageSize);
		for (size_t j = 0; j < stage01Index[i].size(); ++j)
		{
			stage01Index[i][j] = roomIndex->GetStage()[i][j];
		}
	}
	// Room Size��ŭ resize�ϰ�
	roomInfo.resize(stageSize);
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		roomInfo[i].resize(stageSize);
		for (size_t j = 0; j < roomInfo[i].size(); ++j)
		{
			// Room�� ������ ��������
			roomInfo[i][j] = roomIndex->GetRoomType()[i][j];
		}
	}

	// ������ Room���� DOOR_INFO�� ������ ���ߺ��� �ʱ�ȭ
	door.resize(stageSize);
	for (size_t i = 0; i < door.size(); ++i)
	{
		door[i].resize(stageSize);
		for (size_t j = 0; j < door[i].size(); ++j)
		{
			// Door�� Size
			objectSize = 80.0f;
			//UP
			door[i][j][DOOR_UPSTATE].img = nullptr;
			door[i][j][DOOR_UPSTATE].doorState = DoorStates::CLOSED;										// Door�� ����
			door[i][j][DOOR_UPSTATE].doorDir = ObjectDir::UP;												// Door�� ����
			door[i][j][DOOR_UPSTATE].roomType = RoomTypes::NONE;											// Door�� ����

			door[i][j][DOOR_UPSTATE].pos.x = 640.0f;														// terrain frameX 16
			door[i][j][DOOR_UPSTATE].pos.y = 80.0f;															// terrain frameY 2
			door[i][j][DOOR_UPSTATE].shape = {
				(LONG)(door[i][j][DOOR_UPSTATE].pos.x - (objectSize * DEVIDE_HALF)),						// shape.left
				(LONG)(door[i][j][DOOR_UPSTATE].pos.y - (objectSize * DEVIDE_HALF) - ADJUST_SIZE_40),		// shape.top
				(LONG)(door[i][j][DOOR_UPSTATE].pos.x + (objectSize * DEVIDE_HALF)),						// shape.right
				(LONG)(door[i][j][DOOR_UPSTATE].pos.y + (objectSize * DEVIDE_HALF))							// shape.bottom
			};
			//DOWN
			door[i][j][DOOR_DOWNSTATE].img = nullptr;
			door[i][j][DOOR_DOWNSTATE].doorState = DoorStates::CLOSED;										// Door�� ����
			door[i][j][DOOR_DOWNSTATE].doorDir = ObjectDir::DOWN;											// Door�� ����
			door[i][j][DOOR_DOWNSTATE].roomType = RoomTypes::NONE;											// Door�� ����

			door[i][j][DOOR_DOWNSTATE].pos.x = 640.0f;														// terrain frameX 16
			door[i][j][DOOR_DOWNSTATE].pos.y = 720.0f;														// terrain frameY 18
			door[i][j][DOOR_DOWNSTATE].shape = {
				(LONG)(door[i][j][DOOR_DOWNSTATE].pos.x - (objectSize * DEVIDE_HALF)),						// shape.left
				(LONG)(door[i][j][DOOR_DOWNSTATE].pos.y - (objectSize * DEVIDE_HALF)),						// shape.top
				(LONG)(door[i][j][DOOR_DOWNSTATE].pos.x + (objectSize * DEVIDE_HALF)),						// shape.right
				(LONG)(door[i][j][DOOR_DOWNSTATE].pos.y + (objectSize * DEVIDE_HALF) + ADJUST_SIZE_40)		// shape.bottom
			};
			//LEFT
			door[i][j][DOOR_LEFTSTATE].img = nullptr;
			door[i][j][DOOR_LEFTSTATE].doorState = DoorStates::CLOSED;										// Door�� ����
			door[i][j][DOOR_LEFTSTATE].doorDir = ObjectDir::LEFT;											// Door�� ����
			door[i][j][DOOR_LEFTSTATE].roomType = RoomTypes::NONE;											// Door�� ����

			door[i][j][DOOR_LEFTSTATE].pos.x = 80.0f;														// terrain frameX 2
			door[i][j][DOOR_LEFTSTATE].pos.y = 400.0f;														// terrain frameY 10
			door[i][j][DOOR_LEFTSTATE].shape = {
				(LONG)(door[i][j][DOOR_LEFTSTATE].pos.x - (objectSize * DEVIDE_HALF)),						// shape.left
				(LONG)(door[i][j][DOOR_LEFTSTATE].pos.y - (objectSize * DEVIDE_HALF)),						// shape.top
				(LONG)(door[i][j][DOOR_LEFTSTATE].pos.x + (objectSize * DEVIDE_HALF) - ADJUST_SIZE_13),		// shape.right
				(LONG)(door[i][j][DOOR_LEFTSTATE].pos.y + (objectSize * DEVIDE_HALF))						// shape.bottom
			};
			//RIGHT
			door[i][j][DOOR_RIGHTSTATE].img = nullptr;
			door[i][j][DOOR_RIGHTSTATE].doorState = DoorStates::CLOSED;										// Door�� ����
			door[i][j][DOOR_RIGHTSTATE].doorDir = ObjectDir::RIGHT;											// Door�� ����
			door[i][j][DOOR_RIGHTSTATE].roomType = RoomTypes::NONE;											// Door�� ����

			door[i][j][DOOR_RIGHTSTATE].pos.x = 1200.0f;													// terrain frameX 29
			door[i][j][DOOR_RIGHTSTATE].pos.y = 400.0f;														// terrain frameY 10
			door[i][j][DOOR_RIGHTSTATE].shape = {
				(LONG)(door[i][j][DOOR_RIGHTSTATE].pos.x - (objectSize * DEVIDE_HALF) + ADJUST_SIZE_13),	// shape.left
				(LONG)(door[i][j][DOOR_RIGHTSTATE].pos.y - (objectSize * DEVIDE_HALF)),						// shape.top
				(LONG)(door[i][j][DOOR_RIGHTSTATE].pos.x + (objectSize * DEVIDE_HALF)),						// shape.right
				(LONG)(door[i][j][DOOR_RIGHTSTATE].pos.y + (objectSize * DEVIDE_HALF))						// shape.bottom
			};
		}
	}

	// ����ߴ����� ���θ� �˱� ���� ���� ���� �ʱ�ȭ
	isTransitMap.resize(stageSize);
	for (size_t i = 0; i < isTransitMap.size(); ++i)
	{
		isTransitMap[i].resize(stageSize);
		for (size_t j = 0; j < isTransitMap[i].size(); ++j)
		{
			isTransitMap[i][j] = false;
		}
	}

	// �湮�ϸ鼭 ������ �� ���� ��, ��, ��, �� �� RoomType���� �Ǻ��ؼ� Image���� ����
	StoreRoomType(startPoint, startPoint);

	// ���� ���� ��ġ
	currLocatedRow = startPoint;
	currLocatedColumn = startPoint;

	// Ư�� ����� �ڱ� �濡 �´� �̹����� ������ ��
	FixBossDoor();									// BossRoom
	FixCurseDoor();									// CurseRoom
	FixItemDoor();									// ItemRoom
	FixSatanDoor();									// SatanRoom
	// Ư�� ����� ���� ��� ���� �����ִ�.
	FixPrivateDoor();
	FixStartDoor();

	// DoorState�� ���� �̹��� ������ �ʱ�ȭ
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
	// ��, ��, ��, �� �� ������ �����ϱ� ���� ����
	int topRow = row - 1;
	int bottomRow = row + 1;
	int leftColumn = column - 1;
	int rightColumn = column + 1;

	// ���� �������� ��, ��, ��, �� �� RoomTypes�� �ν��Ͽ� Image ����, ���� �� �� Ư�� ����� ���� �׻� �����ְų� ����ִ�.
	// ��
	if (topRow >= OUT_OF_STAGE)
	{
		switch (roomInfo[topRow][currColumn])
		{
		case RoomTypes::BOSS:
			door[currRow][currColumn][DOOR_UPSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
			door[currRow][currColumn][DOOR_UPSTATE].roomType = RoomTypes::BOSS;
			break;
		case RoomTypes::CURSE:
			door[currRow][currColumn][DOOR_UPSTATE].doorState = DoorStates::OPENED;
			door[currRow][currColumn][DOOR_UPSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
			door[currRow][currColumn][DOOR_UPSTATE].roomType = RoomTypes::CURSE;
			break;
		case RoomTypes::ITEM:
			door[currRow][currColumn][DOOR_UPSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
			door[currRow][currColumn][DOOR_UPSTATE].roomType = RoomTypes::ITEM;
			break;
		case RoomTypes::NORMAL:
			door[currRow][currColumn][DOOR_UPSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][DOOR_UPSTATE].roomType = RoomTypes::NORMAL;
			break;
		case RoomTypes::PRIVATE:
			door[currRow][currColumn][DOOR_UPSTATE].doorState = DoorStates::CLOSED;
			door[currRow][currColumn][DOOR_UPSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][DOOR_UPSTATE].roomType = RoomTypes::PRIVATE;
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][DOOR_UPSTATE].doorState = DoorStates::OPENED;
			door[currRow][currColumn][DOOR_UPSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
			door[currRow][currColumn][DOOR_UPSTATE].roomType = RoomTypes::SATAN;
			break;
		case RoomTypes::START:
			door[currRow][currColumn][DOOR_UPSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][DOOR_UPSTATE].roomType = RoomTypes::START;
			break;
		default:
			break;
		}
	}
	// ��
	if (bottomRow < stageSize)
	{
		switch (roomInfo[bottomRow][currColumn])
		{
		case RoomTypes::BOSS:
			door[currRow][currColumn][DOOR_DOWNSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
			door[currRow][currColumn][DOOR_DOWNSTATE].roomType = RoomTypes::BOSS;
			break;
		case RoomTypes::CURSE:
			door[currRow][currColumn][DOOR_DOWNSTATE].doorState = DoorStates::OPENED;
			door[currRow][currColumn][DOOR_DOWNSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
			door[currRow][currColumn][DOOR_DOWNSTATE].roomType = RoomTypes::CURSE;
			break;
		case RoomTypes::ITEM:
			door[currRow][currColumn][DOOR_DOWNSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
			door[currRow][currColumn][DOOR_DOWNSTATE].roomType = RoomTypes::ITEM;
			break;
		case RoomTypes::NORMAL:
			door[currRow][currColumn][DOOR_DOWNSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][DOOR_DOWNSTATE].roomType = RoomTypes::NORMAL;
			break;
		case RoomTypes::PRIVATE:
			door[currRow][currColumn][DOOR_DOWNSTATE].doorState = DoorStates::CLOSED;
			door[currRow][currColumn][DOOR_DOWNSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][DOOR_DOWNSTATE].roomType = RoomTypes::PRIVATE;
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][DOOR_DOWNSTATE].doorState = DoorStates::OPENED;
			door[currRow][currColumn][DOOR_DOWNSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
			door[currRow][currColumn][DOOR_DOWNSTATE].roomType = RoomTypes::SATAN;
			break;
		case RoomTypes::START:
			door[currRow][currColumn][DOOR_DOWNSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][DOOR_DOWNSTATE].roomType = RoomTypes::START;
			break;
		default:
			break;
		}
	}
	// ��
	if (leftColumn >= OUT_OF_STAGE)
	{
		switch (roomInfo[currRow][leftColumn])
		{
		case RoomTypes::BOSS:
			door[currRow][currColumn][DOOR_LEFTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
			door[currRow][currColumn][DOOR_LEFTSTATE].roomType = RoomTypes::BOSS;
			break;
		case RoomTypes::CURSE:
			door[currRow][currColumn][DOOR_LEFTSTATE].doorState = DoorStates::OPENED;
			door[currRow][currColumn][DOOR_LEFTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
			door[currRow][currColumn][DOOR_LEFTSTATE].roomType = RoomTypes::CURSE;
			break;
		case RoomTypes::ITEM:
			door[currRow][currColumn][DOOR_LEFTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
			door[currRow][currColumn][DOOR_LEFTSTATE].roomType = RoomTypes::ITEM;
			break;
		case RoomTypes::NORMAL:
			door[currRow][currColumn][DOOR_LEFTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][DOOR_LEFTSTATE].roomType = RoomTypes::NORMAL;
			break;
		case RoomTypes::PRIVATE:
			door[currRow][currColumn][DOOR_LEFTSTATE].doorState = DoorStates::CLOSED;
			door[currRow][currColumn][DOOR_LEFTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][DOOR_LEFTSTATE].roomType = RoomTypes::PRIVATE;
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][DOOR_LEFTSTATE].doorState = DoorStates::OPENED;
			door[currRow][currColumn][DOOR_LEFTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
			door[currRow][currColumn][DOOR_LEFTSTATE].roomType = RoomTypes::SATAN;
			break;
		case RoomTypes::START:
			door[currRow][currColumn][DOOR_LEFTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][DOOR_LEFTSTATE].roomType = RoomTypes::START;
			break;
		default:
			break;
		}
	}
	// ��
	if (rightColumn < stageSize)
	{
		switch (roomInfo[currRow][rightColumn])
		{
		case RoomTypes::BOSS:
			door[currRow][currColumn][DOOR_RIGHTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
			door[currRow][currColumn][DOOR_RIGHTSTATE].roomType = RoomTypes::BOSS;
			break;
		case RoomTypes::CURSE:
			door[currRow][currColumn][DOOR_RIGHTSTATE].doorState = DoorStates::OPENED;
			door[currRow][currColumn][DOOR_RIGHTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
			door[currRow][currColumn][DOOR_RIGHTSTATE].roomType = RoomTypes::CURSE;
			break;
		case RoomTypes::ITEM:
			door[currRow][currColumn][DOOR_RIGHTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
			door[currRow][currColumn][DOOR_RIGHTSTATE].roomType = RoomTypes::ITEM;
			break;
		case RoomTypes::NORMAL:
			door[currRow][currColumn][DOOR_RIGHTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][DOOR_RIGHTSTATE].roomType = RoomTypes::NORMAL;
			break;
		case RoomTypes::PRIVATE:
			door[currRow][currColumn][DOOR_RIGHTSTATE].doorState = DoorStates::CLOSED;
			door[currRow][currColumn][DOOR_RIGHTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][DOOR_RIGHTSTATE].roomType = RoomTypes::PRIVATE;
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][DOOR_RIGHTSTATE].doorState = DoorStates::OPENED;
			door[currRow][currColumn][DOOR_RIGHTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
			door[currRow][currColumn][DOOR_RIGHTSTATE].roomType = RoomTypes::SATAN;
			break;
		case RoomTypes::START:
			door[currRow][currColumn][DOOR_RIGHTSTATE].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
			door[currRow][currColumn][DOOR_RIGHTSTATE].roomType = RoomTypes::START;
			break;
		default:
			break;
		}
	}

	// �湮 Ȯ��
	isTransitMap[currRow][currColumn] = true;
	// ���� ������ �̵�
	// ��
	if (topRow >= OUT_OF_STAGE && roomInfo[topRow][currColumn] != RoomTypes::NONE && isTransitMap[topRow][currColumn] == false)
	{
		StoreRoomType(topRow, currColumn);
	}
	// ��
	if (bottomRow < stageSize && roomInfo[bottomRow][currColumn] != RoomTypes::NONE && isTransitMap[bottomRow][currColumn] == false)
	{
		StoreRoomType(bottomRow, currColumn);
	}
	// ��
	if (leftColumn >= OUT_OF_STAGE && roomInfo[currRow][leftColumn] != RoomTypes::NONE && isTransitMap[currRow][leftColumn] == false)
	{
		StoreRoomType(currRow, leftColumn);
	}
	// ��
	if (rightColumn < stageSize && roomInfo[currRow][rightColumn] != RoomTypes::NONE && isTransitMap[currRow][rightColumn] == false)
	{
		StoreRoomType(currRow, rightColumn);
	}
}
