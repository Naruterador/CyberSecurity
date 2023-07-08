#### Nmap语法
- -A 全面扫描/综合扫描
```shell
nmap-A 127.0.0.1 
```

- 扫描指定网段
```shell
nmap 127.0.0.1
nmap 127.0.0.1/24
```

#### Nmap 主机发现

- -sP ping扫描
```shell
nmap -sP 127.0.0.1
```

- -P0 无ping扫描备注：【协议1,协设2〕【目标】扫描
```shell
nmap -P0 127.0.0.1
```

- 如果想知道是如何判断目标主机是否存在可以使用--packet-trace选项
```shell
nmap -P0 --packet-trace 127.0.0.1
```

- -PS TCP SYN Ping扫描
```shell
nmap -PS -v 127.0.0.1
#指定端口
nmap -PS 80,100-200 -v 127.0.0.1
```

- -PA TCP ACK Ping扫描
```shell
nmap -PA -v 127.0.0.1
```

- -PU UDP Ping扫描
```shell
nmap -PU -v 127.0.0.1
```

- -PE;-PP;-PM ICMP Ping Types 扫描
   - 使用ICMP Echo扫描方式
   ```shell
   nmap -PE -v 127.0.0.1
   ```
   - -PE:-PP:-PM
     ```shell
     #使用ICMP时间戳Ping扫描
     mmap -PP -v 127.0.0.1
     #使用ICMP地址掩码Ping扫描
     nmap -PM -v 127.0.0.1

- -PR ARP Ping
   ```shell
   #-PR可以实现ARP协议的主机发现
   #当目标主机和我们处于同一个网段的时候，使用ARP协议扫描技术就是最佳的选择。不仅速度快，扫描结果也是最为精准。这是因为没有任何的安全措施会阻止正常的ARP请求
   nmap -PR 127.0.0.1
   ```

- -n 禁止DNS反向解析(使用该选项的时Nmap永远不对目标ip地址作反向域名解析)
   ```shell
   #-n
   nmap -n 127.0.0.1
   ```

- -R 反向解析域名(使用该选项的时候Nmap永远对目标ip地址作反向域名解析)
   ```shell
   #-R
   nmap -R -sL 127.0.0.1
   ```

- --system-dns
   ```shell
   #--system-dns 使用系统域名解析器(如果你希望使用系统自带的解析器，就制定该选项(通过getnameinfo()调用一次解析一个IP)
   nmap --system-dns 127.0.0.1 127.0.0.2

- -sL列表扫描
   ```shell
   nmap -sL 127.0.0.1
   ```

- -sL
   ```shell
   #禁止反向域解折（使用该选项的时候Nmap不对目标ip地址作反向城名解机）
   nmap -n -sL 127.0.0.1
   ```

- -6 扫描IPV6地址
   ```shell
   #-6
   nmap -6 fe80::d920:6c18:1f7f:3d7c
   ```

- --traceroute
```shell
   #--traceroute 路由跟踪(使用--traceroute选项即可进行路由追踪)使用路由追踪功能可以帮助用户了解网络的同行情况,通过此选项可以轻松地查出从计算机到目标之间所经过的网络节点,并可以看到通过各个节点的时间.
   nmap --traceroute -v 127.0.0.1
```

- -PY
```shell
# -PY SCTP INIT Ping扫描（通过向目标发送INIT包,根据目标主机的相应判断目标主机是否存活)
nmap-PY -v 127.0.0.1
```

#### 探索网络

- -T
  - -T 时序选项
  ```shell
  nmap -T0 127.0.0.1
  nmap -T1 127.0.0.1
  ```

  - T0-T5：使用的是一种快速扫描的方式，扫描速度的级别范围在（T0-T5）之间，级别越高，扫描越快。
    - -T0(编执的)丰常慢的扫描,用于1DS逃避。
    - -T1(史崇的)缓慢的扫描,用于IDS逃避。
    - -T2（文雅的)降低速度以降低对带宽的消耗此选项一般不常用.
    - -T3(普通的)：默认,根据目标的反应自动调整时间，
    - -T4(野蜜的)快速扫描,常用扫描方式,需萝在很好的网络坏境下进行扫描,请求可能会淹没目标.
    - -T5(疯狂的)急速扫描,这种扫描方式以钙性准确度来提升扫描速度.

- -p
  - -p 常用扫描方式(-p指定扫描端口如80,1433,1521,3306,3389等等）
  ```shell
  nmap -p 3389 127.0.0.1
  #对所有的65535个端口扫描，可以使用参数 -p “*”
  nmap -p “*” 127.0.0.1
  ```
  - -F 选项 使用该选项可以快速扫描端口,但并不是所有端口都会扫描,只会扫描有限的端口,在Nmap中nmap-services包含了默认扫描的端口,也可以用--datadir选项指定自己的nmap-services文件
  - --top-ports选项
  ```shell
  nmap --top-ports 100 127.0.0.1 (输出结果扫描100个使用率最高的端口)
  ```
- 使用TCP协议进行主机发现（-sS -sT）
TCP协议的主要过程由三次握手构成：主动端先发送SYN报文，被动端回应SYN+ACK报文，然后主动端再回应ACK。利用这个过程，Nmap向目标发送SYN报文，如果对方回应了SYN+ACK，则说明目标在线。
由于三次握手最后一步的意义不大，所以扫描时，这一步可以完成也可以不完成，如果完成的话称之为全开(放)扫描，不完成则叫半开（SYN）扫描
  - -sS
    - -sS TCP SYN扫描(半开)
    ```shell
    nmap -sS 127.0.0.1
    ```
  - -sT
    - -sT TCP 连接扫描（全开）
    ```shell
    nmap -sT 127.0.0.1
    ```
- UDP相比于TCP协议简单，但是扫描主机时，并不如TCP协议方便，而且花费的时间很长，这种扫描方式并不常用 
  - -sU
    - -sU UDP扫描
    ```shell
    nmap -sU -D 80-500 127.0.0.1
    ```
- -sN;-sF;-sX
    - -sN;-sF;-sX 隐蔽扫描
      - -sN是Null扫描,是通过发送非常规的TCP通信数据包对计算机进行探测
      ```shell
      nmap -sN 127.0.0.1
      ```
    - -sF是FIN扫描,当我们使用TCP 
    ```shell
    #SYN扫描时可能会被目标主机的防火墙发现并阻止
    #SYN数据包使用TCP 
    #FIN扫描方式会有很好的穿透效果
    nmap -sF 127.0.0.1
    ```
    - -sX是Xmas扫描
    ```shell
    nmap -sX 127.0.0.1
    ```
- -sA
  - -sA TCP ACK扫描
  ```shell
  nmap -sA -v 127.0.0.1
  ```
- -sW
  - -sW TCP窗口扫描
  ```shell
  nmap -sW -V -F 127.0.0.1
  ```
- -sM  
  - -sM TCP Maimon扫描
  ```shell
  nmap -sM -T4 127.0.0.1
  ```
- --scanflags
  - --scanflags 自定义TCP扫描(--scanflags选项可以是一个数字标记值)
  ```shell
  nmap -sT --scanflags SYNURG 127.0.0.1
  ```
- -sI
  - -sI 空闲扫描
  ```shell
  nmap -sI 192.168.1.100:80 127.0.0.1
  ```
- -sO
  - -sO IP协议扫描
  ```shell
  nmap -sO -T4 127.0.0.1
  ```
- -b
  - -b FTP Bounce扫描(使用-b选项就可以进行FTP Bounce Scan扫描,它允许用户连接一台FTP服务器,然后要求文件送到一台第三方服务器,这种扫描方式很少被支持,但是也是躲避防火墙的办法〕
  ```shell
  nmap -b 127.0.0.1
  ```

#### 指纹识别与探测
- -sV
  - -sV 版本探测
  ```shell
  nmap -sV 127.0.0.1
  可以借助-A选项进行操作系统探测和版本探测,结果信息更详细和直观
  nmap -sV -A 127.0.0.1
  ```
- --allports
  - --allports 全端口版本探测
  ```shell
  nmap -sV --allports 127.0.0.1
  ```
- --version-intensity
  - --version-intensity 设置扫描强度(赋予的值越高,服务越有可能被正确识别,但是时间
也较长,强度在0~9之间,默认强度是7，0代表最低强度,9代表最高强度）
  ```shell
  nmap -sV --version-intensity 5 127.0.0.1
  ```
- --version-lighte
  - --version-light 轻量级扫描(--version-intensity有0~9的测试等级,--version-
intensity则是对应的--version-intensity 2的快捷方式,轻量级扫描会节省时间,但是准确性会隆低，使用以下选项可以节约部分时间和不会栖牲太多准确性）
  ```shell
  nmap -sV --version-light 127.0.0.1
  ```
- --version-all
  - --version-all 重量级扫描
  ```shell
  nmap -sV --version-all 127.0.0.1
  ```
- --version-trace
  - --version-trace 获取详细版本信息
  ```shell
  nmap -sV --version-trace 127.0.0.1
  ```
- -sR
  - -sR RPC扫描
  ```shell
  nmap -sV -sR 127.0.0.1
  ```
- -O
  - -O 启用操作系统探测
  ```shell
  nmap -O 127.0.0.1
  ```
- --osscan-limit
  - --osscan-limit 对指定的目标进行操作系统检测(该选项仅在使用-O或-A进行操作系统检测时起作用〕
  ```shell
  nmap -O --osscan-limit 127.0.0.1/24
  ```
- --osscan-quess:--fuzzy
  - --osscan-guess;--fuzzy推测系统版本(当无法准确识别的时候,nmap会从最接近数据中取值,大胆的猜测目标系统)
  ```shell
  nmap -O --osscan-guess 127.0.0.1
  ```

#### 伺机而动
- --min-hostgroup
  - --min-hostgroup 调整井行扫描组的大小(nmap默认情況下进行扫描,首先开始扫描较小的组,最小为5,会在最短的时间产生一个想要的结果,随后馒慢增加大小，最大为1024.为了保证效率,会针对UDP或少量端口的TCP扫描）
  ```shell
  nmap --min-hostgroup -30 127.0.0.1/24
  ```
- --min-parallelism
  - --min-parallelism 调整探测报文的并行度
  ```shell
  nmap --min-parallelism 100 127.0.0.1/24
  ```
- --max-parallelism
  - --max-parallelism 调整探测报文的并行度
  ```shell
  nmap --max-parallelism 100 127.0.0.1
  ``` 

- --min-rtt-timeoute
  - --min-rtt-timeout 调整探测报文超时(使用该选项时,规定100毫秒是比较合适的,rtt值不得小于100,也最好不要大于1000毫秒〕
  ```shell
  nmap --min-rtt-timeout 500ms 127.0.0.1
  ```
- --max-rtt-timeout
  - --max-rtt-timeout 调整探测报文超时
  ```shell
  nmap --max-rtt-timeout 500ms 127.0.0.1
  ```

- --initial-rtt-timeout
  - --initial-rtt-timeout 调整探测报文超时
  ```shell
  nmap --initial-rtt-timeout 500ms 127.0.0.1
  ```
- --host-timeoute
  - --host-timeout 放弃低速目标主机(单位是毫秒,一般我们设置为1800000毫秒,保证nmap在对单个主机扫描的时间不会超过半个小时,在半小时后的时间内其他主机也会同时扫描.）
  ```shell
  nmap --host-timeout 100ms 127.0.0.1/24
  ```
- --scan-delay
  - --scan-delay 调整探测报文的时间间隔(该选项可以控制Nmap对一个或多个主机发送探测报文的等待时间 等待时间可以毫秒为单位。）
  ```shell
  nmap --scan-delay 1s 127.0.0.1
  ```
- --max-scan-delay
  - --max-scan-delay 调整探测报文的时间间隔
  ```shell
  nmap --max-scan-delay 30s 127.0.0.1
  ```

#### 防火墙/IDS逃逸
- -f
  - -f报文分段
  ```shell
  nmap -sX -v -F 127.0.0.1(ping扫描目标主机）
  #如果在无法获知目标主机的端口是否开放，此时尝试使用报文分段进行扫描
  nmap -f -v 127.0.0.1
  ```
- --mtu
  - --mtu 指定偏移大小
  ```shell
  nmap --mtu 16 127.0.0.1
  ```
- -D
  - -D IP欺编(IP欺骗的语法如下：Nmap -D [decoy1,decoy2..IRND:number1(目标]）
  ```shell
  (使用-D选项可以指定多个ip地址,或者使用RND随机生成几个地址,在指定的诱饵之间使用逗号进行分割,需要注意的是在进行版本检测或者TCP扫描的时候诱饵是无效的。)
  nmap -D RND:11 127.0.0.1
  ```
  - 随机的方法容易发现,接下来将指定几个I地址对目标实施扫描来达到更好的效果.
  ```shell
  nmap -D 127.0.0.1,127.0.0.2,127.0.0.253 127.0.153.1
  ```
  - 通过抓包的方法看到nmap正在使用我们指定的ip进行对目标主机的扫描,可以使用ME选项指定自己的真实IP
  ```
  nmap -D 127.0.0.1,127.0.0.2,127.0.0.253,ME 127.0.153.1
  ```
- -sI
  - -sI 原地址欺骗(使用-sI选项可以进行源地址欺骗,如果Nmap无法确定你的原地址,Nmap会给出相应的提示,使用-sI选项指定需要发包的接口ip地址）
  ```shell
  nmap -sI xssm.me:80 127.0.0.1
  ```
- --source-porte
  - --source-port 源端口欺骗(使用--source-port选项可以进行源地址欺编,也可以用-g选项,只需要提供端口,nmap就可以从端口发数据）
  ```shell
  nmap --source-port 53 127.0.0.1
  ```
- --data-length
  - --data-length 指定发包长度(使用--datalength可以在发送报文的时候指定发包长度,tcp包是40字节,ICMP Echo有28个字节）
  ```shell
  nmap --data-length 30 127.0.0.1
  ```
- --randomize-hosts
  - --randomize-hosts 目标主机随机排序(使用该选项可以对主机进行随机的排序,最多可达8096个主机,单方面使用这个选项对防火墙/DS逃逸效果不大.配合时间选项会有很好的效果）
  ```shell
  nmap --randomize-hosts 127.0.0.1-200
  ```
- --spoof-mac
  - --spoof-mac MAC地址欺昵
  ```shell
  #使用该选项就可以进行MAC地址欺骗,冒失的指定一个MAC地址会引起管理员怀疑,这是可以用字符串'0'随机分配一个MAC地址,也可以指定一个MAC地址进行欺骗.MAC地址最好是存在的,这样才能起到欺编的效果,使用--spoof-mac选项可以用参数包括0MAC Address, Vendor Name 0表示随机生成一个MAC地址 MAC Address 表示用户手动指定一个MAC地址，Vendor Name表示从指定厂商生成一个MAC地址。
  nmap -sT -PN --spoof-mac 0 127.0.0.1
  ```

#### 信息收集
- -script ip-geolocation-* IP信息收集
  - --script ip-geolocation-*
  ```shell
  nmap --script ip-geolocation-* www.xssm.me
  ```
- whois
  - whois whois查询(查询目标域名whois信息）(有时候whois查询到信息并不准确,我们更热衷于查询历史whois记录)
  ```shell
  nmap --script whois www.xssm.me
  ```
  - 大部分网站启用了whois保护或隐藏电话，姓名等信息,我们可以查询历史whois,例如whois可能还没有启用whois保护，我们可以启用其他几个whois查询脚本
  ```shell
  nmap --script whois --script-args whois.whodb=nofollow www.xssm.me
  ```
  - 如果域名比较多,我们可以使用列表的方式进行查询.
  ```shell
  nmap --sn --script whois -v -iL host.txt
  ```
- http-email-harvest
  - http-email-harvest 搜集E-maill信息(Email查询)
  ```
  nmap --script http-email-harvest www.xssm.me
  ```
- hostmap-ip2hosts
  - hostmap-ip2hosts IP反查
  ```shell
  nmap -sn --script hostmap-ip2hosts www.xssm.me
  ```
- dns-brute
- dns-brute DNS信息搜集(域名系统是因特网的一项服务,他作为将域名和Ip地址相互映射的一个分布式数据库，能够使人更方便的访问互联网,dns使用tcp和udp端口53,当前,对于每一级域名长度的限制是63个字符,域名总长度则不能超过253个字符）
```shell
nmap --script dns-brute www.xssm.me
```
- membase-http-info
  - membase-http-info 检索系统信息
  - 该脚本的默认线程数量是5,如果是扫描一个大型网站,速度可能会较慢,可以设置一下扫描线线程
  ```shell 
  #设置10个线程时相应扫描速度会增加很多
  nmap --script dns-brute dns-brute.threads=10 www.xssm.me    
  #如果需要查询多个域名可以指定一个列表：
  nmap --script dns-brutedns-brute.threads=10,dns-brute.hostlist www.xssm.me.
  ```

- smb-security-mode.nse
  - smb-security-mode.nse 后台打印机服务漏洞
  ```shell
  nmap -p 445 127.0.0.1 --script membase-http-info
  ```

- smb-check-vulns.nse
  - smb-check-yulns.nse 系统漏洞扫描(可以使用U：或者T进行配合,这样会得到意想不到的效果）
  ```shell
  nmap --script smb-security-mode.nse -p 445 127.0.0.1
  ```
- http-stored-xss.nse
  - http-stored-xss.nse 扫描Web漏洞
  ```shell
  nmap -p80 --script http-stored-xss.nse www.xssm.me
  ```
- snmp-win32-services
  - snmp-win32-services 通讨snmp列举Windows服务/账户
  ```shell
  nmap -sU -p 161 --script=snmp-win32-services 127.0.0.1
  ```


- dns-brute
  - dns-brute 枚举DNS服务器的主机名(下面的示例是对baidu.com子域名的枚举）
  ```shell
  nmap --script dns-brute --script-args dns-brute.domain=baidu.com
  #所有有关子域名及服务器都被dns-brute脚本枚举出来,该脚本可以使用"dns-brute.threads=线程“指定线程来加快或减少破解速度 使用dns-brute.hostlist=/hostfile.txt指定一个需要枚举的列表.
  ```

- htto-header/http-sitmap-generator
  - http-header/http-sitmap-generator HTTP信息搜集
  ```shell
  #使用nmap扫描http版本,得知当前版本漏洞,例如Apache,IIS7,Nginx的畸形漏洞在相应的低版本中都会存在.nmap可以非常简单的发泄这些漏洞
  nmap -sV -p 80 www.xssm.me  
  #对目标地址进行HTTP头信息探测
  nmap -p 80 --script=http-headers baidu.com
  #爬行Web目录结构
  nmap -p 80 --script=http-sitemap-generator www.baidu.com
  ```
- ssl-enum-ciphers
  - ssl-enum-ciphers 枚举SSL秘钥
  ```shell
  nmap -p 443 --script=ssl-enum-ciphers www.baidu.com
  ```

- ssh-hostkey
  - ssh-hostkey SSH服务秘钥信息探测(sh-hosts可以查看SSH服务的秘钥信息）
  ```shell
  nmap -p 22 --script ssh-hostkey --script-args ssh hostkey=full 127.0.0.1
  ```

#### 数据库渗透测试
- mysql-databases
  - mysql-databases MYSQL列举数据库(如果目标端口改变需要-p指定相应的端口)
  ```shell
  nmap -p3306 --script mysql-databases --script-args mysqluser=root, mysqlpass 127.0.01

- mysql-variables
  - mysql-variables 列举MYSQL变量(如果目标端口改变组需要-p指定相应的端口）
  ```shell
  nmap -p3306 --script=mysql-variables 127.0.0.1
  ```
- mysql-empty-password
  - mysql-empty-password检查MYSQL权限
  ```shell
  nmap -p3306 --script=mysql-empty-password 127.0.0.1
  #如果无法确定目标开放的端口号,可以用-sV选项进行扫描
  nmap-sV--script=mysql-empty-password127.0.0.1
  ```
- mysql-brute
  - mysal-brute 审计MYSQL密码
  ```shell
  nmap --script=mysql-brute 127.0.0.1
  #该脚本用于MYSQL弱口令,默认查找全部MYSQL端口,也可以用-p指定端口,也可以自定义账号密码字典
  nmap -p 3306 --script=mysql-brute userdb=/root/passdb.txt passdb=/root/pass.txt 127.0.0.1
  ```
- mysql-audite
  - mysal-audit 审计MYSQL安全配置
  ```shell
  nmap -p 3306 --script mysql-audit --script-args "mysql-audit.username='root',mysql-audit.password=,mysql-audit.filename='nselib/data/mysql-cis.audit'" 127.0.0.1
  ```

- oracle-brute
  - oracle-brute 审计oracle密码
  ```shell
  nmap --script oracle-brute -p 1521 --script-args oracle-brute.sid=test 127.0.0.1
  #该脚本暴力破解Oracle密码,但是我们可以用-p指定端口,也可以自定义账号密码字典需要userdb选项指定账号字典passdb指向密码字典
  nmap --script oracle-brute -p 1521 --script-args oracle-brute.sid=test --script-argsuserdb=/tmp/usernames.txt,passdb=/tmp/passwords.txt127.0.0.1
  ```
- ms-sql-brute
  - ms-sql-brute 审计msSQL密码
  ```shell
  nmap -p 1433 --script ms-sql-brute - -script-argsuserdb=name.txt,passdb=pass.txt 127.0.0.1
  ```
- ms-sql-empty-password
  - ms-sql-empty-password 检查msSQL空密码
  ```shell
  nmap -p 1433 --script ms-sql-empty-password 127.0.0.1
  ```
- ms-sql-tables
  - ms-sql-tables 读取msSQL数据
  ```shell
  nmap -p 1433 --script ms-sql-tables-scripts-args mssal.username=sq,mssal.password=sa 127.0.0.1

- ms-sql-xp-cmdshell
  - ms-sql-xp-cmdshell msSQL执行系统命令
  ```shell
  nmap -p 1433 --script ms-sql-xp-cmdshell --script-args mssql.username=sa,mssql.password=sa,ms-sql-xp-cmdshell.cmd="ipconfig" 127.0.0.1
  ```
- pgsql-brute
  - pgsql-brute审计PgSQL密码
  ```shell
  nmap -p 5432 --script pgsql-brute 127.0.0.1
  ```

#### 渗透测试
- http-brute
  - http-brute 南计HTTP身份验证
  ```shell
  nmap --script http-brute -p 80 www.xssm.me
  ```
- ftp-brute
  - ftp-brute 审计FTP服务器
  ```shell
  nmap --script ftp-brute -p 21 127.0.0.1
  #如果上面没有破解成功,需要设置一个账号密码的字典进行破解
  nmap --script ftp-brute --script-args userdb=user.txt,passdb=pass.txt -p 21 127.0.0.1
  ```
- http-wordpress-brute
  - http-wordpress-brute
  ```shell
  nmap -p80 --script http-wordpress-brute 127.0.0.1
  #若是需要自定字典则需要设蛋userdb.passdb诜顶指定相应的字曲
  nmap -p80 --script http-wordpress-brute--script-args userdb=user.txt,passdb=passwd.txt 127.0.0.1
  #还可以设置线程数，减少破解时间  
  nmap -p80 --script http-wordpress-brute --script-args http-wordpress-brute, threads=10 127.0.0.1
  ```
- http-joomla-brute
  - http-joomla-brute 审计joomla程序 
  ```shell
  nmap -p80 --script http-joomla-brute 127.0.0.1
  #自定义账号密码字典,进行高效率的破解。
  nmap -p80 --script http-joomlabrute --script-args userdb=users.txt,passdb=passwords.txt127.0.0.1
  #设置线程让破解更加高效
  nmap -p80 --script http-joomlabrute --script-args userdb=users.txt,passdb=passwords.txt,http-joomla-brute.threads=5 127.0.0.1
  ```
- pop3-brute
  - pop3-brute 审计邮件服务器(如果需要自定义字典需要设置passdb,userdb两个选项指定相应的字典）
  nmap-p110 --script=pop3-brute 127.0.0.1 
- smb-brute.nse 
  - smb-brute.nse 审计SMB口令
  ```shell
  nmap --script smb-brute.nse -p445 127.0.0.1
  可以使用passdb选项指向一个自定义字典
  nmap --script smb-brute.nse --script-args passdb=pass.txt -p445 127.0.0.1
  ```
- vnc-brute
  - vnc-brute 审计vnc服务器(如果需要自定义宇典需要设置passdb、userdb两个选项指定相应的字典）
  ```shell
  nmap --script vnc-brute -p 5900 127.0.0.1
  ```
- smtp-brute
  - smtp-brute 审计SMTP服务器
  ```shell
  nmap -p 25 --script smtp-brute 127.0.0.1
  ```
- smtp-enum-users
  - smtp-enum-users 宙计SMTP服务器
  ```shell
  #若要进行邮件的接收与发送则需要有对应的邮箱账户,通过VRFY,EXPN,或RCPT命令可以枚举邮箱用户 ,在nmap的脚本中smtp-enum-users则可以通过枚举远程系统所有的用户
  nmap -p 25 --script=smtp-enum-users.nse smtp.xx.com
  ```
- stuxnet-detect
  - stuxnet-detect 检测Stuxnet壖虫
  ```shell
  nmap --script stuxnet-detect -p 445 127.0.0.1
  ```
- snmp-netstat
  - snmp-netstat SNMP服务安全审计(获取目标主机网络连接状态）
  ```shell
  nmap -sU -p 161 --script=snmp-netstat 127.0.0.1
  ```
- snmp-processes
  - snmp-processes SNMP服务安全审计(snmp-processes脚本可以通过SNMP服务协议枚举运行的系统进程）
  ```shell
  nmap -sU -p 161 --script=snmp-processes 127.0.0.1
  ```
- snmp-win32-services
  - snmp-win32-services SNMP服务安全审计(snmp-win32-services脚本可以获得Windows服务器的服务）
  ```shell
  nmap -sU -p 161 --script=snmp-win32-services 127.0.0.1
  ```
- snmp-brute
  - snmp-brute SNMP服务安全审计(snmp-brute可以对目标服务器的snmp服务进行口令审计)
  ```shell
  nmap -sU -p 161 --script=snmp-brute 127.0.0.1
  ```

#### Nmap技巧
- --send-eth-
  - --send-eth 发送以太网数据包
  ```shell
  nmap --send-eth 127.0.0.1
  ```
- --send-ip
  - --send-ip 网络层发送
  ```shell
  nmap --send-ip 127.0.0.1
  ```
- --privileged
  - --privileged 假定拥有所有权
  ```shell
  nmap --privileged 127.0.0.1
  ```
- --interactive
  - --interactive 在交互模式中启动
  - --interactive告诉nmap在交互模式中启动,这时nmap会提供交互横式,便于扫描
  ```shell
  nmap --interactive && n -T4 127.0.0.1
  ```
- -V
  - -V 查看Nmap版本号(使用-V选项或者--version选项查看nmap的版本信息）
  ```shell
  namp-V
  ```
- -d
  - -d 设置调试級别(使用-d选项设置调试级别,可选有1~9,-d 9是最高级别,这时候产生的数据会非常多）
  ```shell
  nmap -d 1 127.0.0.1
  ```
- --packet-trace
  - --packet-trace 跟踪发送接受的报文-
  ```shell
  nmap --packet-trace -p 20-30 127.0.0.1
  ```
- --iflist
  - --iflist 列举接口和路由
  ```shell
  nmap --iflist 127.0.0.1
  ```
- -e
  - -e指定网络接口
  ```shell
  namp -e eth0 127.0.0.1
  ```
- -oG
  - -oG 继续中断扫描(使用-oG将扫描结果保存为TXT,然后在扫描过程中按下Ctrl+C终止扫描）
  ```shell
  nmap --oG 1.txt -y 192.168.1.1/24
  #使用--resume选项继续扫描.
  nmap --resume 1.txt
  ```
- firewalk
  - firewalk 探测防火墙
  ```shell
  nmap --script=firewalk --traceroute 127.0.0.1
  ```
- vmauthd-brute
  - vmauthd-brute VMWare认证破解
  ```shell
  nmap -p 902 --script vmauthd-brute 127.0.0.1
  ```

#### Nmap保存和输出
- -oN
  - oN 标准保存
  ```shell
  nmap -F -oN test1.txt 127.0.0.1
  ```
- -oX
  - -oX XML保存
  ```shell
  nmap -F -oX test1.xml 127.0.0.1
  ```
- -oS
  - -oS 133t保存
  ```shell
  nmap -F -oS test1.txt 127.0.0.1
  ```

- -oG
  - -oG Grep保存
  ```shell
  nmap -F -oG test1.txt 127.0.0.1
  ```
- -oA
  - -oA 保存到所有格式
  ```sehll
  nmap -F -oA testA 127.0.0.1
  ```
- --append-output
  - --append-output 补充保存文件
  ```shell
  nmap -F --append-output -oN test1.txt 127.0.0.1
  ```
- -oX
  - -oX 转换XML保存(--stylesheet可以将XSL样式表转为XML保存）
  ```shell
  nmap -F -oX testB.xml--stylesheethttp://www.insecure.org/nmap/data/
  nmap.xsl127.0.0.1
  ```
- --oX
  - --oX 忽路XML声明的XSL样式表(--no-styleshee选项禁止nmap的XML保存关联任何XSL样式表）
  ```shell
  nmap -oX testC.xml --no-stylesheet 127.0.0.1
  ```