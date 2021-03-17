#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <sstream>
#define GRIDSIZE 25
#define LV_WIDTH 10
#define LV_HEIGHT 6
#define LV_NUM 60

#define Card_WIDTH 100    //牌宽75
#define Care_HEIGHT 120   //牌高107



//枚举定义网格状态
typedef enum CARDSTATE
{
	ncBG,		    //背景
	ncCARD,		    //卡
};
typedef enum GAMEOVERSTATE
{
	ncNo,		//游戏未结束
	ncWIN,		//游戏胜利
	ncLOSE,		//游戏失败
};
using namespace sf;			//SFML中的每个类都位于该命名空间之下，不设定sf命名空间的话，相应的函数前需要用作用域解析符，例如 sf::VideoMode(width* GRIDSIZE, height* GRIDSIZE)

class Card
{
public:
	int mState;			//卡的状态
	int mStateBackUp;	//卡原始状态备份
	int card;           //卡的牌号0~51
	bool isPress;		//卡是否被点击
	bool isMatch;       //是否已经配对
	Card() {
		mState = ncBG;
		card = 53;
		isPress = false;
		isMatch = false;
	}
	~Card() {

	}
};
class Game
{
public:
	sf::RenderWindow window;
	Game();
	~Game();
	bool gameOver, gameQuit;
	int Window_width, Window_height, stageWidth, stageHeight, mMineNum, mFlagCalc, PressNum;
	int mTime;  //游戏计时
	Card mGameData[LV_HEIGHT][LV_WIDTH];		//数组取最高难度的舞台尺寸
	bool isGameBegin;		//游戏是否开始
	int isGameOverState;	//游戏结束的状态
	sf::Vector2i mCornPoint ,DrawPoint;	//舞台的左顶点坐标,牌的左顶点
	int cardSize;	//牌的大小
	int imgButNo, imgCdBgNo, imgBGNo, imgGONo;

	Texture tBackground, tCdBackground, tTiles, tButtons, tNum, tTimer, tCounter, tGameOver, tCard[52];		//	创建纹理对象
	Sprite  sBackground, sCdBackground, sTiles, sButtons, sNum, sTimer, sCounter, sGameOver, sCard[52];		//	创建精灵对象
	sf::IntRect  ButtonRectRestart, ButtonRectBG, ButtonRectSkin, ButtonTips, ButtonRectQuit;

	SoundBuffer sbWin, sbBoom;
	Sound soundWin, soundBoom;
	Music bkMusic;

	// A Clock starts counting as soon as it's created
	sf::Clock gameClock, mouseClickTimer;

	void Run();

	void Initial();
	void IniData();
	void LoadMediaData();
	void Match();  //配对
	void CardSet();//放牌
	void SetZero();//置成未翻开状态

	void Input();
	void LButtonDown(Vector2i mPoint);		//鼠标左击

	void Logic();
	void isWin();

	void Draw();
	void DrawCard();
	void DrawButton();
	void DrawScore();
	void DrawTimer();
	void DrawGameEnd();

};

#pragma once
