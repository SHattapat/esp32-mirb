#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "rom/uart.h"
#include <unistd.h>
#include <string.h>
/* nvs init is necessary to use wifi */
#include "nvs_flash.h"

#undef getchar
#define getchar uart_getchar

#define STATE_NML 0x00
#define STATE_ESC 0x01
#define STATE_CSI 0x02

int count = 0;
static char *arr[100] = {"0","1","2", "3","4","5", "6","7","8", "9","10","11", "12"};
uint8_t **ptr = arr;
_sig_func_ptr
signal(int sig, _sig_func_ptr func)
{
  return SIG_ERR;
}

static void
echo_rewrite(const uint8_t *s, size_t n, int cursor) {
  //printf("\nS : %s \n",s);
  //printf("N : %zu \n",n);
  //printf("C : %d \n",cursor);
  //printf("1");
  printf("\e[3G\e[J");
  printf("%.*s ", n, s);
  
  if (n && s[n-1] != '\n') {
    //printf("2");
    printf("\e[%dG",3 + cursor);
    //printf("echo_rewrite_IO");
  }
   //printf("TESTT");
  fflush(stdout);
}
static void
Test_enter(const uint8_t *t,int cout,size_t n){
  //char *arr[] = {"0","1","2", "3","4","5", "6","7","8", "9","10","11", "12"};
  //static char *arr[100] = {"0","1","2", "3","4","5", "6","7","8", "9","10","11", "12"};

  // copying str1 to str2
  
  //printf("Enter B result 0:%s\n", arr[0]);
  //printf("Enter B result 1:%s\n", arr[1]);
  //printf("Enter B result 2:%s\n", arr[2]);
  //printf("Enter B result 3:%s\n", arr[3]);
  //printf("Enter B result 4:%s\n", arr[4]);
  //char  s = "TEST";
  ptr[cout] = t;
  for (int i = 0; i < 10; i++ )
        printf(" %d Cout %s  PT:%p \n",cout,ptr[i],ptr[i]);
        //printf("SAVE : %.*s  \n",n,t);

  
  //strcpy(arr,t);
  //arr[cout] = t; 
  //printf("Enter  %d result :%s\n",cout, ptr[cout]);
  //printf("Enter  %d result 1:%s\n",cout, ptr[1]);
  //printf("Enter  %d result 2:%s\n",cout, ptr[2]);
  //printf("Enter  %d result 3:%s\n",cout, ptr[3]);
  //printf("Enter  %d result 4:%s\n",cout, ptr[4]);
}
static void 
appendToString(const uint8_t *t, size_t tLength, char *string) {
    // Find the length of the existing string
    size_t stringLength = strlen(string);
    
    // Iterate over the `t` array and convert each uint8_t value to a character
    for (size_t i = 0; i < tLength; i++) {
        char c = (char)t[i];
        
        // Append the character to the existing string
        string[stringLength + i] = c;
    }
    
    // Null-terminate the string after the appended characters
    string[stringLength + tLength] = '\0';

}
static int
uart_getchar(void)
{
  static size_t n = 0;
  static uint8_t buf[1024];
  static uint8_t last = 0;
  uint8_t c, s = STATE_NML;
  int v = 0, cursor = 0;
  uint8_t  out_arr ;

  //static char *arr[100] = {"0","1","2", "3","4","5", "6","7","8", "9","10","11", "12"};
  
  uint8_t  datain = STATE_NML;
  int countTo = 0;
  

  if (n) 
  {
    c = buf[0];
    //printf("Test buf: %s \n",buf);
    //printf("Test c: %s \n",c);
    memmove(buf, buf + 1, --n);
    return (int)c;
  }
  do
  {
    c = uart_rx_one_char_block(); // input buttom
    if (last == '\r' && c == '\n') 
    {
      continue;
    }
    last = c;
    if (c == '\b' || c == 0x7f) {
      
      if (n && cursor) {
        //printf("1 BS \n");
        //printf("1 buf %s\n",buf);
        //printf("1 cursor %d\n",cursor);
        //printf("1 n %d\n",n);
        //printf("1 C %d\n",c);
        //memmove(buf + (cursor - 1), buf + cursor, n - cursor);
        --n, --cursor;

        //printf("2 BS \n");
        //printf("2 buf %s\n",buf);
        //printf("2 cursor %d\n",cursor);
        //printf("2 n %d\n",n);
        //printf("2 C %d\n",c);
        echo_rewrite(buf, n, cursor);
      }

      
      continue;
    }
    if (c == '\e') /////////////// ESC
    {
      s = STATE_ESC; // <---New S = STATE_ESC 0x01
      //printf("ESC \n");
      continue;
    }

    if (c == '\r') ///// new line
    {
      //char string[20] = "";  // Example string array
      //printf("Enter");
      //printf("\nEnter S >>> %s \n",buf);
      count += 1 ;
      //printf("Enter count %d \n",count);
      //datain = buf ;
      //out_arr = buf;
      //memmove(datain, buf, 10 );
      //strcat(arr, datain);
      //arr[count] = buf ;
      
      //printf("  bus: %s\n",buf);

     

      //Test_enter(buf,count,n);

      //appendToString(buf, sizeof(buf), string);
    
      //printf("%s\n", string);  // Output: Hello, Hello
      //data_in = arr[count];

      //printf("Enter result :%s:\n", buf);
      c = '\n';

    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // printf("s:%d",s);

    switch (s) 
    {
      //printf("s:%d \n",s);
    case STATE_ESC: // = 0x01
                    // TEST STATE_CSI <<<<<<<<<<<<<<<<<<<<<<<<<<<<=======================||||||||||
      //printf("case STATE_ESC :%d \n", s);

      if (c == '[') 
      {
        //printf(" case '[' \n");
        s = STATE_CSI; // <---New S = STATE_CSI 0x02 |
        v = 0;
      }
      else
      {
        //printf(" STATE_NML; = 0x00 \n");
        s = STATE_NML; // = 0x00 if no key pressed.
      }
      continue;

    case STATE_CSI:
      //printf(" STATE_CSI = 0x02 \n");
      switch (c) {
      case '0'...'9':
        //printf(" case 0..9 \n");
        //printf("AF V:%d",v);
        //printf(" AF C HEX: 0x%x\n",c);
        v = (v * 10) + (c - '0');
        //printf("BF V:%d",v);
        //printf(" BF C HEX: 0x%x\n",c);
      case ';':
        //printf(" case ; \n");
        v = 0;
      
      case 'A'...'z':
        //printf("B case\n");
        switch (c) {
        case 'C':
          //printf("test....C\n");
          if (!v) {
            v = 1;
          }
          if (n - cursor < v) {
            v = n - cursor;
          }
          cursor += v;
          //printf("Move right\n");
          echo_rewrite(buf, n, cursor);//////////////////////////////////////// 2
          break;

        case 'A':
          if (!v) 
          {
              v = 1;
           }
          countTo += 1 ;
          //printf("countTo %d ",countTo);
          //printf("Move UP\n");
          /*
          printf("\e[3G\e[J");
          printf("%.*s ", n, s);
  
          if (n && s[n-1] != '\n') {
    
          printf("\e[%dG",3 + cursor);
          //printf("echo_rewrite_IO");
          }
           */

          //printf("Pre result :%s | %d \n", arr[countTo],countTo);

         static uint8_t t[] = { 72, 101, 108, 108, 111 };  // Static array of uint8_t values
         char string[20] = "Hello, ";  // Example string array
         appendToString(t, sizeof(t), string);
         //printf("\e[3G\e[J");
         //printf("%.*s",10, string);  // Output: Hello, Hello
         //fflush(stdout);

          //out_arr = arr[countTo];
          //printf("out_arr %d \n",out_arr);11
          //printf(" %d Cout %s  PT:%p \n",arr[]);
          echo_rewrite(t,10 , cursor);//////////////////////////////////////// test
          break;

        case 'B':
          if (!v) 
          {
              v = 1;
          }
          countTo -= 1 ;
          //printf("countTo %d ",countTo);
          //printf("Move Down\n");
          echo_rewrite(buf, n, cursor);//////////////////////////////////////// test
          break;
        
        case 'D':
          if (!v) {
            v = 1;
          }
          if (cursor < v) {
            v = cursor;
          }
          cursor -= v;
          //printf("Move left\n");
          echo_rewrite(buf, n, cursor);/////////////////////////////////////////////// 3
          break;
          
        }
      default:
        s = STATE_NML; // = 0x00 if no key pressed.
      }
      continue;
    }
    //printf("Test.1");
    if (c != '\n') 
    {
      //char str2[] = "";
      
      memmove(buf + (cursor + 1), buf + cursor, n - cursor);
      //memmove(buf, buf + cursor, n - cursor);
      //printf("\n   | HEX: 0x%x\n",c);
      //printf("cursor:%d\n",cursor);
      buf[cursor] = c;
      ++n, ++cursor;
      //printf("++%d %d\n",n,cursor);
    } 
    else 
    {
      buf[n++] = c;
      cursor = n;
      //printf("  bus: %s\n",buf);
     
      //printf("  C2d: 0x%d\n",c);
      
      //printf("  C2u: 0x%u\n",c);
      //printf("  C2x: 0x%x\n",c);
      //printf("b+%d %d\n",n,cursor);
    }
    
    //printf("P4");
    echo_rewrite(buf, n, cursor);/////////////////////////////////////////// 4

  } 
 while (c != '\n');
  return uart_getchar();
  //return 0; SHattapat
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

void
app_main()
{
  /* nvs init is necessary to use wifi */
  //static uint8_t t[] = { 72, 101, 108, 108, 111 };  // Static array of uint8_t values
  //char string[20] = "Hello, ";  // Example string array
    
  //appendToString(t, sizeof(t), string);
    
  //printf("%s\n", string);  // Output: Hello, Hello
  printf("Welcome... To ESP32-MIRB \n");   
  /*int k = 0;
    for (int i = 0; i <= 50; i++) {
        printf("Progress :%d%% [\033[K", k);
        for (int j = 0; j < i; j++) 
        {
            putchar('W');
        }
        
        usleep(100000); // sleep for 100 milliseconds
        printf("]");
        fflush(stdout); // flush the output buffer
        printf("\r"); // return the cursor to the beginning of the line
        k = k+2;
    }
    
    printf("    Done!\n");
    //fflush(stdout); // flush the output buffer
  */

  /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %d chip with %d CPU cores, WiFi%s%s, ",
            EXPR_FNAME,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("starting now . . . \n");
    fflush(stdout);
    


  nvs_flash_init();
  xTaskCreate(&mirb_task, "mirb_task", 16384, NULL, 5, NULL);//16384
}
