#include <iostream>
#include <time.h>

struct Spusok{
	char * text;
	Spusok * link;
};
Spusok *begin, *end;
int n;
void CreateFile(){
	FILE *file=fopen("file.txt","w");
	for(int i=0;i<n;i++) 
	{
		for(int j=rand()%8+1;j<10;j++)
			fprintf(file,"%c",(char)(rand()%26+65));
		fprintf(file,"\n");
	}
	fclose(file);
}
void AddElement(char * value){
	Spusok *p=new Spusok;
	p->text=value;
	p->link=NULL;
	(!end?begin=p:end->link=p);
	end=p;
}
void CreateQueueFromFile(){
	FILE *file=fopen("file.txt","r");
	for(int i=0;i<n;i++)
	{
		char * temp = new char[11];
		fscanf(file,"%s",temp);
		AddElement(temp);
	}
	fclose(file);
}
void Sort(){
	for(int k=0;k<n-1;k++)
	{
		Spusok *p=begin;
		for(int i=0;i<n-k-1;i++,p=p->link)
			if(strcmp(p->text,p->link->text)>0)
			{
				char * temp = p->text;
				p->text = p->link->text;
				p->link->text = temp;
			}
	}
}
void WriteQueueToFile(){
	FILE *file=fopen("file.txt","w");
	for(Spusok *p=begin;p;p=p->link)
		fprintf(file,"%s\n",p->text);
	fclose(file);
}
void FreeMemory(){
	Spusok *p=begin->link;
	delete[] begin->text;
	delete begin;
	begin = p;
	if(p) FreeMemory();
}
int main(){
	srand(time(NULL));
	begin=NULL;
	end=NULL;
	std::cout<<"Enter count of words:\n";
	std::cin>>n;
	CreateFile();
	CreateQueueFromFile();
	Sort();
	WriteQueueToFile();
	if(n>0)FreeMemory();
	return 0;
}