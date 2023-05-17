#include "IniFIle.h"
#include <sstream>	//string转数字类型的标准模板库
#include <fstream>
#include <iostream>
Value::Value()
{

}

//Value::Value(bool value)
//{
//	//value ? m_value = "true" : m_value = "false";
//	m_value = value ? "true" : "false";
//}
//
//Value::Value(int value)
//{
//	stringstream ss;
//	ss << value;
//	m_value = ss.str();
//}
//
//Value::Value(double value)
//{
//	stringstream ss;
//	ss << value;
//	m_value = ss.str();
//}
//
////构造函数赋值写法
//Value::Value(const char * value) :m_value(value)
//{
//
//}
//
//Value::Value(const string & value) : m_value(value)
//{
//
//}
//
//
//void Value::operator = (bool value)
//{
//	m_value = value ? "true" : "false";
//}
//
//void Value::operator = (int value)
//{
//	stringstream ss;
//	ss << value;
//	m_value = ss.str();
//}
//
//void Value::operator = (double value)
//{
//	stringstream ss;
//	ss << value;
//	m_value = ss.str();
//}
//
//void Value::operator = (const char * value)
//{
//	m_value = value;
//}
//
//void Value::operator = (const string & value)
//{
//	m_value = value;
//}

//修改后的写法
Value::Value(bool value)
{
	*this = value;
}

Value::Value(int value)
{
	*this = value;
}

Value::Value(double value)
{
	*this = value;
}

Value::Value(const char * value)
{
	*this = value;
}

Value::Value(const string & value)
{
	*this = value;
}


Value & Value::operator = (bool value)
{
	m_value = value ? "true" : "false";
	return *this;
}

Value & Value::operator = (int value)
{
	stringstream ss;
	ss << value;
	m_value = ss.str();
	return *this;
}

Value & Value::operator = (double value)
{
	stringstream ss;
	ss << value;
	m_value = ss.str();
	return *this;
}

Value & Value::operator = (const char * value)
{
	m_value = value;
	return *this;
}

Value & Value::operator = (const string & value)
{
	m_value = value;
	return *this;
}

Value::operator bool()
{
// 	if (m_value == "true") {
// 		return true;
// 	}
// 	return false;
	//优化
	return m_value == "true";
}
Value::operator int()
{
	return std::atoi(m_value.c_str());
}
Value::operator double()
{
	return std::atof(m_value.c_str());
}
Value::operator string()
{
	return m_value;
}

IniFile::IniFile()
{

}

bool IniFile::load(const string & filename)
{
	m_filename = filename;
	//读取文件使用ifstream
	ifstream fin(filename);
	if (fin.fail()) {
		return false;
	}
	//读取文件
	string line;
	string section;
	while (std::getline(fin, line)) {
		line = trim(line);
		//std::cout << line << std::endl;
		if (line == "") {
			continue;
		}
		if (line[0] == '[') {
			int pos = line.find_first_of(']');
			section = line.substr(1, pos - 1);
			section = trim(section);
			m_sections[section] = Section();
		}
		else {//如果不是段，判断为key value
			int pos = line.find_first_of('=');
			string key = line.substr(0, pos);
			key = trim(key);
			string value = line.substr(pos + 1, line.length() - pos);
			value = trim(value);
			m_sections[section][key] = value;
		}
	}
	fin.close();
	return true;
}

string IniFile::trim(string s)
{
	if (s.empty()) {
		return s;
	}
	//将头尾的空格给删除
	s.erase(0, s.find_first_not_of(" \n\r"));
	s.erase(s.find_last_not_of(" \n\r") + 1);
	return s;
}

Value & IniFile::get(const string & section, const string & key)
{
	return m_sections[section][key];
}

// void IniFile::set(const string & section, const string & key, bool value)
// {
// 	m_sections[section][key] = value;
// }
// void IniFile::set(const string & section, const string & key, int value)
// {
// 	m_sections[section][key] = value;
// }
// void IniFile::set(const string & section, const string & key, double value)
// {
// 	m_sections[section][key] = value;
// }
// void IniFile::set(const string & section, const string & key, const char * value)
// {
// 	m_sections[section][key] = value;
// }
// void IniFile::set(const string & section, const string & key, const string & value)
// {
// 	m_sections[section][key] = value;
// }
//Value实现了数据类型转换
void IniFile::set(const string & section, const string & key, const Value & value)
{
	m_sections[section][key] = value;
}

bool IniFile::has(const string & section)
{
	return (m_sections.find(section) != m_sections.end());
}

bool IniFile::has(const string & section, const string & key)
{
	//先判断是否有这个段
	std::map<string, Section>::const_iterator it = m_sections.find(section);
	if (it != m_sections.end()) {
		return (it->second.find(key) != it->second.end());
	}
	return false;
}

void IniFile::remove(const string & section)
{
	m_sections.erase(section);
}

void IniFile::remove(const string & section, const string & key)
{
	//先判断是否有这个段,不能使用const_iterator否则删除失败
	std::map<string, Section>::iterator it = m_sections.find(section);
	if (it != m_sections.end()) {
		it->second.erase(key);
	}
}

void IniFile::clear()
{
	m_sections.clear();
}

string IniFile::str()
{
	stringstream ss;
	for (std::map<string, Section>::iterator it = m_sections.begin();
		it != m_sections.end(); it++)
	{
		ss << "[" << it->first << "]" << endl;
		for (std::map<string, Value>::iterator iter = it->second.begin();
			iter != it->second.end(); iter++)
		{
			ss << iter->first << " = " << string(iter->second) << endl;
		}
		ss << endl;
	}
	return ss.str();
}

void IniFile::show()
{
	std::cout << str();
}

bool IniFile::save(const string & filename)
{
	ofstream fout(filename);
	if (fout.fail()) {
		return false;
	}
	fout << str();
	fout.close();
	return true;
}