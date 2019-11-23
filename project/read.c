#include<stdio.h>
#include<string.h>

int main()
{
  FILE *fa,*fp;
  fa = fopen("a.txt","r");
  fp = fopen("test.txt","r");
  char username[255],password[255],hashed[255],passInput[255],usrInput[255],buffer[510];
  printf("Username : ");
  scanf("%s",usrInput);
  int key[255]= {0};
  int cases[2] = {97,65},i,j;
  int usrStat = 0,line = 1;
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
    int comma = 0,k = 0,a =0,len;
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
    for(;i<strlen(passInput) && i<x;i++)
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
  }
  else
  {
    printf("Username/Password is incorrect.\n");
  }
  fclose(fa);
  fclose(fp);
  return 0;
}
