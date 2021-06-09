#pragma once
class Tool
{
private:
	int _data[4][4];//4*4的方块数组变量
	int _type;		//俄罗斯方块的类型变量

public:
	Tool(int type);	//构造函数,本类没有使用动态分配，无需析构，类对象可直接复制、赋值。
	const int GetType() const;	//获取Tool的类型
	const int & ElementAt(int i, int j) const; //获取小方块数值
	Tool Roll();	//对方块进行形态变换
};

