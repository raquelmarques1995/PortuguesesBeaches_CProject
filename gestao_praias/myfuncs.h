#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
#define MAX 1024
void getstr(char str[],size_t len)
{
    char buffer[MAX];
    fgets(buffer,MAX,stdin);
    buffer[strcspn(buffer,"\n")]='\0';
    if(strlen(buffer)<len)
        strcpy(str,buffer);
    else{
        strncpy(str,buffer,len-1);
        strcat(str,"\0");
    }
}

int getint(){
    char buffer[MAX];
    fgets(buffer,MAX,stdin);
    return atoi(buffer);
}

void strupper(char *str){
    for(int i=0;str[i];i++)
        str[i]=toupper(str[i]);
}
void strlower(char str[]){
    for(int i=0;str[i];i++)
        str[i]=tolower(str[i]);
}


bool strstrcase(char *str1,char *str2){
    char aux1[strlen(str1)+1];
    char aux2[strlen(str2)+1];
    strcpy(aux1,str1);
    strcpy(aux2,str2);
    strupper(aux1);
    strupper(aux2);
    if(strstr(aux1,aux2)!=NULL)
        return true;
    else
        return false;
}


