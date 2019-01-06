#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#define BUF_LEN 80
int file_desc;
static pthread_mutex_t led_mutex;

void* led_thread(void *param) {
    
  char tmp[BUF_LEN];
  while (1) 
  {
    pthread_mutex_lock(&led_mutex);
    
    // Open file
    file_desc = open("/dev/gpio_driver", O_RDWR);
    if (file_desc < 0) 
    {
        printf("Error, file not opened\n");
        exit(1);
    }

    read(file_desc, tmp, BUF_LEN);

          
    if(tmp[0]=='F')
    {
      printf("KRAJ ,TVOJ REZULTAT JE %s,VRATI SWITCHEVE U POCETNI POLOZAJ\n",tmp);
      pthread_mutex_unlock(&led_mutex);
      return 0;
    }
    else
    {
      printf("");
    }
    close(file_desc);

    pthread_mutex_unlock(&led_mutex);
    
  }

}

int main() {
    system("sudo rmmod gpio_driver | sudo rm /dev/gpio_driver ");
    system("make -C ../../../gpio_driver | sudo insmod ../../../gpio_driver/gpio_driver.ko | sudo mknod /dev/gpio_driver c 243 0 ");
    
    int c0 = 0;
    pthread_t hLed;

    pthread_create(&hLed, NULL, led_thread, (void*)&c0);
    
    //pthread_join(hLed, NULL);
    //pthread_mutex_destroy(&led_mutex);
    getchar();
    return 0;
}

