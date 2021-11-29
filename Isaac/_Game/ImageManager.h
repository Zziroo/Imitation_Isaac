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

	//사용할 이미지를 등록하는 기능
	void AddImage(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = NULL);
	void AddImage(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = NULL);

	Image* FindImage(const char* fileName);		//등록된 이미지 중에 필요한 이미지를 찾는 기능
	void DeleteImage(const char* fileName);		//사용이 종료된 이미지를 등록 해제하는 기능

	virtual ~ImageManager() = default;
};

