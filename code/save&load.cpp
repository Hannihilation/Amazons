//读取、存储存档的函数
#include<iostream>
#include<cstring>
#include<fstream>
#include<cstdlib>
#include<io.h>
#include<vector>
using namespace std;
void getFiles( string path, vector<string>& files );//这个我复制粘贴的，我看不懂
//输出存档列表
void list()
{
    system("cls"); cout<<"\n\n\n\n\n\n";
    cout<<"\t\t\t\t\t\t存档列表："<<endl<<endl;
    vector<string> filesname;
    getFiles("./save",filesname);
    int size = filesname.size();  
    for (int i = 0;i < size;i++)   
        cout<<"\t\t\t\t\t\t"<<filesname[i].c_str()+7<<endl;  
    cout<<endl;
    return;
}
//自动存档，chess为棋盘，step为步数，color为颜色
void auto_save(int chess[8][8],int step,int color)
{
    char name[20]={"./cache/"};
    itoa(step,name+8,10);
    ofstream autofile(name);//以step的值为名存储
    for(int i = 0;i < 8; i++)
            for(int j = 0;j < 8; j++)
            {
                autofile<<chess[i][j]<<' ';
                if(j==7) autofile<<endl;
            }
    autofile<<step<<' '<<color;
    autofile.close();
    autofile.open("./cache/now");//更新now文件，即当前棋局
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
//存档，chess为棋盘，step为步数，color为颜色，save为路径
bool save(int chess[8][8],int*step,int*color,char save[])
{ 
    ofstream outfile;
    int mark=0;
    if(!access(save,0))//判断已经是否存在此存档
    {
        cout<<"\t\t\t\t  注意：此存档已存在，是否覆盖？ y 是 n 否"<<endl<<"\t\t\t\t\t\t    ";
        char c=0;
    loop:
        cin>>c;
        mark++;
        if(c=='n') {cout<<"\t\t\t\t\t  请重新输入存档名称：";return 0;}//选否，存档失败返回0
        else if(c=='y') {outfile.open(save,ios::out|ios::trunc);}//选是，则覆盖原存档
        else if(mark<20){cout<<"\t\t\t\t\t\t请输入y或n"<<endl<<"\t\t\t\t\t\t    "; goto loop;}
        else if(mark==20){cout<<"\t\t\t\t\t  你他娘的能按我说的输入吗？"<<endl<<"\t\t\t\t\t\t    "; goto loop;}
        else if(mark==21){cout<<"\t\t\t\t      你憨批吧，都跟你说了输入Y或者N"<<endl<<"\t\t\t\t\t\t    "; goto loop;}
        else if(mark==22){cout<<"\t\t\t\t\t      再这样我要喷你了"<<endl<<"\t\t\t\t\t\t    ";goto loop;}
        else {cout<<"\t\t\t\t\t\t  mdzz"<<endl<<"\t\t\t\t\t\t    "; goto loop;}
    }
    else outfile.open(save,ios::out);//写入
    for(int i = 0;i < 8; i++)
        for(int j = 0;j < 8; j++)
        {
            outfile<<chess[i][j]<<' ';
            if(j==7) outfile<<endl;
        }
    outfile<<*step<<' '<<*color;
    outfile.close();
    return 1;//存档成功返回1
}
//读档
bool load(int chess[8][8],int*step,int*color,char save[])
{ 
    ifstream infile(save);
    if(infile.fail()) {cout<<"\t\t\t\t\t无此存档，请重新输入存档名：";return 0;}//判断存档是否存在，不存在则读档失败返回0
    if(save[2]=='s')//当读取的是save文件夹中的存档时，删除原有的cache
        for(int i=*step;i>=0;i-=2)
            {
                char name[20]={"./cache/"};
                itoa(i,name+8,10);
                remove(name);
            }
    for(int i = 0;i < 8; i++)//读取
        for(int j = 0;j < 8; j++)
        {
            infile>>chess[i][j];
        }
    infile>>*step>>*color;
    infile.close();
    return 1;//读档成功返回1
}

//这个我复制粘贴的，我看不懂
void getFiles( string path, vector<string>& files )  
{  
    //文件句柄  
    long   hFile   =   0;  
    //文件信息  
    struct _finddata_t fileinfo;  
    string p;  
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)  
    {  
        do  
        {  
            //如果是目录,迭代之  
            //如果不是,加入列表  
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

//存档操作界面，返回1回到对局循环，返回0回到菜单
bool operation(int chess[8][8],int*step,int*color)
{
    list();
    cout<<"\t\t\t\t\t  请输入要选择的存档名称：";
    char name[20]={"./save/"};
    while(cin>>name+7)
    {
        cout<<"\t\t\t\t     请选择：0 返回 1 存档 2 读档 3 删档"<<endl<<"\t\t\t\t\t\t    ";
        char choice=0;
        while(cin>>choice)
        {
            if(getchar()!='\n') {while(getchar()!='\n'); cout<<"\t\t\t\t\t  请重新输入："; continue;}
            else if(choice=='0') return 0;
            else if(choice=='1') {if(save(chess,step,color,name)) return 1; break;}//存档成功返回1，则退出，存档失败重新输入
            else if(choice=='2') {if(load(chess,step,color,name)) return 1; break;}//读档成功返回1，则退出，读档失败重新输入
            else if(choice=='3') 
            {
                cout<<"\t\t\t\t\t确定要删除此存档吗？ y 是 n 否\n"<<"\t\t\t\t\t\t    ";//确定是否删除
                cin>>choice; if(choice=='y') remove(name);                
                return 0;
            }
            else cout<<"\t\t\t\t\t    无效选择，请重新输入：";
        }
    }
}