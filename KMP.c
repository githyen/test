#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void output(char *pat);

void fail(char *pat)
{
  int n=strlen(pat);
  int arr[n];
  arr[0]=-1;
  
  for(int j=1; j<n; j++){
   int i=arr[j-1];
		while(pat[j]!=pat[i+1]&&i>=0) i=arr[i];
			if(pat[j]==pat[i+1]) arr[j]=i+1;
			else arr[j]=-1;
		}
	printf("f     ");
  for(int i=0; i<n; i++)
	  printf("%3d",arr[i]);
}
int match(const char *txt, const char *pat)
{
	int pt=1,pp=0;
	int arr[1024];

	arr[pt]=0;

	while(pat[pt]!='\0')
	{
		if(pat[pt]==pat[pp]) arr[++pt]=++pp;
		else if(pp==0) arr[++pt]=pp;
		else pp=arr[pp];
	}

	pt=pp=0;
	while(txt[pt]!='\0' && pat[pp] !='\0'){
		if(txt[pt]==pat[pp]) { pt++; pp++; }
		else if(pp==0) pt++;
		else pp=arr[pp];
	}

	if(pat[pp]=='\0')
		return pt-pp;
	return -1;
}

int main(){

	char fname[20];
	scanf("%s",fname);
	FILE *fp=NULL;

	fp=fopen(fname,"w+");
	if(fp==NULL)
	{
		fprintf(stderr,"file open error \n");
		exit(1);
	}
	char buf[1024];
	
	scanf("%s",buf);
	fwrite(buf,sizeof(char),strlen(buf),fp);
	fseek(fp,0,SEEK_SET);

	fgets(buf,1024,fp);
	
	char pat[1024];
	scanf("%s",pat);
	
	printf("\n\nfailure function\n");
	output(pat);
	fail(pat);
	int mat=match(buf,pat);
	
	if(mat==-1)
	{
		printf("\nthe pattern %s is not found \n",pat);
	}
	else
		printf("\nthe pattern %s is found at the position %d \n",pat,mat);

	exit(0);
}
void output(char *pat)
{
	printf("\n");
	printf("j     ");

	for(int i=0; i<strlen(pat); i++)
		printf("%3d",i);

	printf("\n");
	printf("pat   ");
	for(int i=0; i<strlen(pat); i++)
	printf("%3c",pat[i]);

	printf("\n");
}

