#pragma once

class KeyManager : public Singleton<KeyManager>
{
private:
	bitset<KEY_MAX_COUNT>	keyUp;		//Ű�� �� ���� �������� �ƴ���
	bitset<KEY_MAX_COUNT>	keyDown;	//Ű�� ���� �������� �ƴ���

protected:

public:
	void Init();
	void Release();

	bool IsOnceKeyDown(int key);		//Ű�� ù��°�� ���ȴ��� �Ǵ�
	bool IsOnceKeyDown(char key);		//Ű�� ù��°�� ���ȴ��� �Ǵ�
	bool IsOnceKeyUp(int key);			//Ű�� ù��°�� ���ȴٰ� ���������� �Ǵ�
	bool IsOnceKeyUp(char key);			//Ű�� ù��°�� ���ȴٰ� ���������� �Ǵ�
	bool IsStayKeyDown(int key);		//Ű�� ������ �ִ��� �Ǵ�
	bool IsStayKeyDown(char key);		//Ű�� ������ �ִ��� �Ǵ�

	virtual ~KeyManager() = default;
};

