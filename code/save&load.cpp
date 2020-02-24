//��ȡ���洢�浵�ĺ���
#include<iostream>
#include<cstring>
#include<fstream>
#include<cstdlib>
#include<io.h>
#include<vector>
using namespace std;
void getFiles( string path, vector<string>& files );//����Ҹ���ճ���ģ��ҿ�����
//����浵�б�
void list()
{
    system("cls"); cout<<"\n\n\n\n\n\n";
    cout<<"\t\t\t\t\t\t�浵�б�"<<endl<<endl;
    vector<string> filesname;
    getFiles("./save",filesname);
    int size = filesname.size();  
    for (int i = 0;i < size;i++)   
        cout<<"\t\t\t\t\t\t"<<filesname[i].c_str()+7<<endl;  
    cout<<endl;
    return;
}
//�Զ��浵��chessΪ���̣�stepΪ������colorΪ��ɫ
void auto_save(int chess[8][8],int step,int color)
{
    char name[20]={"./cache/"};
    itoa(step,name+8,10);
    ofstream autofile(name);//��step��ֵΪ���洢
    for(int i = 0;i < 8; i++)
            for(int j = 0;j < 8; j++)
            {
                autofile<<chess[i][j]<<' ';
                if(j==7) autofile<<endl;
            }
    autofile<<step<<' '<<color;
    autofile.close();
    autofile.open("./cache/now");//����now�ļ�������ǰ���
    for(int i = 0;i < 8; i++)
            for(int j = 0;j < 8; j++)
            {
                autofile<<chess[i][j]<<' ';
                if(j==7) autofile<<endl;
            }
    autofile<<step<<' '<<color;
    autofile.close();
    return;
}
//�浵��chessΪ���̣�stepΪ������colorΪ��ɫ��saveΪ·��
bool save(int chess[8][8],int*step,int*color,char save[])
{ 
    ofstream outfile;
    int mark=0;
    if(!access(save,0))//�ж��Ѿ��Ƿ���ڴ˴浵
    {
        cout<<"\t\t\t\t  ע�⣺�˴浵�Ѵ��ڣ��Ƿ񸲸ǣ� y �� n ��"<<endl<<"\t\t\t\t\t\t    ";
        char c=0;
    loop:
        cin>>c;
        mark++;
        if(c=='n') {cout<<"\t\t\t\t\t  ����������浵���ƣ�";return 0;}//ѡ�񣬴浵ʧ�ܷ���0
        else if(c=='y') {outfile.open(save,ios::out|ios::trunc);}//ѡ�ǣ��򸲸�ԭ�浵
        else if(mark<20){cout<<"\t\t\t\t\t\t������y��n"<<endl<<"\t\t\t\t\t\t    "; goto loop;}
        else if(mark==20){cout<<"\t\t\t\t\t  ��������ܰ���˵��������"<<endl<<"\t\t\t\t\t\t    "; goto loop;}
        else if(mark==21){cout<<"\t\t\t\t      �㺩���ɣ�������˵������Y����N"<<endl<<"\t\t\t\t\t\t    "; goto loop;}
        else if(mark==22){cout<<"\t\t\t\t\t      ��������Ҫ������"<<endl<<"\t\t\t\t\t\t    ";goto loop;}
        else {cout<<"\t\t\t\t\t\t  mdzz"<<endl<<"\t\t\t\t\t\t    "; goto loop;}
    }
    else outfile.open(save,ios::out);//д��
    for(int i = 0;i < 8; i++)
        for(int j = 0;j < 8; j++)
        {
            outfile<<chess[i][j]<<' ';
            if(j==7) outfile<<endl;
        }
    outfile<<*step<<' '<<*color;
    outfile.close();
    return 1;//�浵�ɹ�����1
}
//����
bool load(int chess[8][8],int*step,int*color,char save[])
{ 
    ifstream infile(save);
    if(infile.fail()) {cout<<"\t\t\t\t\t�޴˴浵������������浵����";return 0;}//�жϴ浵�Ƿ���ڣ������������ʧ�ܷ���0
    if(save[2]=='s')//����ȡ����save�ļ����еĴ浵ʱ��ɾ��ԭ�е�cache
        for(int i=*step;i>=0;i-=2)
            {
                char name[20]={"./cache/"};
                itoa(i,name+8,10);
                remove(name);
            }
    for(int i = 0;i < 8; i++)//��ȡ
        for(int j = 0;j < 8; j++)
        {
            infile>>chess[i][j];
        }
    infile>>*step>>*color;
    infile.close();
    return 1;//�����ɹ�����1
}

//����Ҹ���ճ���ģ��ҿ�����
void getFiles( string path, vector<string>& files )  
{  
    //�ļ����  
    long   hFile   =   0;  
    //�ļ���Ϣ  
    struct _finddata_t fileinfo;  
    string p;  
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)  
    {  
        do  
        {  
            //�����Ŀ¼,����֮  
            //�������,�����б�  
            if((fileinfo.attrib &  _A_SUBDIR))  
            {  
                continue;
            }  
            else  
            {  
                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
            }  
        }while(_findnext(hFile, &fileinfo)  == 0);  
        _findclose(hFile);  
    }  
}

//�浵�������棬����1�ص��Ծ�ѭ��������0�ص��˵�
bool operation(int chess[8][8],int*step,int*color)
{
    list();
    cout<<"\t\t\t\t\t  ������Ҫѡ��Ĵ浵���ƣ�";
    char name[20]={"./save/"};
    while(cin>>name+7)
    {
        cout<<"\t\t\t\t     ��ѡ��0 ���� 1 �浵 2 ���� 3 ɾ��"<<endl<<"\t\t\t\t\t\t    ";
        char choice=0;
        while(cin>>choice)
        {
            if(getchar()!='\n') {while(getchar()!='\n'); cout<<"\t\t\t\t\t  ���������룺"; continue;}
            else if(choice=='0') return 0;
            else if(choice=='1') {if(save(chess,step,color,name)) return 1; break;}//�浵�ɹ�����1�����˳����浵ʧ����������
            else if(choice=='2') {if(load(chess,step,color,name)) return 1; break;}//�����ɹ�����1�����˳�������ʧ����������
            else if(choice=='3') 
            {
                cout<<"\t\t\t\t\tȷ��Ҫɾ���˴浵�� y �� n ��\n"<<"\t\t\t\t\t\t    ";//ȷ���Ƿ�ɾ��
                cin>>choice; if(choice=='y') remove(name);                
                return 0;
            }
            else cout<<"\t\t\t\t\t    ��Чѡ�����������룺";
        }
    }
}