#include "stdafx.h"
#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = ImageLoadType::Empty;
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hMemDc = CreateCompatibleDC(hdc);

	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

	ReleaseDC(_hWnd, hdc);

	if (imageInfo->hBitmap == NULL) 
	{
		Release();
		return E_FAIL;
	}
	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	HDC hdc = GetDC(_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = ImageLoadType::File;
	imageInfo->hBitmap = (HBITMAP)LoadImage(_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hMemDc = CreateCompatibleDC(hdc);

	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

	ReleaseDC(_hWnd, hdc);

	this->isTransparent = isTrans;
	this->transColor = transColor;

	if (imageInfo->hBitmap == NULL) 
	{
		Release();
		return E_FAIL;
	}
	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	HDC hdc = GetDC(_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = ImageLoadType::File;
	imageInfo->hBitmap = (HBITMAP)LoadImage(_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hMemDc = CreateCompatibleDC(hdc);

	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

	ReleaseDC(_hWnd, hdc);

	this->isTransparent = isTrans;
	this->transColor = transColor;

	imageInfo->maxFrameX = maxFrameX;
	imageInfo->maxFrameY = maxFrameY;
	imageInfo->currFrameX = 0;
	imageInfo->currFrameY = 0;
	imageInfo->frameWidth = width / maxFrameX;
	imageInfo->frameHeight = height / maxFrameY;

	if (imageInfo->hBitmap == NULL) 
	{
		Release();
		return E_FAIL;
	}
	return S_OK;
}

void Image::Release()
{
	if (imageInfo) 
	{
		SelectObject(imageInfo->hMemDc, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDc);

		delete imageInfo;
		imageInfo = nullptr;
	}
}

void Image::Render(HDC hdc)
{
	BitBlt(
		hdc,
		0,
		0,
		imageInfo->width,
		imageInfo->height,
		imageInfo->hMemDc,
		0,
		0,
		SRCCOPY);
}

void Image::Render(HDC hdc, int destX, int destY)
{
	if (isTransparent) 
	{
		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,

			imageInfo->hMemDc,
			0, 0,
			imageInfo->width, imageInfo->height,
			transColor);
	}
	else 
	{
		BitBlt(
			hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDc,
			0,
			0,
			SRCCOPY);
	}
}

void Image::Render(HDC hdc, int destX, int destY, int frameX, int frameY)
{
	if (isTransparent)
	{
		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->frameWidth / 2),
			destY - (imageInfo->frameHeight / 2),
			(INT)(imageInfo->frameWidth),
			(INT)(imageInfo->frameHeight),

			imageInfo->hMemDc,
			imageInfo->frameWidth * frameX,
			imageInfo->frameHeight * frameY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			transColor);
	}
	else
	{
		BitBlt(
			hdc,
			destX - (imageInfo->frameWidth / 2),
			destY - (imageInfo->frameHeight / 2),
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDc,
			imageInfo->frameWidth * frameX,
			imageInfo->frameHeight * frameY,
			SRCCOPY);
	}
}

void Image::EnlargeSampleTile(HDC hdc, int destX, int destY, int frameX, int frameY, float scale)
{
	if (isTransparent)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			(INT)(imageInfo->frameWidth * scale),
			(INT)(imageInfo->frameHeight * scale),

			imageInfo->hMemDc,
			imageInfo->frameWidth * frameX,
			imageInfo->frameHeight * frameY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			transColor);
	}
	else
	{
		StretchBlt(
			hdc,
			destX,
			destY,
			(INT)(imageInfo->frameWidth * scale),
			(INT)(imageInfo->frameHeight * scale),

			imageInfo->hMemDc,
			imageInfo->frameWidth* frameX,
			imageInfo->frameHeight* frameY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::TransparentRender(HDC hdc, int destX, int destY, int frameX, int frameY, float transparency)
{
	BLENDFUNCTION _bf;
	_bf.BlendOp = 0;
	_bf.BlendFlags = 0;
	_bf.SourceConstantAlpha = (BYTE)transparency;
	_bf.AlphaFormat = 0;

	if (isTransparent)
	{
		GdiAlphaBlend(
			hdc,
			destX - (imageInfo->frameWidth / 2),
			destY - (imageInfo->frameHeight / 2),
			(INT)(imageInfo->frameWidth),
			(INT)(imageInfo->frameHeight),

			imageInfo->hMemDc,
			imageInfo->frameWidth * frameX,
			imageInfo->frameHeight * frameY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			_bf);
	}
	else
	{
		BitBlt(
			hdc,
			destX - (imageInfo->frameWidth / 2),
			destY - (imageInfo->frameHeight / 2),
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDc,
			imageInfo->frameWidth * frameX,
			imageInfo->frameHeight * frameY,
			SRCCOPY);
	}
}
