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

	// Door�� ���¿� ���� �̹��� ��ȭ
	ChangeImageDoorState();

	// ���� Map�� Monster�� ������ Door Open State
	OpenTheDoor();

	// Door�� Open ���� �� �� ũ�� ��ȭ
	ChangeShapeOpenDoor();
}

void DoorEditing::Render(HDC hdc)
{
	// ��
	if (door[currRow][currColumn][UPPER_DOOR].img != nullptr)
	{
		switch (door[currRow][currColumn][UPPER_DOOR].roomType)
		{
		case RoomTypes::BOSS: 
			door[currRow][currColumn][UPPER_DOOR].img->Render(hdc, (INT)door[currRow][currColumn][UPPER_DOOR].pos.x, (INT)door[currRow][currColumn][UPPER_DOOR].pos.y + 5, UPPER_DOOR, door[currRow][currColumn][UPPER_DOOR].img->GetCurrFrameY());
			break;
		case RoomTypes::CURSE: case RoomTypes::ITEM: case RoomTypes::NORMAL: case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currRow][currColumn][UPPER_DOOR].img->Render(hdc, (INT)door[currRow][currColumn][UPPER_DOOR].pos.x, (INT)door[currRow][currColumn][UPPER_DOOR].pos.y, UPPER_DOOR, door[currRow][currColumn][UPPER_DOOR].img->GetCurrFrameY());
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][UPPER_DOOR].img->Render(hdc, (INT)door[currRow][currColumn][UPPER_DOOR].pos.x, (INT)door[currRow][currColumn][UPPER_DOOR].pos.y - 13, UPPER_DOOR, door[currRow][currColumn][UPPER_DOOR].img->GetCurrFrameY());
			break;
		default:
			break;
		}
	}
	// ��
	if (door[currRow][currColumn][LOWER_DOOR].img != nullptr) 
	{
		switch (door[currRow][currColumn][LOWER_DOOR].roomType)
		{
		case RoomTypes::BOSS:
			door[currRow][currColumn][LOWER_DOOR].img->Render(hdc, (INT)door[currRow][currColumn][LOWER_DOOR].pos.x, (INT)door[currRow][currColumn][LOWER_DOOR].pos.y - 5, LOWER_DOOR, door[currRow][currColumn][LOWER_DOOR].img->GetCurrFrameY());
			break;
		case RoomTypes::CURSE: case RoomTypes::ITEM: case RoomTypes::NORMAL: case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currRow][currColumn][LOWER_DOOR].img->Render(hdc, (INT)door[currRow][currColumn][LOWER_DOOR].pos.x, (INT)door[currRow][currColumn][LOWER_DOOR].pos.y, LOWER_DOOR, door[currRow][currColumn][LOWER_DOOR].img->GetCurrFrameY());
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][LOWER_DOOR].img->Render(hdc, (INT)door[currRow][currColumn][LOWER_DOOR].pos.x, (INT)door[currRow][currColumn][LOWER_DOOR].pos.y + 13, LOWER_DOOR, door[currRow][currColumn][LOWER_DOOR].img->GetCurrFrameY());
			break;
		default:
			break;
		}
	}
	// ��
	if (door[currRow][currColumn][LEFT_DOOR].img != nullptr) 
	{
		switch (door[currRow][currColumn][LEFT_DOOR].roomType)
		{
		case RoomTypes::BOSS:
			door[currRow][currColumn][LEFT_DOOR].img->Render(hdc, (INT)door[currRow][currColumn][LEFT_DOOR].pos.x + 15, (INT)door[currRow][currColumn][LEFT_DOOR].pos.y, LEFT_DOOR, door[currRow][currColumn][LEFT_DOOR].img->GetCurrFrameY());
		break; case RoomTypes::CURSE: case RoomTypes::ITEM: case RoomTypes::NORMAL: case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currRow][currColumn][LEFT_DOOR].img->Render(hdc, (INT)door[currRow][currColumn][LEFT_DOOR].pos.x + 10, (INT)door[currRow][currColumn][LEFT_DOOR].pos.y, LEFT_DOOR, door[currRow][currColumn][LEFT_DOOR].img->GetCurrFrameY());
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][LEFT_DOOR].img->Render(hdc, (INT)door[currRow][currColumn][LEFT_DOOR].pos.x, (INT)door[currRow][currColumn][LEFT_DOOR].pos.y, LEFT_DOOR, door[currRow][currColumn][LEFT_DOOR].img->GetCurrFrameY());
			break;
		default:
			break;
		}
	}
	// ��
	if (door[currRow][currColumn][RIGHT_DOOR].img != nullptr) 
	{
		switch (door[currRow][currColumn][RIGHT_DOOR].roomType)
		{
		case RoomTypes::BOSS:
			door[currRow][currColumn][RIGHT_DOOR].img->Render(hdc, (INT)door[currRow][currColumn][RIGHT_DOOR].pos.x - 15, (INT)door[currRow][currColumn][RIGHT_DOOR].pos.y, RIGHT_DOOR, door[currRow][currColumn][RIGHT_DOOR].img->GetCurrFrameY());
		break; 
		case RoomTypes::CURSE: case RoomTypes::ITEM: case RoomTypes::NORMAL: case RoomTypes::PRIVATE: case RoomTypes::START:
			door[currRow][currColumn][RIGHT_DOOR].img->Render(hdc, (INT)door[currRow][currColumn][RIGHT_DOOR].pos.x - 10, (INT)door[currRow][currColumn][RIGHT_DOOR].pos.y, RIGHT_DOOR, door[currRow][currColumn][RIGHT_DOOR].img->GetCurrFrameY());
			break;
		case RoomTypes::SATAN:
			door[currRow][currColumn][RIGHT_DOOR].img->Render(hdc, (INT)door[currRow][currColumn][RIGHT_DOOR].pos.x, (INT)door[currRow][currColumn][RIGHT_DOOR].pos.y, RIGHT_DOOR, door[currRow][currColumn][RIGHT_DOOR].img->GetCurrFrameY());
			break;
		default:
			break;
		}
	}

	GameObject::Render(hdc);
}

void DoorEditing::OnDebug(HDC hdc)
{
#ifdef _DEBUG
	#pragma region SampleChangeDoorState
	// ����) Ű�Է��� ���� �� �ش� ���� ���� OPENED ���·� ��ȭ
	if (Input::GetButtonDown('O'))
	{
		for (int i = 0; i < 4; ++i)
		{
			if (door[currRow][currColumn][i].img != nullptr)
			{
				door[currRow][currColumn][i].doorState = DoorStates::OPENED;
			}
		}
	}
	if (Input::GetButtonDown('C'))
	{
		door[currRow][currColumn][UPPER_DOOR].doorState = DoorStates::CLOSED;
		door[currRow][currColumn][LOWER_DOOR].doorState = DoorStates::CLOSED;
		door[currRow][currColumn][LEFT_DOOR].doorState = DoorStates::CLOSED;
		door[currRow][currColumn][RIGHT_DOOR].doorState = DoorStates::CLOSED;
	}
	#pragma endregion
	#pragma region SampleChangeMap
	// ����) ��,��,��,�� Ű�� �Է��ؼ� ���� �ٲ�.(���� �˾Ƽ� ���������)
	if (Input::GetButtonDown(VK_UP))
	{
		int nextUpRow = currRow - 1;
		if (nextUpRow >= OUT_OF_STAGE && roomInfo[nextUpRow][currColumn] != RoomTypes::NONE)
		{
			--currRow;
		}
		if (currRow < OUT_OF_STAGE)
		{
			currRow = OUT_OF_STAGE;
		}
	}
	if (Input::GetButtonDown(VK_DOWN))
	{
		int nextDownRow = currRow + 1;
		if (nextDownRow < stageSize && roomInfo[nextDownRow][currColumn] != RoomTypes::NONE)
		{
			++currRow;
		}
		if (currRow >= stageSize)
		{
			currRow = stageSize - 1;
		}
	}
	if (Input::GetButtonDown(VK_LEFT))
	{
		int nextLeftColumn = currColumn - 1;
		if (nextLeftColumn >= OUT_OF_STAGE && roomInfo[currRow][nextLeftColumn] != RoomTypes::NONE)
		{
			--currColumn;
		}
		if (currColumn < OUT_OF_STAGE)
		{
			currColumn = OUT_OF_STAGE;
		}
	}
	if (Input::GetButtonDown(VK_RIGHT))
	{
		int nextRightColumn = currColumn + 1;
		if (nextRightColumn < stageSize && roomInfo[currRow][nextRightColumn] != RoomTypes::NONE)
		{
			++currColumn;
		}
		if (currColumn >= stageSize)
		{
			currColumn = stageSize - 1;
		}
	}
	#pragma endregion
#endif
	if (debugMode)
	{
		Rectangle(hdc, door[currRow][currColumn][UPPER_DOOR].shape.left, door[currRow][currColumn][UPPER_DOOR].shape.top, door[currRow][currColumn][UPPER_DOOR].shape.right, door[currRow][currColumn][UPPER_DOOR].shape.bottom);
		Rectangle(hdc, door[currRow][currColumn][LOWER_DOOR].shape.left, door[currRow][currColumn][LOWER_DOOR].shape.top, door[currRow][currColumn][LOWER_DOOR].shape.right, door[currRow][currColumn][LOWER_DOOR].shape.bottom);
		Rectangle(hdc, door[currRow][currColumn][LEFT_DOOR].shape.left, door[currRow][currColumn][LEFT_DOOR].shape.top, door[currRow][currColumn][LEFT_DOOR].shape.right, door[currRow][currColumn][LEFT_DOOR].shape.bottom);
		Rectangle(hdc, door[currRow][currColumn][RIGHT_DOOR].shape.left, door[currRow][currColumn][RIGHT_DOOR].shape.top, door[currRow][currColumn][RIGHT_DOOR].shape.right, door[currRow][currColumn][RIGHT_DOOR].shape.bottom);
	}
}

void DoorEditing::ApplyDoorInfo(int nextRow, int nextColumn, int row, int column, int direction)
{
	switch (roomInfo[nextRow][nextColumn])
	{
	case RoomTypes::BOSS:
		door[row][column][direction].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
		door[row][column][direction].roomType = RoomTypes::BOSS;
		break;
	case RoomTypes::CURSE:
		door[row][column][direction].doorState = DoorStates::OPENED;
		door[row][column][direction].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
		door[row][column][direction].roomType = RoomTypes::CURSE;
		break;
	case RoomTypes::ITEM:
		door[row][column][direction].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
		door[row][column][direction].roomType = RoomTypes::ITEM;
		break;
	case RoomTypes::NORMAL:
		door[row][column][direction].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
		door[row][column][direction].roomType = RoomTypes::NORMAL;
		break;
	case RoomTypes::PRIVATE:
		door[row][column][direction].doorState = DoorStates::CLOSED;
		door[row][column][direction].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
		door[row][column][direction].roomType = RoomTypes::PRIVATE;
		break;
	case RoomTypes::SATAN:
		door[row][column][direction].doorState = DoorStates::OPENED;
		door[row][column][direction].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
		door[row][column][direction].roomType = RoomTypes::SATAN;
		break;
	case RoomTypes::START:
		door[row][column][direction].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Normal_Room_Door.bmp");
		door[row][column][direction].roomType = RoomTypes::START;
		break;
	default:
		break;
	}
}

void DoorEditing::ChangeImageDoorState()
{
	// DoorState ���� ���� �̹��� ��ȭ
	for (int i = 0; i < 4; ++i)
	{
		if (door[currRow][currColumn][i].img != nullptr)
		{
			if (door[currRow][currColumn][i].doorState == DoorStates::OPENED)
			{
				door[currRow][currColumn][i].img->SetCurrFrameY(OPENED_STATE_DOOR);
			}
			if (door[currRow][currColumn][i].img->GetMaxFrameY() >= CLOSED_STATE_DOOR && door[currRow][currColumn][i].doorState == DoorStates::CLOSED)
			{
				door[currRow][currColumn][i].img->SetCurrFrameY(CLOSED_STATE_DOOR);
			}
			if (door[currRow][currColumn][i].img->GetMaxFrameY() >= LOCKED_STATE_DOOR && door[currRow][currColumn][i].doorState == DoorStates::LOCKED)
			{
				door[currRow][currColumn][i].img->SetCurrFrameY(LOCKED_STATE_DOOR);
			}
		}
	}
}

void DoorEditing::ChangeShapeOpenDoor()
{
	// DoorStates::OPENED �̰�, �̹����� �ִٸ� shape�� �۰� �����.
	// ��
	if (door[currRow][currColumn][UPPER_DOOR].doorState == DoorStates::OPENED && door[currRow][currColumn][UPPER_DOOR].img != nullptr)
	{
		objectSize = 10.0f;
		door[currRow][currColumn][UPPER_DOOR].shape = {
			(LONG)(door[currRow][currColumn][UPPER_DOOR].pos.x - (objectSize * DEVIDE_HALF)),							// shape.left
			(LONG)(door[currRow][currColumn][UPPER_DOOR].pos.y - (objectSize * DEVIDE_HALF)),							// shape.top
			(LONG)(door[currRow][currColumn][UPPER_DOOR].pos.x + (objectSize * DEVIDE_HALF)),							// shape.right
			(LONG)(door[currRow][currColumn][UPPER_DOOR].pos.y + (objectSize * DEVIDE_HALF))							// shape.bottom
		};
	}
	// ��
	if (door[currRow][currColumn][LOWER_DOOR].doorState == DoorStates::OPENED && door[currRow][currColumn][LOWER_DOOR].img != nullptr)
	{
		objectSize = 10.0f;
		door[currRow][currColumn][LOWER_DOOR].shape = {
			(LONG)(door[currRow][currColumn][LOWER_DOOR].pos.x - (objectSize * DEVIDE_HALF)),							// shape.left
			(LONG)(door[currRow][currColumn][LOWER_DOOR].pos.y - (objectSize * DEVIDE_HALF)),							// shape.top
			(LONG)(door[currRow][currColumn][LOWER_DOOR].pos.x + (objectSize * DEVIDE_HALF)),							// shape.right
			(LONG)(door[currRow][currColumn][LOWER_DOOR].pos.y + (objectSize * DEVIDE_HALF))							// shape.bottom
		};
	}
	// ��
	if (door[currRow][currColumn][LEFT_DOOR].doorState == DoorStates::OPENED && door[currRow][currColumn][LEFT_DOOR].img != nullptr)
	{
		objectSize = 10.0f;
		door[currRow][currColumn][LEFT_DOOR].shape = {
			(LONG)(door[currRow][currColumn][LEFT_DOOR].pos.x - (objectSize * DEVIDE_HALF)),							// shape.left
			(LONG)(door[currRow][currColumn][LEFT_DOOR].pos.y - (objectSize * DEVIDE_HALF) - ADJUST_SIZE_15),			// shape.top
			(LONG)(door[currRow][currColumn][LEFT_DOOR].pos.x + (objectSize * DEVIDE_HALF)),							// shape.right
			(LONG)(door[currRow][currColumn][LEFT_DOOR].pos.y + (objectSize * DEVIDE_HALF) + ADJUST_SIZE_15)			// shape.bottom
		};
	}
	// ��
	if (door[currRow][currColumn][RIGHT_DOOR].doorState == DoorStates::OPENED && door[currRow][currColumn][RIGHT_DOOR].img != nullptr)
	{
		objectSize = 10.0f;
		door[currRow][currColumn][RIGHT_DOOR].shape = {
			(LONG)(door[currRow][currColumn][RIGHT_DOOR].pos.x - (objectSize * DEVIDE_HALF)),							// shape.left
			(LONG)(door[currRow][currColumn][RIGHT_DOOR].pos.y - (objectSize * DEVIDE_HALF) - ADJUST_SIZE_15),		// shape.top
			(LONG)(door[currRow][currColumn][RIGHT_DOOR].pos.x + (objectSize * DEVIDE_HALF)),							// shape.right
			(LONG)(door[currRow][currColumn][RIGHT_DOOR].pos.y + (objectSize * DEVIDE_HALF) + ADJUST_SIZE_15)			// shape.bottom
		};
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
					door[i][j][UPPER_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
					door[i][j][UPPER_DOOR].roomType = RoomTypes::BOSS;
				}
				if (bottomRow < stageSize && roomInfo[bottomRow][j] != RoomTypes::NONE)
				{
					door[i][j][LOWER_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
					door[i][j][LOWER_DOOR].roomType = RoomTypes::BOSS;
				}
				if (leftColumn >= OUT_OF_STAGE && roomInfo[i][leftColumn] != RoomTypes::NONE)
				{
					door[i][j][LEFT_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
					door[i][j][LEFT_DOOR].roomType = RoomTypes::BOSS;

				}
				if (rightColumn < stageSize && roomInfo[i][rightColumn] != RoomTypes::NONE)
				{
					door[i][j][RIGHT_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Boss_Room_Door.bmp");
					door[i][j][RIGHT_DOOR].roomType = RoomTypes::BOSS;
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
					door[i][j][UPPER_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
					door[i][j][UPPER_DOOR].doorState = DoorStates::OPENED;
					door[i][j][UPPER_DOOR].roomType = RoomTypes::CURSE;
				}
				if (bottomRow < stageSize && roomInfo[bottomRow][j] != RoomTypes::NONE)
				{
					door[i][j][LOWER_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
					door[i][j][LOWER_DOOR].doorState = DoorStates::OPENED;
					door[i][j][LOWER_DOOR].roomType = RoomTypes::CURSE;
				}
				if (leftColumn >= OUT_OF_STAGE && roomInfo[i][leftColumn] != RoomTypes::NONE)
				{
					door[i][j][LEFT_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
					door[i][j][LEFT_DOOR].doorState = DoorStates::OPENED;
					door[i][j][LEFT_DOOR].roomType = RoomTypes::CURSE;
				}
				if (rightColumn < stageSize && roomInfo[i][rightColumn] != RoomTypes::NONE)
				{
					door[i][j][RIGHT_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp");
					door[i][j][RIGHT_DOOR].doorState = DoorStates::OPENED;
					door[i][j][RIGHT_DOOR].roomType = RoomTypes::CURSE;
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
					door[i][j][UPPER_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
					door[i][j][UPPER_DOOR].doorState = DoorStates::OPENED;
					door[i][j][UPPER_DOOR].roomType = RoomTypes::ITEM;
				}
				if (bottomRow < stageSize && roomInfo[bottomRow][j] != RoomTypes::NONE)
				{
					door[i][j][LOWER_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
					door[i][j][LOWER_DOOR].doorState = DoorStates::OPENED;
					door[i][j][LOWER_DOOR].roomType = RoomTypes::ITEM;
				}
				if (leftColumn >= OUT_OF_STAGE && roomInfo[i][leftColumn] != RoomTypes::NONE)
				{
					door[i][j][LEFT_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
					door[i][j][LEFT_DOOR].doorState = DoorStates::OPENED;
					door[i][j][LEFT_DOOR].roomType = RoomTypes::ITEM;
				}
				if (rightColumn < stageSize && roomInfo[i][rightColumn] != RoomTypes::NONE)
				{
					door[i][j][RIGHT_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Item_Room_Door.bmp");
					door[i][j][RIGHT_DOOR].doorState = DoorStates::OPENED;
					door[i][j][RIGHT_DOOR].roomType = RoomTypes::ITEM;
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
					door[i][j][UPPER_DOOR].doorState = DoorStates::OPENED;
				}
				if (bottomRow < stageSize && roomInfo[bottomRow][j] != RoomTypes::NONE)
				{
					door[i][j][LOWER_DOOR].doorState = DoorStates::OPENED;
				}
				if (leftColumn >= OUT_OF_STAGE && roomInfo[i][leftColumn] != RoomTypes::NONE)
				{
					door[i][j][LEFT_DOOR].doorState = DoorStates::OPENED;
				}
				if (rightColumn < stageSize && roomInfo[i][rightColumn] != RoomTypes::NONE)
				{
					door[i][j][RIGHT_DOOR].doorState = DoorStates::OPENED;
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
					door[i][j][UPPER_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
					door[i][j][UPPER_DOOR].doorState = DoorStates::OPENED;
					door[i][j][UPPER_DOOR].roomType = RoomTypes::SATAN;
				}
				if (bottomRow < stageSize && roomInfo[bottomRow][j] != RoomTypes::NONE)
				{
					door[i][j][LOWER_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
					door[i][j][LOWER_DOOR].doorState = DoorStates::OPENED;
					door[i][j][LOWER_DOOR].roomType = RoomTypes::SATAN;
				}
				if (leftColumn >= OUT_OF_STAGE && roomInfo[i][leftColumn] != RoomTypes::NONE)
				{
					door[i][j][LEFT_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
					door[i][j][LEFT_DOOR].doorState = DoorStates::OPENED;
					door[i][j][LEFT_DOOR].roomType = RoomTypes::SATAN;
				}
				if (rightColumn < stageSize && roomInfo[i][rightColumn] != RoomTypes::NONE)
				{
					door[i][j][RIGHT_DOOR].img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Satan_Room_Door.bmp");
					door[i][j][RIGHT_DOOR].doorState = DoorStates::OPENED;
					door[i][j][RIGHT_DOOR].roomType = RoomTypes::SATAN;
				}
			}
		}
	}
}

void DoorEditing::FixStartDoor()
{
	int topRow = (INT)(currRow - 1);
	int bottomRow = (INT)(currRow + 1);
	int leftColumn = (INT)(currColumn - 1);
	int rightColumn = (INT)(currColumn + 1);
	// ���� ���� �ִ��� Ȯ���Ͽ� ���� ����
	if (topRow >= OUT_OF_STAGE && roomInfo[topRow][currColumn] != RoomTypes::NONE)
	{
		door[currRow][currColumn][UPPER_DOOR].doorState = DoorStates::OPENED;
	}
	if (bottomRow < stageSize && roomInfo[bottomRow][currColumn] != RoomTypes::NONE)
	{
		door[currRow][currColumn][LOWER_DOOR].doorState = DoorStates::OPENED;
	}
	if (leftColumn >= OUT_OF_STAGE && roomInfo[currRow][leftColumn] != RoomTypes::NONE)
	{
		door[currRow][currColumn][LEFT_DOOR].doorState = DoorStates::OPENED;
	}
	if (rightColumn < stageSize && roomInfo[currRow][rightColumn] != RoomTypes::NONE)
	{
		door[currRow][currColumn][RIGHT_DOOR].doorState = DoorStates::OPENED;
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
			door[i][j][UPPER_DOOR].img = nullptr;
			door[i][j][UPPER_DOOR].doorState = DoorStates::CLOSED;										// Door�� ����
			door[i][j][UPPER_DOOR].doorDir = ObjectDir::UP;												// Door�� ����
			door[i][j][UPPER_DOOR].roomType = RoomTypes::NONE;											// Door�� ����

			door[i][j][UPPER_DOOR].pos.x = 640.0f;														// terrain frameX 16
			door[i][j][UPPER_DOOR].pos.y = 80.0f;														// terrain frameY 2
			door[i][j][UPPER_DOOR].shape = {
				(LONG)(door[i][j][UPPER_DOOR].pos.x - (objectSize * DEVIDE_HALF)),						// shape.left
				(LONG)(door[i][j][UPPER_DOOR].pos.y - (objectSize * DEVIDE_HALF) - ADJUST_SIZE_40),		// shape.top
				(LONG)(door[i][j][UPPER_DOOR].pos.x + (objectSize * DEVIDE_HALF)),						// shape.right
				(LONG)(door[i][j][UPPER_DOOR].pos.y + (objectSize * DEVIDE_HALF))						// shape.bottom
			};
			//DOWN
			door[i][j][LOWER_DOOR].img = nullptr;
			door[i][j][LOWER_DOOR].doorState = DoorStates::CLOSED;										// Door�� ����
			door[i][j][LOWER_DOOR].doorDir = ObjectDir::DOWN;											// Door�� ����
			door[i][j][LOWER_DOOR].roomType = RoomTypes::NONE;											// Door�� ����

			door[i][j][LOWER_DOOR].pos.x = 640.0f;														// terrain frameX 16
			door[i][j][LOWER_DOOR].pos.y = 720.0f;														// terrain frameY 18
			door[i][j][LOWER_DOOR].shape = {
				(LONG)(door[i][j][LOWER_DOOR].pos.x - (objectSize * DEVIDE_HALF)),						// shape.left
				(LONG)(door[i][j][LOWER_DOOR].pos.y - (objectSize * DEVIDE_HALF)),						// shape.top
				(LONG)(door[i][j][LOWER_DOOR].pos.x + (objectSize * DEVIDE_HALF)),						// shape.right
				(LONG)(door[i][j][LOWER_DOOR].pos.y + (objectSize * DEVIDE_HALF) + ADJUST_SIZE_40)		// shape.bottom
			};
			//LEFT
			door[i][j][LEFT_DOOR].img = nullptr;
			door[i][j][LEFT_DOOR].doorState = DoorStates::CLOSED;										// Door�� ����
			door[i][j][LEFT_DOOR].doorDir = ObjectDir::LEFT;											// Door�� ����
			door[i][j][LEFT_DOOR].roomType = RoomTypes::NONE;											// Door�� ����

			door[i][j][LEFT_DOOR].pos.x = 80.0f;														// terrain frameX 2
			door[i][j][LEFT_DOOR].pos.y = 400.0f;														// terrain frameY 10
			door[i][j][LEFT_DOOR].shape = {
				(LONG)(door[i][j][LEFT_DOOR].pos.x - (objectSize * DEVIDE_HALF)),						// shape.left
				(LONG)(door[i][j][LEFT_DOOR].pos.y - (objectSize * DEVIDE_HALF)),						// shape.top
				(LONG)(door[i][j][LEFT_DOOR].pos.x + (objectSize * DEVIDE_HALF) - ADJUST_SIZE_14),		// shape.right
				(LONG)(door[i][j][LEFT_DOOR].pos.y + (objectSize * DEVIDE_HALF))						// shape.bottom
			};
			//RIGHT
			door[i][j][RIGHT_DOOR].img = nullptr;
			door[i][j][RIGHT_DOOR].doorState = DoorStates::CLOSED;										// Door�� ����
			door[i][j][RIGHT_DOOR].doorDir = ObjectDir::RIGHT;											// Door�� ����
			door[i][j][RIGHT_DOOR].roomType = RoomTypes::NONE;											// Door�� ����

			door[i][j][RIGHT_DOOR].pos.x = 1200.0f;														// terrain frameX 29
			door[i][j][RIGHT_DOOR].pos.y = 400.0f;														// terrain frameY 10
			door[i][j][RIGHT_DOOR].shape = {
				(LONG)(door[i][j][RIGHT_DOOR].pos.x - (objectSize * DEVIDE_HALF) + ADJUST_SIZE_14),		// shape.left
				(LONG)(door[i][j][RIGHT_DOOR].pos.y - (objectSize * DEVIDE_HALF)),						// shape.top
				(LONG)(door[i][j][RIGHT_DOOR].pos.x + (objectSize * DEVIDE_HALF)),						// shape.right
				(LONG)(door[i][j][RIGHT_DOOR].pos.y + (objectSize * DEVIDE_HALF))						// shape.bottom
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
	currColumn = startPoint;
	currRow = startPoint;

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
						door[i][j][k].img->SetCurrFrameY(OPENED_STATE_DOOR);
					}
					if (door[i][j][k].img->GetMaxFrameY() >= CLOSED_STATE_DOOR && door[i][j][k].doorState == DoorStates::CLOSED)
					{
						door[i][j][k].img->SetCurrFrameY(CLOSED_STATE_DOOR);
					}
					if (door[i][j][k].img->GetMaxFrameY() >= LOCKED_STATE_DOOR && door[i][j][k].doorState == DoorStates::LOCKED)
					{
						door[i][j][k].img->SetCurrFrameY(LOCKED_STATE_DOOR);
					}
				}
			}
		}
	}
}

void DoorEditing::OpenTheDoor()
{
	if (normalMonster[0][currRow][currColumn].empty())
	{
		// ��
		if (door[currRow][currColumn][UPPER_DOOR].img != nullptr)
		{
			door[currRow][currColumn][UPPER_DOOR].doorState = DoorStates::OPENED;
		}
		// ��
		if (door[currRow][currColumn][LOWER_DOOR].img != nullptr)
		{
			door[currRow][currColumn][LOWER_DOOR].doorState = DoorStates::OPENED;
		}
		// ��
		if (door[currRow][currColumn][LEFT_DOOR].img != nullptr)
		{
			door[currRow][currColumn][LEFT_DOOR].doorState = DoorStates::OPENED;
		}
		// ��
		if (door[currRow][currColumn][RIGHT_DOOR].img != nullptr)
		{
			door[currRow][currColumn][RIGHT_DOOR].doorState = DoorStates::OPENED;
		}
	}
}

void DoorEditing::StoreRoomType(int row, int column)
{
	// ��, ��, ��, �� �� ������ �����ϱ� ���� ����
	int topRow = row - 1;
	int bottomRow = row + 1;
	int leftColumn = column - 1;
	int rightColumn = column + 1;

	// ���� �������� ��, ��, ��, �� �� RoomTypes�� �ν��Ͽ� Image ����, ���� �� �� Ư�� ����� ���� �׻� �����ְų� ����ִ�.
	// ��
	if (topRow >= OUT_OF_STAGE)
	{
		ApplyDoorInfo(topRow, column, row, column, UPPER_DOOR);
	}
	// ��
	if (bottomRow < stageSize)
	{
		ApplyDoorInfo(bottomRow, column, row, column, LOWER_DOOR);
	}
	// ��
	if (leftColumn >= OUT_OF_STAGE)
	{
		ApplyDoorInfo(row, leftColumn, row, column, LEFT_DOOR);
	}
	// ��
	if (rightColumn < stageSize)
	{
		ApplyDoorInfo(row, rightColumn, row, column, RIGHT_DOOR);
	}

	// �湮 Ȯ��
	isTransitMap[row][column] = true;

	// ���� ������ �̵�
	// ��
	if (topRow >= OUT_OF_STAGE && roomInfo[topRow][column] != RoomTypes::NONE && isTransitMap[topRow][column] == false)
	{
		StoreRoomType(topRow, column);
	}
	// ��
	if (bottomRow < stageSize && roomInfo[bottomRow][column] != RoomTypes::NONE && isTransitMap[bottomRow][column] == false)
	{
		StoreRoomType(bottomRow, column);
	}
	// ��
	if (leftColumn >= OUT_OF_STAGE && roomInfo[row][leftColumn] != RoomTypes::NONE && isTransitMap[row][leftColumn] == false)
	{
		StoreRoomType(row, leftColumn);
	}
	// ��
	if (rightColumn < stageSize && roomInfo[row][rightColumn] != RoomTypes::NONE && isTransitMap[row][rightColumn] == false)
	{
		StoreRoomType(row, rightColumn);
	}
}
