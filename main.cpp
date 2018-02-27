#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;


struct Node
{
	char ID;      //�O�W�r��
	char *code;   //�Ocode
	int turn;     //�O���Ǫ�
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
	string ary2[100]; //�O�̫�s�X��
	string ary3[100]; //�O�ӧO�s�X��
	string sp[100];   //�B�z���ѻP�s�X���̫�S�n�L���N�X
	int ary4[100];    //�O�W�r��


	

	

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
	
	

	//���FŪ���`��ƶ}��
	fstream file2;
	file2.open("p5.in");
	if(!file2)
	{
		cout<<"�}�ɥ���!\n";
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

	cout<<"�`���: "<<totalline<<"\n\n";

    // Ū�J��J�ɮ�
    fstream file;
	file.open("p5.in",ios::in);
	if(!file)
	{
		cout<<"�}�ɥ���!\n";
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

				if(ss.fail())  //�p�G�����᧹�A�N���Xwhile
				break;
			}

			decode[decodeIndex-1]='\0';
			ss.clear();

			

		}
		if(file.getline(buffer3,sizeof(buffer3))==NULL)  //buffer�Sԣ�\�ΡA�º鮳�Ӱ��
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
			PRO[j]=num[j]/total;         //�D�X�U�I���O�X�{�����v
// ��ܿ�J���		
		cout<<"�N�X ����   ���v\n";
		for(int k=0;letter[k]!='\0';k++)
			cout<<letter[k]<<"     "<<num[k]<<"     "<<PRO[k]<<"\n";


		//decode�����
		cout<<"\n�ݳQ�ഫ�N�X��:\n";
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
//�إ߳�V�쵲
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
        // ��X�̤p���`�I
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
      
        // ��X�ĤG�p���`�I
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

        
        // �N�̤p��Ӹ`�I���v���M�s�J�s�`�I
        newnode=(struct Node *)calloc(sizeof(struct Node),1);
        newnode->prob=(min1node->prob)+(min2node->prob);
        newnode->leftnode=min1node;
        newnode->rightnode=min2node;
        
        // �N�s�`�I�[�J���C�̫e��
        newnode->nextnode=headnode;
        headnode=newnode;
	
        
        // ������Ӿ��v�̤p���`�I
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
    
    // ��ܵ��G
    CodeString=(char *)malloc(sizeof(char)*CharNumber);
    cout<<"\nHuffman Code:\n(���Ƨ�)\n";
    PrintResult(headnode,CodeString,0,decode);


    
    // ����O����
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
		 file3.open((char*) filename, ios::app);      //�Happend�Ҧ��}���ɮסA�ǳƼg�J

        if(!file3)     //�ˬd�ɮ׬O�_���\�}��

        {

                cerr << "Can't open file!\n";

                exit(1);     //�b�����`���ΤU�A���_�{��������

        }

		else
		{

	
        codestring[level]='\0';
		startnode->code=codestring;
		cout<<startnode->ID<<" "<<codestring<<endl;
    
		string result_string;
        char *test_char=codestring;
       //�Q��assign��*char�নstring
	   string x=result_string.assign(test_char);
		

	//��z�s�X�}�l
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
			
				cout<<"\n(�w�Ƨ�)";
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


				cout<<"\n�s�X���G\n";
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
    //��z�s�X����


		}
		file3.close();
       //�g�ɵ���


	
		
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




