#include "Game.h"
#include <stdlib.h>



Game::Game()
{
	Window_width = 1050;
	Window_height = 960;
	imgButNo = 1;
	imgCdBgNo = 1;
	imgBGNo = 1;
	imgGONo = 1;
	window.create(sf::VideoMode(Window_width, Window_height), L"������Ϸ");
}


Game::~Game()
{
}

void Game::Initial()
{
	window.setFramerateLimit(10); //ÿ������Ŀ��֡��
	cardSize = GRIDSIZE; //�����λ�õĿ�Ĵ�С


	stageWidth = LV_WIDTH;//��̨��ȣ�������
	stageHeight = LV_HEIGHT;//��̨�߶ȣ�������
	//mMineNum = LV_NUM;

	gameOver = false;
	gameQuit = false;
	isGameOverState = ncNo;	//��ʼ����Ϸ�Ľ���״̬
	isGameBegin = false;	//��ʼ����Ϸ�Ƿ�ʼ
	mTime = 0;				//��ʼ����Ϸ���е�ʱ��

	mCornPoint.x = (Window_width - stageWidth * Card_WIDTH) / 2;		//������̨�����Ͻ�����
	mCornPoint.y = (Window_height - stageHeight * Care_HEIGHT) / 2;
	IniData();		//��ʼ������
	LoadMediaData();	//�����ز�
}
void Game::IniData()
{
	for (int j = 0; j < stageHeight; j++) {
		for (int i = 0; i < stageWidth; i++) {
			mGameData[j][i].isPress = false;
			mGameData[j][i].isMatch = false;
			mGameData[j][i].mState = ncBG;
			mGameData[j][i].card = 53;
		}
	}

	PressNum = 0;
}
void Game::LoadMediaData()
{
	std::stringstream ss;
	//�Ƶ�ͼƬ
	ss << "data/images/cdbg" << imgCdBgNo << ".jpg";
	if (!tCdBackground.loadFromFile(ss.str()))
	{
		std::cout << "Card Background image û���ҵ�" << std::endl;
	}
	ss.str("");

	ss << "data/images/BG" << imgBGNo << ".jpg";
	if (!tBackground.loadFromFile(ss.str()))
	{
		std::cout << "Background image û���ҵ�" << std::endl;
	}
	ss.str("");
	
	for (int i = 0; i < 52; i++) {
		ss << "data/images/pukeimage/" << i + 1 << ".jpg";
		if (!tCard[i].loadFromFile(ss.str()))
		{
			std::cout << "Card image" << i + 1 << " û���ҵ�" << std::endl;
		}
		ss.str(""); //����ַ���
	}
	
	
	ss << "data/images/button" << imgButNo << ".jpg";
	if (!tButtons.loadFromFile(ss.str()))
	{
		std::cout << "button image û���ҵ�" << std::endl;
	}
	ss.str("");

	if (!tNum.loadFromFile("data/images/num.png"))
	{
		std::cout << "num.png û���ҵ�" << std::endl;
	}
	if (!tTimer.loadFromFile("data/images/jishiqi.png"))
	{
		std::cout << "jishiqi.png û���ҵ�" << std::endl;
	}

	ss << "data/images/gameover" << imgGONo << ".png";
	if (!tGameOver.loadFromFile(ss.str()))
	{
		std::cout << "gameover image û���ҵ�" << std::endl;
	}
	ss.str("");

	sBackground.setTexture(tBackground);
	sCdBackground.setTexture(tCdBackground);
	sButtons.setTexture(tButtons);
	sNum.setTexture(tNum);
	sTimer.setTexture(tTimer);
	sGameOver.setTexture(tGameOver);
	for (int i = 0; i < 52; i++) {
		sCard[i].setTexture(tCard[i]);

	}
}

void Game::CardSet() {
	srand((unsigned int)time(0));
	for (int j = 0; j < stageHeight; j++) {
		for (int i = 0; i < stageWidth; i++) {
			mGameData[j][i].card = 53;
		}
	}
	for (int i = 0; i < LV_NUM / 2;i++) {
		int m = rand() % stageHeight;
		int n = rand() % stageWidth;
		while (mGameData[m][n].card != 53) {
			m++;
			if (m > 5) {
				m = 0;
				n++;
			}
			if (n > 9) n = 0;
		}
		if (mGameData[m][n].card == 53) {
			mGameData[m][n].card = i;
		}
	}
	int k = 0;
	for (int j = 0; j < stageHeight; j++) {
		for (int i = 0; i < stageWidth; i++) {
			if (mGameData[j][i].card == 53) {
				mGameData[j][i].card = k;
				k++;
			}
		}
	}
}

void Game::Match() //���
{

	int a[4], b[4], t=0;
	if (PressNum >= 2) {
		for (int j = 0; j < stageHeight; j++) {
			for (int i = 0; i < stageWidth; i++) {
				if (mGameData[j][i].isPress == true && mGameData[j][i].isMatch == false)
				{
					a[t] = j;
					b[t] = i;
					t++;
				}
			}
		}
		if (PressNum < 4) {
			for (int i = 0; i < PressNum; i++) {
				for (int j = i + 1; j < PressNum; j++) {
					if (mGameData[a[i]][b[i]].card == mGameData[a[j]][b[j]].card) {
						mGameData[a[i]][b[i]].isMatch = true;
						mGameData[a[j]][b[j]].isMatch = true;
						for (int m = 0; m < PressNum; m++) {
							if (mGameData[a[m]][b[m]].isMatch != true) {
								Sleep(500);
								mGameData[a[m]][b[m]].mState = ncBG;
								mGameData[a[m]][b[m]].isPress = false;
							}
						}
						PressNum = 0;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < PressNum; i++) {
				for (int j = i + 1; j < PressNum; j++) {
					if (mGameData[a[i]][b[i]].card == mGameData[a[j]][b[j]].card) {
						mGameData[a[i]][b[i]].isMatch = true;
						mGameData[a[j]][b[j]].isMatch = true;
						for (int m = 0; m < PressNum; m++) {
							if (mGameData[a[m]][b[m]].isMatch != true) {
								Sleep(500);
								mGameData[a[m]][b[m]].mState = ncBG;
								mGameData[a[m]][b[m]].isPress = false;
							}
						}
						PressNum = 0;
					}
				}
			}
			if (PressNum != 0) {
				Sleep(500);
				for (int m = 0; m < PressNum; m++) {
					mGameData[a[m]][b[m]].mState = ncBG;
					mGameData[a[m]][b[m]].isPress = false;
				}
				PressNum = 0;
			}
		}
		
		
	}

	
}

void Game::Input()
{
	sf::Event event; //event types ����Window��Keyboard��Mouse��Joystick��4����Ϣ
					//ͨ��  bool Window :: pollEvent��sf :: Event��event�� �Ӵ���˳��ѯ�ʣ� polled ���¼��� 
					//�����һ���¼��ȴ������ú���������true�������¼���������䣨filled���¼����ݡ� 
					//������ǣ���ú�������false�� ͬ����Ҫ����Ҫע�⣬һ�ο����ж���¼�; ������Ǳ���ȷ������ÿ�����ܵ��¼��� 
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();  //���ڿ����ƶ���������С����С�����������Ҫ�رգ���Ҫ�Լ�ȥ����close()����
			gameQuit = true;
		}
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			window.close();  //���ڿ����ƶ���������С����С�����������Ҫ�رգ���Ҫ�Լ�ȥ����close()����
			gameQuit = true;
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			if (isGameOverState == ncNo)
			{
				if (mouseClickTimer.getElapsedTime().asMilliseconds() > 100)
					LButtonDown(Mouse::getPosition(window));	//�����ε���ļ������100���룬���ж�Ϊ��굥��
			}
		}
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (isGameOverState == ncNo)
			{
				mouseClickTimer.restart();//SFML��clock�����������getElapsedTime()��restart()�����򵥣�
				//��ť�ж�
				if (isGameBegin == false)
				{
					Initial();//��ʱˢ����̨
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (ButtonRectBG.contains(event.mouseButton.x, event.mouseButton.y))
			{
				imgBGNo++;
				if (imgBGNo > 2)//����������
					imgBGNo = 1;
				imgGONo++;
				if (imgGONo > 2)//ʤ��������
					imgGONo = 1;
				LoadMediaData();
			}
			if (ButtonRectSkin.contains(event.mouseButton.x, event.mouseButton.y))
			{
				imgCdBgNo++;
				if (imgCdBgNo > 2)//Ƥ��������
					imgCdBgNo = 1;
				imgButNo++;
				if (imgButNo > 2)//��ť������
					imgButNo = 1;
				LoadMediaData();
			}
			if (ButtonRectRestart.contains(event.mouseButton.x, event.mouseButton.y))
			{
				Initial();
			}
			if (ButtonRectQuit.contains(event.mouseButton.x, event.mouseButton.y))
			{
				window.close();
				gameOver = false;
				gameQuit = true;
			}

		}
	}
}
void Game::LButtonDown(Vector2i mPoint)		//������
{
	int i, j;
	i = (mPoint.x - mCornPoint.x) / Card_WIDTH;//��ȡ��굱ǰ����Ŀ��λ��
	j = (mPoint.y - mCornPoint.y) / Care_HEIGHT;

	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)//���������ڷ�Χ��
	{
		if (isGameBegin == false)//�����Ϸδ��ʼ
		{
			isGameBegin = true;//��Ϸ��ʼ
			CardSet();
			gameClock.restart();
		}
		if (mGameData[j][i].isMatch == false) {//���״̬���������
			if (mGameData[j][i].isPress == false)
			{
				mGameData[j][i].isPress = true;//��ǰ�鱻���
				mGameData[j][i].mState = ncCARD;
				PressNum++;
			}
		}
	}
}

void Game::Logic()
{
	isWin();
}
void Game::isWin()
{
	int i, j, c = 0;
	for (j = 0; j < stageHeight; j++)
		for (i = 0; i < stageWidth; i++)
		{
			if (mGameData[j][i].mState == ncCARD)
				c++;
		}
	if (c == LV_NUM) {
		isGameBegin = false;
		isGameOverState = ncWIN;
	}
}
void Game::Draw()
{
	window.clear();	//����

	//���Ʊ���
	sBackground.setPosition(0, 0);
	window.draw(sBackground);

	//������̨
	
	DrawButton();
	DrawTimer();
	DrawCard();

	if (isGameOverState)
		DrawGameEnd();

	window.display();//����ʾ�����������ݣ���ʾ����Ļ�ϡ�SFML���õ���˫�������
}
void Game::DrawCard()
{
	int x = 35, y = 110;
	int x1 = x, y1 = y, i = 0;
	for (int i = 0; i < stageWidth; i++) {
		for (int j = 0; j < stageHeight; j++) {
			int k = mGameData[j][i].card;
			switch (mGameData[j][i].mState)
			{
			case ncBG:
				sCdBackground.setPosition(x1, y1);
				window.draw(sCdBackground);
				break;
			case ncCARD:
				sCard[k].setPosition(x1, y1);
				window.draw(sCard[k]);
				break;
			}
			y1 += 120;
		}
		x1 += 100;
		y1 = y;
	}
	
}

void Game::DrawButton()
{
	Vector2i LeftCorner;
	int ButtonWidth = 150;
	int ButtonHeight = 100;
	int detaX = 55;
	LeftCorner.x = detaX;//ָ�����
	LeftCorner.y = Window_height - GRIDSIZE * 5;//ָ���߶�

	//ButtonRectRestart
	sButtons.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);							//	���ð�ť��λ������
	ButtonRectRestart.left = LeftCorner.x;											//��¼��ť��λ������
	ButtonRectRestart.top = LeftCorner.y;
	ButtonRectRestart.width = ButtonWidth;
	ButtonRectRestart.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectSkin;
	LeftCorner.x = detaX * 3 + ButtonWidth;
	sButtons.setTextureRect(IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);							//	���ð�ť��λ������
	ButtonRectSkin.left = LeftCorner.x;											//��¼��ť��λ������
	ButtonRectSkin.top = LeftCorner.y;
	ButtonRectSkin.width = ButtonWidth;
	ButtonRectSkin.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectBG
	LeftCorner.x = detaX * 5 + ButtonWidth * 2;
	sButtons.setTextureRect(IntRect(2 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);							//	���ð�ť��λ������
	ButtonRectBG.left = LeftCorner.x;											//��¼��ť��λ������
	ButtonRectBG.top = LeftCorner.y;
	ButtonRectBG.width = ButtonWidth;
	ButtonRectBG.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectQuit
	LeftCorner.x = detaX * 7 + ButtonWidth * 3;
	sButtons.setTextureRect(IntRect(3 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);							//	���ð�ť��λ������
	ButtonRectQuit.left = LeftCorner.x;											//��¼��ť��λ������
	ButtonRectQuit.top = LeftCorner.y;
	ButtonRectQuit.width = ButtonWidth;
	ButtonRectQuit.height = ButtonHeight;
	window.draw(sButtons);

}
void Game::DrawTimer()
{
	Vector2i LeftCorner;
	LeftCorner.x = Window_width - sTimer.getLocalBounds().width*1.1;
	LeftCorner.y = 10;
	sTimer.setPosition(LeftCorner.x, LeftCorner.y);	//�������������ͼλ��
	window.draw(sTimer);

	if (isGameBegin)
		mTime = gameClock.getElapsedTime().asSeconds();

	int mScore = mTime;
	if (mScore > 999)
		mScore = 999;

	int NumSizex = 50;
	int NumSizey = 90;
	LeftCorner.x = LeftCorner.x + sTimer.getLocalBounds().width - NumSizex ;
	LeftCorner.y = LeftCorner.y ;

	//���Ƹ�λ��������
	int a = mScore % 10;
	sNum.setTextureRect(IntRect(a * NumSizex, 0, NumSizex, NumSizey));//������ȡ��������
	sNum.setPosition(LeftCorner.x, LeftCorner.y);//�ں�λ��
	window.draw(sNum);
	//����ʮλ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSizex;
	sNum.setTextureRect(IntRect(a * NumSizex, 0, NumSizex, NumSizey));//������ȡ��������
	sNum.setPosition(LeftCorner.x, LeftCorner.y);//�ں�λ��
	window.draw(sNum);
	//���ư�λ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSizex;
	sNum.setTextureRect(IntRect(a * NumSizex, 0, NumSizex, NumSizey));//������ȡ��������
	sNum.setPosition(LeftCorner.x, LeftCorner.y);//�ں�λ��
	window.draw(sNum);
}
void Game::DrawGameEnd()
{
	Vector2i LeftCorner;
	int ButtonWidth = 700;
	int ButtonHeight = 700;
	LeftCorner.x = (Window_width - ButtonWidth) / 2;//ָ����������
	LeftCorner.y = (Window_height - ButtonHeight) / 2;//ָ����������

	sGameOver.setPosition(LeftCorner.x, LeftCorner.y);							//	���ð�ť��λ������

	if (isGameOverState == ncWIN)
	{
		sGameOver.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
	}
	window.draw(sGameOver);
}
void Game::Run()
{
	do
	{
		Initial();
		while (window.isOpen() && gameOver == false)
		{
			Input();

			Logic();

			Draw();

			Match();
		}
	} while (!gameQuit);

}