#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define maxn 1000000
#define maxw 20

typedef struct{
    char flag, num;
    void *m1[26], *pred;
}Trec;

Trec *mas, *m2, *root;

void Insert(char *s){
    Trec *cur = root;
    for(int i=0; *(s+i)!='\0';i++){
        int cm = (int)(*(s+i)-'a');
        if (!((*cur).m1[cm])){
            (*cur).m1[cm] = ++m2;
            (*m2).pred=cur;
        }
        cur = (*cur).m1[cm];
    }
    (*cur).flag=1;
}

int Delete(char *s){
    Trec *cur = root;
    for(int i=0; ;i++){
        if (*(s+i)=='\0')break;
        int cm = (int)(*(s+i)-'a');
        if(!((*cur).m1[cm]))return -1;
        cur = (*cur).m1[cm];
    }
    if (!((*cur).flag))return -2;
    (*cur).flag = 0;
    return 0;
}

Trec* Search(char * s){
    Trec * cur = root;
    for(int i=0; ;i++){
        if (*(s+i)=='\0')break;
        int cm = (int)(*(s+i)-'a');
        if(!((*cur).m1[cm]))return NULL;
        cur = (*cur).m1[cm];
    }
    return cur;    
}
    
char Show(char *p){
    Trec *root0 = Search(p);
    if(!root0)return -1;
    Trec * cur = root0;
    char *s;
    s=(char*)calloc(maxw,sizeof(char));
    int i = 0;
    if ((*cur).flag){
        printf("%s\n",p);
    }
    while (1){

        while((*cur).num <= 25){
            if ((*cur).m1[(*cur).num]){ 
                *(s+i++) = (char)((*cur).num+'a');
                cur = (*cur).m1[(*cur).num++];
                if ((*cur).flag){
                    *(s+i)='\0';
                    printf("%s%s\n",p,s);
                }
            }
            else (*cur).num++;
        }
        (*cur).num=0;
        if (cur==root0)break;
        cur=(*cur).pred;
        i--;
    }
    return 0;
}

char Gen(int nw,int l1,int l2){
	int rad = l2 - l1 + 1;
    if (l1>l2)return -1;
	for(int i=0; i < nw; i++){
        int len = rand() % rad + l1;
        char *str = (char *)malloc(len+1);
        for(int j=0; j<len; j++)
            *(str+j) = rand() % 26 + 'a';
        *(str+len)='\0';
        Insert(str);
        }
	return 0;
	}

char PrintToFile(){
    FILE * fout = fopen("out.txt","w");
    Trec * cur = root;
    char *s;
    s=(char*)calloc(maxw,sizeof(char));
    int i = 0;
    while (1){
        while((*cur).num <= 25){
            if ((*cur).m1[(*cur).num]){ 
                *(s+i++) = (char)((*cur).num+'a');
                cur = (*cur).m1[(*cur).num++];
                if ((*cur).flag){
                    *(s+i)='\0';
                    fprintf(fout,"%s\n",s);
                }
            }
            else (*cur).num++;
        }
        (*cur).num=0;
        if (cur==root)break;
        cur=(*cur).pred;
        i--;
    }
    fclose(fout);
    return 0;
}

int main(){
    char s1,*s2;
    mas = (Trec*)calloc(maxn*maxw,sizeof(Trec));
    m2 = root = mas;
    char f=0;
    printf("Input 'h' for help\n");
    while(f==0){
        printf("%s","Input operation: ");
        scanf("\n%s",s2);
        s1 = *s2;
        switch (s1){
            case 'a':
                scanf("%s",s2);
                Insert(s2);
                printf("String %s inserted\n",s2);
                break;
            case 'g':
                ;
                int wrd,l1,l2;
				scanf("%d %d %d",&wrd,&l1,&l2);
				Gen(wrd,l1,l2);
				printf("%d words were generated\n",wrd);
                break;
            case 'd':
                scanf("%s",s2);
                int r = Delete(s2);
                if(!r)printf("String %s deleted\n",s2);
                else printf("String %s wasn't found\n",s2); 
                break;
            case 's':
                ;
                char * ssh = "\0"; 
                Show(ssh);
                break;
            case 'p':
                scanf("%s",s2);
                Show(s2);
                break;
            case 'f':
				;
 				time_t t1 = time(NULL); 
                PrintToFile();
				time_t t2 = time(NULL);
			    printf("Time: %f\n",difftime(t2,t1));
                break;
            case 'q':
                printf("%s\n","Quit");
                f=1;
                break;
            case 'h':
                printf("\nBor structure\nby Nickolay Andronov(c)\n\n Operations:\n1)a string - Appends string\n2)d string - Deletes string\n3)s - Shows all strings\n4)q - Quit\n5)h - Help\n6)p string - Prints all strings started with prefix\n7)g(number of words, lowerlimit, upper limit) - Generates random strings \n\n");
                break;
            default: 
                printf("%s\n","Invalid operation");
                break;
        }
    }
	free(mas);		
	return 0;
}
