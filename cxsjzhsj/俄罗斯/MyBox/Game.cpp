#include "stdafx.h"
#include "Game.h"


//Game��Ĺ��캯��
Game::Game(int height, int width) : _tool(0), _nextTool(0)
{
	_netWidth = width;
	_netHeight = height;
	_bigNet = _bigNetAux = NULL;
	_state = STOP;
	_bigNet = new int[_netHeight*_netWidth];   // ������Ϸ�����ʾ����
	_bigNetAux = new int[_netHeight*_netWidth];	// ������Ϸ�����ʾ��������
	for (int i = 0; i < _netHeight; i++)	// ��ʼ����Ϸ�����ʾ����Ϊ0
		for (int j = 0; j < _netWidth; j++)
			_bigNet[i*_netWidth + j] = 0;
	srand((unsigned int)time(0));				// ��������֣���������˹������״�����ʹ��
}

//��������
Game::~Game(void)
{
	delete[] _bigNet;
	delete[] _bigNetAux;
}

//��ʼ��Ϸ
void Game::Start()
{
	_state = GO;			// ��ʼ����Ϸ״̬Ϊ����״̬
	for (int i = 0; i < _netHeight; i++)	// ��ʼ����Ϸ�����ʾ����Ϊ0
		for (int j = 0; j < _netWidth; j++)
			_bigNet[i*_netWidth + j] = 0;
	NextTool();								//	�����������η���Ĳ���
	NextTool();
}

//������һ������
void Game::NextTool()
{                                 // С���ڻ�ľ�����������µĻ�ľ�����ó���λ��
	_iLocY = 0;					  //4*4�������ڵ����Ͻ�Y����
	_iLocX = (_netWidth - 4) / 2; //4*4�������ڵ����Ͻ�X����
	_tool = _nextTool;
	_nextTool = Tool(rand() % 5 + 1);  //������һ������˹����
}

//�����Ƿ���������ƶ�
bool Game::CanMoveDown()
{
	int cnt1 = 4, cnt2 = 0;
	cnt1 += CountNoneZero(_bigNet, _netHeight, _netWidth);
	// ͳ�Ʊ任�󷽿���
	AddToolToAux(_bigNetAux, _iLocX, _iLocY + 1, _tool); // ���跢���任
	cnt2 = CountNoneZero(_bigNetAux, _netHeight, _netWidth);
	return cnt2 == cnt1;
}

//��������е�һά�����в�Ϊ0��Ԫ����
int Game::CountNoneZero(int *matrix, int Height, int Width)
{
	int cnt = 0;
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++) {
			if (matrix[i*Width + j] != 0)
				++cnt;
		}
	return cnt;
}

//������˹�����Ǽ��뵽ָ��������������
void Game::AddToolToAux(int *net, int iOffsetX, int iOffsetY, const Tool &_tool)
{
	if (net != _bigNet)   //��Ҫʱ�ȸ���������������ָ������
		for (int i = 0; i < _netHeight; i++)
			for (int j = 0; j < _netWidth; j++)
				net[i*_netWidth + j] = _bigNet[i*_netWidth + j];
	int iType = _tool.GetType();
	if (iType != 0) {
		//�ϲ�����˹��������
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				if (i + iOffsetY >= 0 &&
					i + iOffsetY < _netHeight  &&
					j + iOffsetX >= 0 &&
					j + iOffsetX < _netWidth   &&
					_tool.ElementAt(i, j) != 0)
					net[(i + iOffsetY)*_netWidth + j + iOffsetX] = iType;
			}
	}
}

//���������ƶ�һ��
void Game::MoveDown()
{
	++_iLocY;
}

//�����Ƿ���������ƶ�
bool Game::CanMoveLeft()
{
	int cnt1 = 4, cnt2 = 0;
	cnt1 += CountNoneZero(_bigNet, _netHeight, _netWidth);
	// ͳ�Ʊ任�󷽿���
	AddToolToAux(_bigNetAux, _iLocX - 1, _iLocY, _tool); // ���跢���任
	cnt2 = CountNoneZero(_bigNetAux, _netHeight, _netWidth);
	return cnt2 == cnt1;
}

//�����Ƿ���������ƶ�
bool Game::CanMoveRight()
{
	int cnt1 = 4, cnt2 = 0;
	// ͳ�Ʊ任�󷽿���
	cnt1 += CountNoneZero(_bigNet, _netHeight, _netWidth);
	AddToolToAux(_bigNetAux, _iLocX + 1, _iLocY, _tool); // ���跢���任
	cnt2 = CountNoneZero(_bigNetAux, _netHeight, _netWidth);
	return cnt2 == cnt1;
}

//���������ƶ�һ��
void Game::MoveLeft()
{
	--_iLocX;
}

//���������ƶ�һ��
void Game::MoveRight()
{
	++_iLocX;
}

//�����Ƿ���Ա任��̬
bool Game::CanRoll()
{
	int cnt1 = 4, cnt2 = 0;
	cnt1 += CountNoneZero(_bigNet, _netHeight, _netWidth);
	// ͳ�Ʊ任�󷽿���
	Tool  toolRotated = _tool.Roll();
	AddToolToAux(_bigNetAux, _iLocX, _iLocY, toolRotated); // ���跢���任
	cnt2 = CountNoneZero(_bigNetAux, _netHeight, _netWidth);
	return cnt2 == cnt1;
}

//�任������̬
void Game::Roll() {
	_tool = _tool.Roll(); //����ת�����˹�������
}

//����������մ�����
void Game::Input(UINT nChar)
{
	switch (nChar) {
	case VK_UP: if (CanRoll())     Roll(); break;
	case VK_DOWN: if (CanMoveDown()) MoveDown(); break;
	case VK_LEFT: if (CanMoveLeft()) MoveLeft(); break;
	case VK_RIGHT: if (CanMoveRight()) MoveRight(); break;
	}
}

//����һ��
bool Game::Go()
{
	if (CanMoveDown()) {			//�ж��Ƿ���������ƶ�һ��
		MoveDown();					//�����ƶ�һ��
		return true;
	}
	else {
		AddToolToAux(_bigNet, _iLocX, _iLocY, _tool); //������ӵ���Ϸ������������
		RemoveLines();				//�Ƴ�����
		NextTool();					//������м�����һ������
		if (IsDead()) {
			_state = STOP;			//������Ϸ״̬Ϊֹͣ
			return false;
		}
		return true;
	}
}

//�Ƴ��в���
void Game::RemoveLines()
{
	for (int i = _netHeight - 1; i >= 0; i--)
		while (CanRemoveLine(i)) //����������ʱ����������
			RemoveLine(i);
}

//�Ƿ�����Ƴ�һ��
bool Game::CanRemoveLine(int index)
{
	int count = 0;
	for (int i = 0; i < _netWidth; i++)
		if (_bigNet[index*_netWidth + i] != 0)
			count++;
	return count == _netWidth; //С��������������������ʱ���п�����
}

//�Ƴ�һ��
void Game::RemoveLine(int index)
{
	for (int i = index; i > 0; i--) //ǰ������������һ��
		for (int j = 0; j < _netWidth; j++)
			_bigNet[i*_netWidth + j] = _bigNet[(i - 1)*_netWidth + j];
	for (int j = 0; j < _netWidth; j++) //��1����0
		_bigNet[j] = 0;
}

//��Ϸ�Ƿ����
bool Game::IsDead()
{
	int cnt1 = 4, cnt2 = 0;
	cnt1 += CountNoneZero(_bigNet, _netHeight, _netWidth);
	// ͳ�Ƽ������˹�����С������
	AddToolToAux(_bigNetAux, _iLocX, _iLocY, _tool); // ���跢���任
	cnt2 = CountNoneZero(_bigNetAux, _netHeight, _netWidth);
	return cnt2 != cnt1; 	//���Ⱦ������ص����������������Dead
}

//��ͣ/�������Ŀ��ƺ���
void Game::PauseOrContinue()
{
	if (_state == PAUSE)
		_state = GO;
	else if (_state == GO)
		_state = PAUSE;
}

