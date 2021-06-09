#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

typedef struct{
	char name;
    int weight;
    int parent;
    int lChild;
    int rChild;
} Node, *HuffmanTree;

typedef char *HuffmanCode;

int Select(HuffmanTree *huffmanTree, int n, int s){
	int i;
	int min;
	for(i = 0; i < n; i++){
        if((*huffmanTree)[i].parent == -1 && i != s){
            min = i;
            break;
        }
    }
    for(i = 0; i < n; i++){
        if((*huffmanTree)[i].parent == -1 && i != s){
            if((*huffmanTree)[i].weight < (*huffmanTree)[min].weight){
               min = i;
            }
        }
    }
   return min;
}

void CreateHuffmanTree(HuffmanTree *huffmanTree, int total){
	int w;
	int i;
	char word;
	int sum = 2 * total - 1;
	int min1 = 0;
	int min2 = 0;
	
	
	//初始化哈夫曼树
	for(i = 0; i <sum; i++){
		if(i < total){
			printf("请输入第%d个结点的字符:",i);
			getchar();
		    scanf("%c",&word);
            (*huffmanTree)[i].name = word;   
            printf("请输入第%d个结点的权值:",i);
		    scanf("%d",&w);
            (*huffmanTree)[i].weight = w;
		}else{
			(*huffmanTree)[i].weight = 0;
			(*huffmanTree)[i].name = ' ';
		}
		(*huffmanTree)[i].parent = -1;	    
        (*huffmanTree)[i].lChild = -1;      
        (*huffmanTree)[i].rChild = -1;
        
    }
       
    for(i = total; i < sum; i++){
    	min1 = Select(huffmanTree,i,i);
    	min2 = Select(huffmanTree,i,min1);
        (*huffmanTree)[min1].parent = i;
        (*huffmanTree)[min2].parent = i;
        (*huffmanTree)[i].lChild = min1;
        (*huffmanTree)[i].rChild = min2;
        (*huffmanTree)[i].weight = (*huffmanTree)[min1].weight + (*huffmanTree)[min2].weight;
    }
    
   
    printf("\n哈夫曼树建毕!\n所建哈夫曼树如下：\n");
    printf("下标位置  字符  权值  左孩子  右孩子  双亲\n"); 
    for(i = 0;i < sum;i ++){
    	printf("%4d        %c%6d",i,(*huffmanTree)[i].name,(*huffmanTree)[i].weight);
    	printf("%8d%8d%6d\n",(*huffmanTree)[i].lChild,(*huffmanTree)[i].rChild,(*huffmanTree)[i].parent);
	}
    	
}


void CreateHuffmanCode(HuffmanTree *huffmanTree, HuffmanCode *huffmanCode, int n){
    int i;
    int j;
    int start;
    int p;
    

    char *code = (char *)malloc(n * sizeof(char));
    code[n-1] = '\0';
    
    for(i = 0; i < n; i++){
        start = n - 1;
		j = i;
		p = (*huffmanTree)[i].parent;
        while(p != -1){ 	     	    
            if( (*huffmanTree)[p].lChild == j){
                 code[--start] = '0';  
            }
            else{
                code[--start] = '1';  
            }
			j = p;
			p = (*huffmanTree)[p].parent;
        }
        huffmanCode[i] = (char *)malloc((n - start) * sizeof(char));
        strcpy(huffmanCode[i], &code[start]);
    }
    free(code);
    //打印编码序列
    for(i = 0; i < n; i++){
         printf("第%d个字符%c的编码是%s\n", i + 1,(*huffmanTree)[i].name, huffmanCode[i]);
    }
    printf("\n");
}

void Coder(HuffmanTree *huffmanTree, HuffmanCode *huffmanCode, char ch[], int n){
	int i;
	int j;
	FILE *file = fopen("D:\\1.txt","w");
	if(file == NULL){
		printf("打开文件失败");
		exit(0);
	}
	printf("%s",huffmanCode[1]);
	printf("111打开文件失败");
	for(i = 0;i < strlen(ch);i ++){
		for (j = 0; j < n; j++ ){
		printf("222打开文件失败");       
            if (ch[i] == (*huffmanTree)[j].name){
                    printf("%s",huffmanCode[j]);
					fprintf(file,huffmanCode[j]);					 
            }
            break;
        }
	}
	
}

int main(){
	int Select(HuffmanTree *huffmanTree, int n, int s);
	
   
    int total;
    char ch[100];
     
    printf("请输入结点总数：total = " );
    scanf("%d",&total);
    printf("\n");
    HuffmanTree HT =(HuffmanTree)malloc((2 * total - 1) * sizeof(Node));;
    HuffmanCode HC=(HuffmanCode)malloc((total+1) * sizeof(char *));
    CreateHuffmanTree(&HT, total);
    CreateHuffmanCode(&HT,&HC,total);
    printf("%s",HC[0]);
    printf("请输入需编码字符串(字符串中的字符须是当前对象中的字符):\n");
    getchar();
    gets(ch);

    printf("编码结果是：\n");
    Coder(&HT,&HC,ch,total);
    
    
    
    return 0;
	
}