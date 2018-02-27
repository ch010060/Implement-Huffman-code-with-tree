#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;


struct Node
{
	char ID;      //記名字的
	char *code;   //記code
	int turn;     //記順序的
    double prob;
    struct Node *nextnode,*leftnode,*rightnode;
};

int ListLength(struct Node *);
void PrintResult(struct Node *,char *,int,char []);
void FreeTree(struct Node *);


    char letter[52]={0};
	double num[52]={0};
	int index=0;
	double PRO[52]={0};
	int totalline=0;
	int identity=0;
	int k=0;
	string ary2[100]; //記最後編碼的
	string ary3[100]; //記個別編碼的
	string sp[100];   //處理有參與編碼但最後沒要印的代碼
	int ary4[100];    //記名字的


	

	

int main()
{
    
    struct Node *headnode=NULL,*newnode=NULL,*lastnode=NULL,*curnode=NULL,*prenode=NULL;
    struct Node *min1node=NULL,*min2node=NULL;
    char *CodeString=NULL;
    int CharNumber;
    double MinProb;
	int decodeIndex=0;
	char decode[100];
	char buffer3[100];
	char buffer2[100];
	char buffer[100];
	stringstream ss (stringstream::in | stringstream::out);
	
	

	//為了讀取總行數開檔
	fstream file2;
	file2.open("p5.in");
	if(!file2)
	{
		cout<<"開檔失敗!\n";
		system("pause");
		return 0;
	}
	else
	{
		while(!file2.eof()){

		if(file2.getline(buffer2,sizeof(buffer))==NULL)
		break;

		totalline++;

		}
	}
	file2.close();

	cout<<"總行數: "<<totalline<<"\n\n";

    // 讀入輸入檔案
    fstream file;
	file.open("p5.in",ios::in);
	if(!file)
	{
		cout<<"開檔失敗!\n";
		system("pause");
		return 0;
	}
	else
	{


	do{


		if(index<totalline-2)
		{

		if((file >> letter[index])==NULL)
			break;
	

		file >> num[index];

		}
		if(index==totalline-1)
		{
			if(file.getline(buffer,sizeof(buffer))==NULL)
			break;

			ss << buffer;
			while(1){
				ss>>decode[decodeIndex];
				decodeIndex++;

				if(ss.fail())  //如果全部丟完，就跳出while
				break;
			}

			decode[decodeIndex-1]='\0';
			ss.clear();

			

		}
		if(file.getline(buffer3,sizeof(buffer3))==NULL)  //buffer沒啥功用，純粹拿來停止的
			break;


		index++;
		
		}while(!file.eof());
		file.close();

		index=totalline-2;
		letter[index]='\0';
		num[index]='\0';
		PRO[index]='\0';

		double total=0;
		for(int i=0;letter[i]!='\0';i++)
			total=total+num[i];	
		
		for(int j=0;letter[j]!='\0';j++)		
			PRO[j]=num[j]/total;         //求出各點分別出現的機率
// 顯示輸入資料		
		cout<<"代碼 次數   機率\n";
		for(int k=0;letter[k]!='\0';k++)
			cout<<letter[k]<<"     "<<num[k]<<"     "<<PRO[k]<<"\n";


		//decode檢驗用
		cout<<"\n待被轉換代碼串:\n";
		for(int i=0;decode[i]!='\0';i++)
			cout<<decode[i];
		cout<<"\n";

	
	}
 


    CharNumber=index;
    
    headnode=(struct Node *)calloc(sizeof(struct Node),1);
    headnode->prob=PRO[0];
	headnode->ID=letter[identity];
	headnode->turn=identity;
	identity++;
//建立單向鏈結
    lastnode=headnode;
	int k=index-1;
	int INDEX=1;
    while(k>0)
    {
        newnode=(struct Node *)calloc(sizeof(struct Node),1);
        newnode->prob=PRO[INDEX];
		newnode->ID=letter[identity];
		newnode->turn=identity;
		identity++;
        lastnode->nextnode=newnode;
        lastnode=newnode;
		INDEX++;
		k--;
    }
 
    curnode=headnode;
	int time=0;
    while(curnode!=NULL)
    {
		
		ary4[time]=curnode->ID;
		time++;
        curnode=curnode->nextnode;
    }
    
    // Huffman Code
    while(ListLength(headnode)!=1)
    {
        // 找出最小的節點
        MinProb=2.0;
        curnode=headnode;
		
        while(curnode!=NULL)
        {
            if((curnode->prob)<MinProb)
            {
                MinProb=curnode->prob;
                min1node=curnode;
            }
            curnode=curnode->nextnode;

			
				
        }
      
        // 找出第二小的節點
        MinProb=2.0;
        curnode=headnode;
	
        while(curnode!=NULL)
        {
            if((curnode->prob)<MinProb && curnode!=min1node)
            {
                MinProb=curnode->prob;
                min2node=curnode;
            }
            curnode=curnode->nextnode;
				
        }

        
        // 將最小兩個節點機率之和存入新節點
        newnode=(struct Node *)calloc(sizeof(struct Node),1);
        newnode->prob=(min1node->prob)+(min2node->prob);
        newnode->leftnode=min1node;
        newnode->rightnode=min2node;
        
        // 將新節點加入到串列最前面
        newnode->nextnode=headnode;
        headnode=newnode;
	
        
        // 移除兩個機率最小的節點
        prenode=headnode;
        curnode=headnode->nextnode;
		
        while(curnode!=NULL)
        {
            if(curnode==min1node || curnode==min2node)
            {
                prenode->nextnode=curnode->nextnode;
                curnode->nextnode=NULL;
                curnode=prenode;
            }
            
            prenode=curnode;
            curnode=curnode->nextnode;
		
        }
    }
    
    // 顯示結果
    CodeString=(char *)malloc(sizeof(char)*CharNumber);
    cout<<"\nHuffman Code:\n(未排序)\n";
    PrintResult(headnode,CodeString,0,decode);


    
    // 釋放記憶體
    FreeTree(headnode);
    free(CodeString);
    
    cout<<"\n";
    system("pause");
    return 0;
}

int ListLength(struct Node *headnode)
{
    struct Node *curnode=NULL;
    int length;
    
    length=0;
    curnode=headnode;
    while(curnode!=NULL)
    {
        length++;
        curnode=curnode->nextnode;
    }
    
    return length;
}

void PrintResult(struct Node *startnode,char *codestring,int level,char ary[100])
{
    if((startnode->leftnode)!=NULL)
    {

		
        codestring[level]='0';
        PrintResult(startnode->leftnode,codestring,level+1,ary);
        codestring[level]='1';
        PrintResult(startnode->rightnode,codestring,level+1,ary);
    }
    else
    {


		 char filename[]="p5.out";
	     fstream file3;
		 file3.open((char*) filename, ios::app);      //以append模式開啟檔案，準備寫入

        if(!file3)     //檢查檔案是否成功開啟

        {

                cerr << "Can't open file!\n";

                exit(1);     //在不正常情形下，中斷程式的執行

        }

		else
		{

	
        codestring[level]='\0';
		startnode->code=codestring;
		cout<<startnode->ID<<" "<<codestring<<endl;
    
		string result_string;
        char *test_char=codestring;
       //利用assign把*char轉成string
	   string x=result_string.assign(test_char);
		

	//整理編碼開始
	for(int i=0;ary[i]!='\0';i++)
	{
		
		if(ary[i]==startnode->ID)
		{
			
			ary3[startnode->turn]=x;
			ary2[i]=x;
			k++;

			
		}
		
		else
		{
			sp[startnode->turn]=x;

		}
		



		if(k==strlen(ary))
	        {
			
				cout<<"\n(已排序)";
				for(int i=0;i<totalline-2;i++)
				{
					if(ary3[i]!="")
					{
					file3<<(char)ary4[i]<<" "<<ary3[i]<<"\n";
					}
					else
					{
					file3<<(char)ary4[i]<<" "<<sp[i]<<"\n";
					}
				}
				

				cout<<endl;
				file3<<"\n";

				for(int i=0;i<totalline-2;i++)
				{
					if(ary3[i]!="")
					{
					cout<<(char)ary4[i]<<" "<<ary3[i]<<"\n";
					}
					else
					{
					cout<<(char)ary4[i]<<" "<<sp[i]<<"\n";
					}
				}


				cout<<"\n編碼結果\n";
				for(int i=0;i<k;i++)
				{
				cout<<ary2[i]<<" ";
				file3<<ary2[i];
				}
			cout<<endl;
			file3<<"\n";
			exit(1);
	
		}	



		
	}
    //整理編碼結束


		}
		file3.close();
       //寫檔結束


	
		
	}
}

void FreeTree(struct Node *startnode)
{
    if(startnode!=NULL)
    {
        FreeTree(startnode->leftnode);
        FreeTree(startnode->rightnode);
        free(startnode);
    }
}




