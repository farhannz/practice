#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
int main()
{
  srand(time(NULL));
  FILE *fp,*fa;
  fp = fopen("test.txt","a+");
  fa = fopen("a.txt","a+");
  char username[255],password[32];
  printf("Username : ");
  scanf(" %s",username);
  printf("Password : ");
  scanf(" %[^\n]s",password);
  int size = strlen(password),key[255],adder[255];
  char hashed[255];
  int i,n,x;
  int cases[2] = {97,65};
  for(i = 0;i<size;i++)
  {
    n = rand()%1000+2;
    x = rand()%2;
    hashed[i] = (password[i] + n)%26+cases[x];
    key[i] = n;
    adder[i] = x;
  }
  fprintf(fp,"%s,%s\n",username,hashed);
  for(i = 0;i<size;i++)
  {
    fprintf(fa,"%d,%d",key[i],adder[i]);
    if(i<size-1)fprintf(fa,",");
  }
  fprintf(fa,"\n");
  fclose(fp);
  fclose(fa);
  return 0;
}
