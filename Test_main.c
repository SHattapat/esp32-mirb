#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "rom/uart.h"
#include <unistd.h>
/* nvs init is necessary to use wifi */
#include "nvs_flash.h"

#undef getchar
#define getchar uart_getchar

#define STATE_NML 0x00
#define STATE_ESC 0x01
#define STATE_CSI 0x02

_sig_func_ptr
signal(int sig, _sig_func_ptr func)
{
  return SIG_ERR;
}

static void
echo_rewrite(const uint8_t *s, size_t n, int cursor)
{ ///////////////////////////////////////////////////////////////////// 0
  // char str2[] = "";
  /*
   int i;
     for (i = 0; i <= 100; i++) {
         printf("\rProcessing: %d%%", i);
         fflush(stdout);
         usleep(100000);
     }
     printf("\r%s\rDone!", "                      ");
   */

  // printf("\e[3G\e[J");
  // printf("%s",s);
  // printf(" \e\r>  %.*s", n, s); //n number of range
  printf(" \e\r> %.*s", n, s); // n number of range

  // printf("\r\33>");
  // printf("\r");
  // memmove(s, str2, sizeof(str2));
  // printf("%d", n);
  // printf("TESTT");
  // if (n && s[n-1] != '\n') {
  // printf("\e[%dG", 3 + cursor);
  //}
  fflush(stdout);
}

static int
uart_getchar(void)
{
  static size_t n = 0;
  static uint8_t buf[1024];
  static uint8_t last = 0;
  uint8_t c, s = STATE_NML;
  int v = 0, cursor = 0;

  if (n)
  {
    c = buf[0];
    // printf("Check1 : %d",c);
    // printf("Test");
    memmove(buf, buf + 1, --n);
    return (int)c;
  }
  do
  {
    c = uart_rx_one_char_block(); // input buttom
    // printf("Check1 : %d",c);
    if (last == '\r' && c == '\n')
    {
      continue;
    }
    last = c; // Get buttom
    // printf("Check2 : %d",c);
    if (c == '\b' || c == 0x7f)
    { /// Del char
      if (n && cursor)
      {
        // printf("+1 :%d %d ",n,cursor);
        memmove(buf + (cursor - 1), buf + cursor, n - (cursor));
        --n, --cursor;
        // printf("+2 :%d %d ",n,cursor);
        // printf("\t  ");
        printf("\r%s\r", "                                                                                         ");
        // printf("++%d %d\n",n,cursor);
        echo_rewrite(buf, n, cursor); /////////////////////////////////////////////////////// 1 Del
      }
      // printf("P1");
      continue;
    }
    if (c == '\e') /////////////// ESC
    {
      s = STATE_ESC; // <---New S = STATE_ESC 0x01
      printf("ESC");
      continue;
    }

    if (c == '\r') ///// new line
    {
      // printf("Enter");
      c = '\n';
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // printf("s:%d",s);

    switch (s)
    {
      // printf("s:%d",s);

    case STATE_ESC: // = 0x01
                    // TEST STATE_CSI <<<<<<<<<<<<<<<<<<<<<<<<<<<<=======================||||||||||
      printf("s:%d", s);
      if (c == '[')
      {
        s = STATE_CSI; // <---New S = STATE_ESC 0x02 |
        v = 0;
      }
      else
      {
        s = STATE_NML; // = 0x00
      }
      continue;

    case STATE_CSI:           // = 0x02 <-------------|
      printf("STATE_CSI IN"); // TEST STATE_CSI <<<<<<<<<<<<<<<<<<<<<<<<<<<<=======================||||||||||
      switch (c)
      {
        printf("c:%d\n", c);
      case '0' ... '9':
        printf("//////////////////////////////////V:%d\n", v);
        v = (v * 10) + (c - '0');
      case ';':
        v = 0;
      case 'A' ... 'z':
        switch (c)
        {
        case 'C':
          if (!v)
          {
            v = 1;
          }
          if (n - cursor < v)
          {
            v = n - cursor;
          }
          cursor += v;
          printf("P2");
          echo_rewrite(buf, n, cursor); //////////////////////////////////////// 2
          break;
        case 'D':
          if (!v)
          {
            v = 1;
          }
          if (cursor < v)
          {
            v = cursor;
          }
          cursor -= v;
          printf("P3");
          echo_rewrite(buf, n, cursor); /////////////////////////////////////////////// 3
          break;
        }
      default:
        s = STATE_NML;
      }
      continue;
    }

    if (c != '\n')
    {
      // char str2[] = "";
      memmove(buf + (cursor + 1), buf + cursor, n - cursor);
      // memmove(buf, buf + cursor, n - cursor);
      printf("   | HEX: 0x%x", c);
      // printf("cursor:%d\n",cursor);
      buf[cursor] = c;
      ++n, ++cursor;
      // printf("++%d %d\n",n,cursor);
    }
    else
    {
      buf[n++] = c;
      cursor = n;
      // printf("  bus: %s\n",buf);

      // printf("  C2d: 0x%d\n",c);

      // printf("  C2u: 0x%u\n",c);
      // printf("  C2x: 0x%x\n",c);
      // printf("b+%d %d\n",n,cursor);
    }

    // printf("P4");
    echo_rewrite(buf, n, cursor); /////////////////////////////////////////// 4

  } while (c != '\n');
  return uart_getchar();
  // return 0; SHattapat
}

#define main mirb_main
#include "../components/mruby/mruby/mrbgems/mruby-bin-mirb/tools/mirb/mirb.c"
#undef main

static void
mirb_task(void *pvParameter)
{
  char *argv[] = {"mirb", NULL};

  mirb_main(1, argv);

  esp_restart();
}

void app_main()
{
  /* nvs init is necessary to use wifi */
  nvs_flash_init();
  xTaskCreate(&mirb_task, "mirb_task", 16384, NULL, 5, NULL); // 16384
}
