#pragma once	//只需要链接一次
#include <string>
#include <map>
using namespace std;
//Ini文件的Value部分
class Value
{
public:
	Value();
	Value(bool value);
	Value(int value);
	Value(double value);
	Value(const char * value);
	Value(const string & value);

	//重载赋值运算符(方便实际使用)
	//void operator = (bool value);
	//void operator = (int value);
	//void operator = (double value);
	//void operator = (const char * value);
	//void operator = (const string & value);
	//将上述代码调整为引用减少代码重复
	//(1)以引用返回函数值，定义函数时需要在函数名前加&
	//(2)用引用返回一个函数值的最大好处是，在内存中不产生被返回值的副本。
	Value & operator = (bool value);
	Value & operator = (int value);
	Value & operator = (double value);
	Value & operator = (const char * value);
	Value & operator = (const string & value);

	//类型转换	没有返回值
	operator bool();
	operator int();
	operator double();
	operator string();
private:
	string m_value;	//负责保存value值
};

//定义section键值对key = value
typedef std::map<string, Value> Section;
class IniFile
{
public:
	IniFile();
	bool load(const string & filename);	//加载文件函数
	bool save(const string & filename);	//保存文件
	void show();	//打印内容
	string str();	//将配置文件中的所有内容转化为字符串

	Value & get(const string & section, const string & key);	//获取对应section下key的value
// 	void set(const string & section, const string & key, bool value);
// 	void set(const string & section, const string & key, int value);
// 	void set(const string & section, const string & key, double value);
// 	void set(const string & section, const string & key, const char * value);
// 	void set(const string & section, const string & key, const string & value);
	//优化set写法
	void set(const string & section, const string & key, const Value & value);	//设置对应section下key的value

	bool has(const string & section);	//判断是或否有section
	bool has(const string & section, const string & key);	//判断section下是否有key

	void remove(const string & section);	//删除section
	void remove(const string & section, const string & key);	//删除section下的key
	void clear();	//清空所有内容

	//只需要重载IniFile的中括号，返回Section即可因为section为map可以直接使用中括号
	Section & operator [](const string& section)
	{
		return m_sections[section];
	}
private:
	string trim(string s);	//将string中空格 \n \t裁剪
private:
	string m_filename;//文件名
	std::map<string, Section> m_sections;
};