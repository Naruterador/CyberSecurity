// SearchJmpEspInUser32.cpp
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
  BYTE *ptr;
  int position;
  HINSTANCE handle;
  bool done_flag = FALSE;
  // 载入kernel.dll
  handle = LoadLibrary("kernel32.dll");
  if (!handle) {
    printf("load dll error!");
    exit(0);
  }
  ptr = (BYTE *)handle;
  for (position = 0; !done_flag; position++) {
    try {
      // jmp esp语句的机器码为 FFE4，所以这里要这么写；
      if (ptr[position] == 0xFF && ptr[position + 1] == 0xE4) {
        int address = (int)ptr + position;
        printf("opcode found at 0x%x\n", address);
      }
    } catch (...) {
      int address = (int)ptr + position;
      printf("end of 0x%x\n", address);
      done_flag = true;
    }
  }
  getchar();
  return 0;
}
