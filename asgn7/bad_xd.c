#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<ctype.h>
int main(int argc,char **argv){int f;if(argc == 1){f=STDIN_FILENO;}else if(argc == 2) {f=open(argv[1], O_RDONLY);if(f<0)return 1;}else return 1;unsigned char b[16];size_t o=0;while(1){ssize_t j=0;while(j<16){ssize_t n=read(f,b+j,16-j);if(n<0){if(f!=STDIN_FILENO)close(f);return 1;}if(n==0)break;j+=n;}if(j==0)break;printf("%08zx: ",o);for(int i=0;i<16;i++){i<j?printf("%02x",b[i]):printf("  ");if(i%2==1)printf(" ");}printf(" ");for(int i=0;i<j;i++){unsigned char c=b[i];printf("%c",isprint(c)?c:'.');}printf("\n");o+=j;}if(f!=STDIN_FILENO)if(close(f)<0)return 1;return 0;}
