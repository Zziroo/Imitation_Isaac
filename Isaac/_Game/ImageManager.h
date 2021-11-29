#pragma once

class Image;
class ImageManager : public Singleton<ImageManager>
{
private:
	map<string, Image*>	mapImages;
	map<string, Image*>::iterator it;
	Image* img = nullptr;

protected:

public:
	void Init();
	void Release();

	//����� �̹����� ����ϴ� ���
	void AddImage(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = NULL);
	void AddImage(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = NULL);

	Image* FindImage(const char* fileName);		//��ϵ� �̹��� �߿� �ʿ��� �̹����� ã�� ���
	void DeleteImage(const char* fileName);		//����� ����� �̹����� ��� �����ϴ� ���

	virtual ~ImageManager() = default;
};

