#pragma once

#include "GameObject.h"

enum class ButtonStates { NONE, UP, DOWN };

class Image;
class Button : public GameObject
{
private:
	struct ButtonInfo
	{
		Image*			image = nullptr;
		POINTFLOAT		pos = {};
		RECT			shape = {};
		ButtonStates	buttonState = ButtonStates::NONE;
		bool			clicked = false;
	};

private:
	ButtonInfo			closeBtn = {};					// Close
	ButtonInfo			enemyBtn = {};					// Enemy
	ButtonInfo			loadBtn = {};					// Load
	ButtonInfo			nextBtn = {};					// Next
	ButtonInfo			obstacleBtn = {};				// Object
	ButtonInfo			prevBtn = {};					// Prev
	ButtonInfo			saveBtn = {};					// Save
	ButtonInfo			sampleTileBtn = {};				// SampleTile

	ButtonInfo			basementTileBtn = {};			// Tile/BASEMENT
	ButtonInfo			caveTileBtn = {};				// Tile/CAVE
	ButtonInfo			cellarTileBtn = {};				// Tile/CELLAR
	ButtonInfo			depthTileBtn = {};				// Tile/DEPTH
	ButtonInfo			exitBtn = {};					// Tile/Exit

	ButtonInfo			curseRoomObstacleBtn = {};		// Obstacle/Curse
	ButtonInfo			itemRoomObstacleBtn = {};		// Obstacle/Item
	ButtonInfo			normalRoomObstacleBtn = {};		// Obstacle/Normal

	Image*				letter_Basement = nullptr;		// Basement
	Image*				letter_Cave = nullptr;			// Cave
	Image*				letter_Cellar = nullptr;		// Cellar
	Image*				letter_Curse = nullptr;			// Curse
	Image*				letter_Depth = nullptr;			// Depth
	Image*				letter_Enemy = nullptr;			// Enemy
	Image*				letter_Exit = nullptr;			// Exit
	Image*				letter_Item = nullptr;			// Item
	Image*				letter_Normal = nullptr;		// Normal
	Image*				letter_Obstacle = nullptr;		// Object
	Image*				letter_Shop = nullptr;			// Shop
	Image*				letter_Tile = nullptr;			// Tile

	int					tileIndex = 0;
	char				text[64] = {};					// Debuging

public:
	virtual void		Init() override;
	virtual void		Release() override;
	virtual void		Update() override;
	virtual void		Render(HDC hdc) override;
	virtual void		OnDebug(HDC hdc) override;

	void				DeclareButtonInfo(ButtonInfo* btnInfo, int width, int height);
	void				ClikedButton(HDC hdc, ButtonInfo* btnInfo);
	void				RenderDownButton(HDC hdc, ButtonInfo* btnInfo);
	void				RenderNormalButton(HDC hdc, ButtonInfo* btnInfo);
	void				RenderUpButton(HDC hdc, ButtonInfo* btnInfo);
	void				ShowLetter(HDC hdc, Image* img, ButtonInfo* btnInfo);

	inline bool			GetPressLoadButton() { return this->loadBtn.clicked; }
	inline bool			GetPressNextButton() { return this->nextBtn.clicked; }
	inline bool			GetPressPrevButton() { return this->prevBtn.clicked; }
	inline bool			GetPressSaveButton() { return this->saveBtn.clicked; }
	inline bool			GetSelectBasementTileButton() { return this->basementTileBtn.clicked; }
	inline bool			GetSelectCaveTileButton() { return this->caveTileBtn.clicked; }
	inline bool			GetSelectCellarTileButton() { return this->cellarTileBtn.clicked; }
	inline bool			GetSelectCurseRoomButton() { return this->curseRoomObstacleBtn.clicked; }
	inline bool			GetSelectDepthTileButton() { return this->depthTileBtn.clicked; }
	inline bool			GetSelectItemRoomButton() { return this->itemRoomObstacleBtn.clicked; }
	inline bool			GetSelectNormalRoomButton() { return this->normalRoomObstacleBtn.clicked; }
	inline bool			GetSelectObstacleButton() { return this->obstacleBtn.clicked; }
	inline bool			GetSelectSampleTileButton() { return this->sampleTileBtn.clicked; }
	inline int			GetTileIndex() { return this->tileIndex; }

	inline void			SetObstacleButton(bool clicked) { this->obstacleBtn.clicked = clicked; }
	inline void			SetPressLoadButton(bool clicked) { this->loadBtn.clicked = clicked; }
	inline void			SetPressNextButton(bool clicked) { this->nextBtn.clicked = clicked; }
	inline void			SetPressPrevButton(bool clicked) { this->prevBtn.clicked = clicked; }
	inline void			SetPressSaveButton(bool clicked) { this->saveBtn.clicked = clicked; }
	inline void			SetSelecteBasementTile(bool clicked) { this->basementTileBtn.clicked = clicked; }
	inline void			SetTileIndex(int tileIndex) { this->tileIndex = tileIndex; }

	virtual ~Button() = default;
};
