#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
void create(FILE*fa,FILE*fp)
{
  char username[255],password[32];
  printf("===================== CREATE ====================\n");
  printf("Username : ");
  scanf(" %s",username);
  int usrStat = 0;
  char buffer[255];
  while(fgets(buffer,255,fp) && usrStat == 0)
  {
    if(strstr(buffer,username) !=NULL) usrStat = 1;
  }
  rewind(fp);
  if(usrStat == 0)
  {
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
  }
  else
  {
    printf("Username has already been taken!\n");
    rewind(fp);
  }
}
void login(FILE*fa,FILE*fp,int * logIn)
{
  printf("===================== LOGIN ====================\n");
  char username[255],password[255],hashed[255],passInput[255],usrInput[255],buffer[510];
  printf("Username : ");
  scanf(" %s",usrInput);
  int key[255]= {0};
  int cases[2] = {97,65},i,j;
  int usrStat = 0,line = 1;
  *logIn = 0;
  while(fgets(buffer,510,(FILE*)fp) && usrStat == 0)
  {
    // fgets(buffer,510,(FILE*)fp);
    i = 0;j = 0;
    for(;buffer[i] != ',';i++)
    {
      username[i] = buffer[i];
    }
    username[i] = '\0';
    i++;
    for(j = 0;buffer[i] != '\n';i++,j++)
    {
      hashed[j] = buffer[i];
    }
    hashed[j] = '\0';
    if(strcmp(usrInput,username)==0)usrStat = 1;
    if(usrStat != 1)line++;
  }
  for(i = 0;i<line;i++)
  {
    fgets(buffer,510,(FILE*)fa);
  }
  int passStat = 0,salah = 0;
  do
  {
    printf("Password : ");
    scanf(" %[^\n]s",passInput);
    // fgets(buffer,510,(FILE*)fa);
    int k = 0,len;
    len = strlen(buffer);
    for(i = 0;i<len;i++)
    {
      j = 0;
      char temp[255];
      while(buffer[i] != ',')
      {
        temp[j] = buffer[i];
        ++j;
        ++i;
      }
      temp[j] = '\0';
      int tmp;
      sscanf(temp,"%d",&tmp);
      key[k] = tmp;++k;
    }
    // printf("\n%s %s %s\n",username,hashed,buffer);
    int adder[k],hKey[k],x;
    for(i = 0,j = 0,x=0;i<k;i++)
    {
      if(i%2)
      {
        adder[j] = key[i];
        ++j;
      }
      else
      {
        hKey[x] = key[i];
        ++x;
      }
    }
    i = 0;
    int size = strlen(passInput);
    for(;i<size && i<x;i++)
    {
      char z = (passInput[i] + hKey[i])%26;
      password[i] = z+cases[adder[i]];
      // printf("%c",password[i]);
    }
    password[i] = '\0';
    if(strcmp(password,hashed)==0)passStat = 1;
    // printf("Pasword is incorrect.\n");
    salah++;
  }while(salah < 3 && passStat == 0);
  if(passStat && usrStat)
  {
    printf("Logged In!\n");
    *logIn = 1;
  }
  else
  {
    printf("Username/Password is incorrect.\n");
  }
  rewind(fp);
  rewind(fa);
}
int main()
{
  int logIn = 0;//status of succes logging in or not;
  int *lPtr = &logIn;
  FILE *fp,*fa;
  fp = fopen("test.txt","a+");
  fa = fopen("a.txt","a+");
  char choose;
  do
  {
    printf("===================================\n");
    printf("1. Create account.\n");
    printf("2. Log In.\n");
    printf("0. Quit.\n");
    printf("Choose : ");
    scanf(" %c",&choose);
    switch (choose) {
      case '1':
        create(fa,fp);
        break;
      case '2':
        rewind(fa);
        rewind(fp);
        login(fa,fp,lPtr);
        break;
      default:
        break;
    }
    printf("\n");
  }while(choose != '0' && logIn == 0);
  fclose(fp);
  fclose(fa);
  return 0;
}
