#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#define BUF_LEN 80

int main()
{
    int file_desc;
    int ret_val;
    char tmp[BUF_LEN] = {0};
    
    //system("make -C ../../../gpio_driver | sudo insmod ../../../gpio_driver/gpio_driver.ko | sudo mknod /dev/gpio_driver c 243 0 ");

    file_desc = open("/dev/gpio_driver", O_RDWR);

    if(file_desc < 0)
    {
        printf("Error, file not opened\n");
        return -1;
    }

    while(tmp[0]!='F')
    {
        ret_val = read(file_desc, tmp, BUF_LEN);
        printf("%s",tmp);
    }
    
    if(tmp[0]=='F')
    {
      printf("KRAJ ,TVOJ REZULTAT JE %s,VRATI SWITCHEVE U POCETNI POLOZAJ\n",tmp);

    }
    close(file_desc);
    //system("sudo rmmod gpio_driver | sudo rm /dev/gpio_driver ");
    getchar();
    return 0;
}
