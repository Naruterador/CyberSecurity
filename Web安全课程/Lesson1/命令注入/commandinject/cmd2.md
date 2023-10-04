```php
<html>                                                                                                           
    <body>
        <form action="" method="get">
            <input type="text" name='ip' />
            <input type="submit" name="submit" value="提交">
<?php
$res = FALSE;
if (isset($_GET['submit'])){
    $ip = $_GET['ip'];
    $m = [];
    if (!preg_match_all("/ /", $ip, $m)){
        $cmd = shell_exec( 'ping  -c 4 ' . $ip );
        echo $cmd;
    }
}
?>
        </form>
    </body>
</html>
```

- 这题过滤了空格
  - payload:
    -   用\${IFS}绕过 127.0.0.1;cat${IFS}flag_1630334994276.php
    -   \${IFS}在Shell脚本中的作用是表示"内部字段分隔符"（Internal Field Separator）。它是一个特殊的Shell变量，用于确定Shell在解析命令和数据时如何将单词和行分割为标记。${IFS}的默认值通常设置为空白字符（即空格、制表符和换行符），这意味着Shell将根据空格和制表符来将文本分割成单词和标记。