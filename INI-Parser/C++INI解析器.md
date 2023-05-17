# C++INI解析器

## 常用配置文件有

INI、XML、JSON、YAML

### INI

```ini
[server]
ip = 127.0.0.1
port = 80

[profile]
name = jack
gender = male
age = 30
```

优点：非常简单、书写方便

缺点：不能表达复杂的数据格式

应用场景：配置文件

### XML

```xml
<?xml version="1.0"?>
<root>
    <server>
    	<ip>127.0.0.1</ip>
    	<port>80</port>
    </server>
    <profile>
    	<name>jack</name>
        <gender>male</gender>
        <age>30</age>
    </profile>
</root>
```

优点：可以表达复杂的数据格式

缺点：复杂、书写麻烦

应用场景：配置文件，数据传输

### JSON

```json
{
    "server":{
        "ip":"127.0.0.1",
        "port":80
    },
    "profile":{
        "name":"jack",
        "gender":"male",
        "age":30
    }
}
```

优点：简单、可以表达复杂的数据格式

缺点：书写麻烦

应用场景：配置文件、数据传输

### YAML

```yaml
server:
	ip: 127.0.0.1
	prot: 80
	
profile:
	name: jack
	gender: male 
	age: 30
```

优点：简单、直接、书写方便、可以表达复杂的数据格式

缺点：它使用空白符号缩进，使用场景受限，无法进行数据传输

运用场景：配置文件

## 应用INI原因

1. 非常简单、书写方便
2. 运用广泛：mysql、redis、php的配置等

## INI格式

INI文件的格式很简单，最基本的三个要素是：sections、parameters、comments

```ini
[sections]
key = value
#注释
```

实例：

main.ini

```ini
[server]
ip = 127.0.0.1
port = 80

[profile]
name = jack
gender = male
age = 30
```

## 主要步骤

1. 先写value类，value需要重载不同类型的构造函数、=号赋值、强制类型转换
2. 写Inifile类，读取ini配置文件，将section-key-value使用map<string, map<string, value>>结构存储
3. 写Inifle类的get函数，获取对应的值
4. 重载Inifile类的中括号，使类可以像访问数组一样获取value，只需要重载IniFile的中括号，返回Section即可因为section为map可以直接使用中括号
5. 写Inifile类的set函数，设置对应的值
6. 写Inifile类中has函数，判断是否有某个段（section）、某个key
7. 写Inifile类中remove函数，删除段、key
8. 写Inifile类中save函数，将文件的内容保存到另外一个文件中

> 注：已知bug，调用get时如果是原本缺少的key，会自动创建出一个新的key和空value