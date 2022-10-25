## Xpath
- MySQL 5.1提供了内置的XML文件解析和修改函数ExtractValue()和UpdateXML()，这样就可以直接使用Mysql来操作XML了，再不用其它编程语言来处理，也显示方便很多
- *注意: 在表里需要设置xml的字段是text格式或者longtext*

#### ExtractValue(查询)
- 语法: ExtractValue(XML_document, XPath_string)
```html
-- 在mysql中设置变量temp_xml
SET @temp_xml = '
<?xml version="1.0" encoding="UTF-8"?>
<root>
    <meta name="description">我在作测试</meta>
    <element name="节点1">
        <child name="子节点1">子节 点1值</child>
    </element>
    <element name="节点2">
        <child name="子节点2">子节点2值</child>
    </element>  
</root>
';

-- 查看变量内容
select @temp_xml

-- 查询xml中指定节点内容
select extractvalue(@temp_xml,'/root/element/child/@name') attr, extractvalue(@temp_xml,'/root/element/child') value;
```

#### 语法: UPDATEXML (XML_document, XPath_string, new_value); 使用UpdateXML修改完内容后会将最新的XML_document返回
```html
ET @temp_xml = '
<?xml version="1.0" encoding="UTF-8"?>
<root>
    <meta name="description">我在作测试</meta>
    <element name="节点1">
        <child name="子节点1">子节 点1值</child>
    </element>
    <element name="节点2">
        <child name="子节点2">子节点2值</child>
    </element>  
</root>
';

select UpdateXML(@temp_xml,'/root/element/child[@name="子节点1"]','子节 点1值xxx') attr 

-- 注意: UpdateXML 不会直接修改原值, 所以需要将修改后的新xml从新赋值进去才行
SET @temp_xml= UpdateXML(@temp_xml,'/root/element/child[@name="子节点1"]','子节 点1值xxx')
```

#### 如果xml内容存储在表里那么修改方式如下:
```html
update  表 
set  xml_doc=UpdateXML(xml_doc,'/root/element/child[@name="子节点1"]','子节 点1值xxx')  
where  条件
```