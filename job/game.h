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

#define Card_WIDTH 100    //�ƿ�75
#define Care_HEIGHT 120   //�Ƹ�107



//ö�ٶ�������״̬
typedef enum CARDSTATE
{
	ncBG,		    //����
	ncCARD,		    //��
};
typedef enum GAMEOVERSTATE
{
	ncNo,		//��Ϸδ����
	ncWIN,		//��Ϸʤ��
	ncLOSE,		//��Ϸʧ��
};
using namespace sf;			//SFML�е�ÿ���඼λ�ڸ������ռ�֮�£����趨sf�����ռ�Ļ�����Ӧ�ĺ���ǰ��Ҫ������������������� sf::VideoMode(width* GRIDSIZE, height* GRIDSIZE)

class Card
{
public:
	int mState;			//����״̬
	int mStateBackUp;	//��ԭʼ״̬����
	int card;           //�����ƺ�0~51
	bool isPress;		//���Ƿ񱻵��
	bool isMatch;       //�Ƿ��Ѿ����
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
	int mTime;  //��Ϸ��ʱ
	Card mGameData[LV_HEIGHT][LV_WIDTH];		//����ȡ����Ѷȵ���̨�ߴ�
	bool isGameBegin;		//��Ϸ�Ƿ�ʼ
	int isGameOverState;	//��Ϸ������״̬
	sf::Vector2i mCornPoint ,DrawPoint;	//��̨���󶥵�����,�Ƶ��󶥵�
	int cardSize;	//�ƵĴ�С
	int imgButNo, imgCdBgNo, imgBGNo, imgGONo;

	Texture tBackground, tCdBackground, tTiles, tButtons, tNum, tTimer, tCounter, tGameOver, tCard[52];		//	�����������
	Sprite  sBackground, sCdBackground, sTiles, sButtons, sNum, sTimer, sCounter, sGameOver, sCard[52];		//	�����������
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
	void Match();  //���
	void CardSet();//����
	void SetZero();//�ó�δ����״̬

	void Input();
	void LButtonDown(Vector2i mPoint);		//������

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
