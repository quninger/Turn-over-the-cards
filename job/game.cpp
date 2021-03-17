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
	window.create(sf::VideoMode(Window_width, Window_height), L"翻牌游戏");
}


Game::~Game()
{
}

void Game::Initial()
{
	window.setFramerateLimit(10); //每秒设置目标帧数
	cardSize = GRIDSIZE; //点击的位置的块的大小


	stageWidth = LV_WIDTH;//舞台宽度（牌列数
	stageHeight = LV_HEIGHT;//舞台高度（牌行数
	//mMineNum = LV_NUM;

	gameOver = false;
	gameQuit = false;
	isGameOverState = ncNo;	//初始化游戏的结束状态
	isGameBegin = false;	//初始化游戏是否开始
	mTime = 0;				//初始化游戏进行的时间

	mCornPoint.x = (Window_width - stageWidth * Card_WIDTH) / 2;		//设置舞台的左上角坐标
	mCornPoint.y = (Window_height - stageHeight * Care_HEIGHT) / 2;
	IniData();		//初始化数据
	LoadMediaData();	//加载素材
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
	//牌的图片
	ss << "data/images/cdbg" << imgCdBgNo << ".jpg";
	if (!tCdBackground.loadFromFile(ss.str()))
	{
		std::cout << "Card Background image 没有找到" << std::endl;
	}
	ss.str("");

	ss << "data/images/BG" << imgBGNo << ".jpg";
	if (!tBackground.loadFromFile(ss.str()))
	{
		std::cout << "Background image 没有找到" << std::endl;
	}
	ss.str("");
	
	for (int i = 0; i < 52; i++) {
		ss << "data/images/pukeimage/" << i + 1 << ".jpg";
		if (!tCard[i].loadFromFile(ss.str()))
		{
			std::cout << "Card image" << i + 1 << " 没有找到" << std::endl;
		}
		ss.str(""); //清空字符串
	}
	
	
	ss << "data/images/button" << imgButNo << ".jpg";
	if (!tButtons.loadFromFile(ss.str()))
	{
		std::cout << "button image 没有找到" << std::endl;
	}
	ss.str("");

	if (!tNum.loadFromFile("data/images/num.png"))
	{
		std::cout << "num.png 没有找到" << std::endl;
	}
	if (!tTimer.loadFromFile("data/images/jishiqi.png"))
	{
		std::cout << "jishiqi.png 没有找到" << std::endl;
	}

	ss << "data/images/gameover" << imgGONo << ".png";
	if (!tGameOver.loadFromFile(ss.str()))
	{
		std::cout << "gameover image 没有找到" << std::endl;
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

void Game::Match() //配对
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
	sf::Event event; //event types 包括Window、Keyboard、Mouse、Joystick，4类消息
					//通过  bool Window :: pollEvent（sf :: Event＆event） 从窗口顺序询问（ polled ）事件。 
					//如果有一个事件等待处理，该函数将返回true，并且事件变量将填充（filled）事件数据。 
					//如果不是，则该函数返回false。 同样重要的是要注意，一次可能有多个事件; 因此我们必须确保捕获每个可能的事件。 
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();  //窗口可以移动、调整大小和最小化。但是如果要关闭，需要自己去调用close()函数
			gameQuit = true;
		}
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			window.close();  //窗口可以移动、调整大小和最小化。但是如果要关闭，需要自己去调用close()函数
			gameQuit = true;
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			if (isGameOverState == ncNo)
			{
				if (mouseClickTimer.getElapsedTime().asMilliseconds() > 100)
					LButtonDown(Mouse::getPosition(window));	//当两次点击的间隔大于100毫秒，则判定为鼠标单击
			}
		}
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (isGameOverState == ncNo)
			{
				mouseClickTimer.restart();//SFML的clock类就两个函数getElapsedTime()和restart()，超简单！
				//按钮判断
				if (isGameBegin == false)
				{
					Initial();//及时刷新舞台
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (ButtonRectBG.contains(event.mouseButton.x, event.mouseButton.y))
			{
				imgBGNo++;
				if (imgBGNo > 2)//背景的数量
					imgBGNo = 1;
				imgGONo++;
				if (imgGONo > 2)//胜利的数量
					imgGONo = 1;
				LoadMediaData();
			}
			if (ButtonRectSkin.contains(event.mouseButton.x, event.mouseButton.y))
			{
				imgCdBgNo++;
				if (imgCdBgNo > 2)//皮肤的数量
					imgCdBgNo = 1;
				imgButNo++;
				if (imgButNo > 2)//按钮的数量
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
void Game::LButtonDown(Vector2i mPoint)		//鼠标左击
{
	int i, j;
	i = (mPoint.x - mCornPoint.x) / Card_WIDTH;//获取鼠标当前点击的块的位置
	j = (mPoint.y - mCornPoint.y) / Care_HEIGHT;

	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)//如果点击是在范围内
	{
		if (isGameBegin == false)//如果游戏未开始
		{
			isGameBegin = true;//游戏开始
			CardSet();
			gameClock.restart();
		}
		if (mGameData[j][i].isMatch == false) {//如果状态不是已配对
			if (mGameData[j][i].isPress == false)
			{
				mGameData[j][i].isPress = true;//当前块被点击
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
	window.clear();	//清屏

	//绘制背景
	sBackground.setPosition(0, 0);
	window.draw(sBackground);

	//绘制舞台
	
	DrawButton();
	DrawTimer();
	DrawCard();

	if (isGameOverState)
		DrawGameEnd();

	window.display();//把显示缓冲区的内容，显示在屏幕上。SFML采用的是双缓冲机制
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
	LeftCorner.x = detaX;//指定宽度
	LeftCorner.y = Window_height - GRIDSIZE * 5;//指定高度

	//ButtonRectRestart
	sButtons.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//读取按钮的纹理区域
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);							//	设置按钮的位置坐标
	ButtonRectRestart.left = LeftCorner.x;											//记录按钮的位置区域
	ButtonRectRestart.top = LeftCorner.y;
	ButtonRectRestart.width = ButtonWidth;
	ButtonRectRestart.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectSkin;
	LeftCorner.x = detaX * 3 + ButtonWidth;
	sButtons.setTextureRect(IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//读取按钮的纹理区域
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);							//	设置按钮的位置坐标
	ButtonRectSkin.left = LeftCorner.x;											//记录按钮的位置区域
	ButtonRectSkin.top = LeftCorner.y;
	ButtonRectSkin.width = ButtonWidth;
	ButtonRectSkin.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectBG
	LeftCorner.x = detaX * 5 + ButtonWidth * 2;
	sButtons.setTextureRect(IntRect(2 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//读取按钮的纹理区域
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);							//	设置按钮的位置坐标
	ButtonRectBG.left = LeftCorner.x;											//记录按钮的位置区域
	ButtonRectBG.top = LeftCorner.y;
	ButtonRectBG.width = ButtonWidth;
	ButtonRectBG.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectQuit
	LeftCorner.x = detaX * 7 + ButtonWidth * 3;
	sButtons.setTextureRect(IntRect(3 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//读取按钮的纹理区域
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);							//	设置按钮的位置坐标
	ButtonRectQuit.left = LeftCorner.x;											//记录按钮的位置区域
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
	sTimer.setPosition(LeftCorner.x, LeftCorner.y);	//计数器纹理的贴图位置
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

	//绘制个位数的数字
	int a = mScore % 10;
	sNum.setTextureRect(IntRect(a * NumSizex, 0, NumSizex, NumSizey));//纹理上取数字纹理
	sNum.setPosition(LeftCorner.x, LeftCorner.y);//摆好位置
	window.draw(sNum);
	//绘制十位数的数字
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSizex;
	sNum.setTextureRect(IntRect(a * NumSizex, 0, NumSizex, NumSizey));//纹理上取数字纹理
	sNum.setPosition(LeftCorner.x, LeftCorner.y);//摆好位置
	window.draw(sNum);
	//绘制百位数的数字
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSizex;
	sNum.setTextureRect(IntRect(a * NumSizex, 0, NumSizex, NumSizey));//纹理上取数字纹理
	sNum.setPosition(LeftCorner.x, LeftCorner.y);//摆好位置
	window.draw(sNum);
}
void Game::DrawGameEnd()
{
	Vector2i LeftCorner;
	int ButtonWidth = 700;
	int ButtonHeight = 700;
	LeftCorner.x = (Window_width - ButtonWidth) / 2;//指定顶点坐标
	LeftCorner.y = (Window_height - ButtonHeight) / 2;//指定顶点坐标

	sGameOver.setPosition(LeftCorner.x, LeftCorner.y);							//	设置按钮的位置坐标

	if (isGameOverState == ncWIN)
	{
		sGameOver.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//读取按钮的纹理区域
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