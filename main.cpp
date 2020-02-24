#include"save&load.cpp"
#include"output.cpp"
#include"evaluate.cpp"
using namespace std;

bool menu(int chess[8][8],int*step,int*color);//进入菜单
bool lose(int chess[8][8],int k);//计算是否结束，k=1为黑子失败，k=-1为白子失败
int main()
{
    system("color 70");
    while(1)
    {
        system("cls");
        char num=0;//输入选项
        int chess[8][8]={0};//存储棋子位置，1代表黑子（先），-1代表白子（后），3代表障碍，0代表无棋子
        int step=0,color=0;//存储步数、玩家执子颜色
        
        if(!access("./cache/now",0))//判断是否存在now文件即是否意外退出
        {
            cout<<"\n\n\n\n\n\n\n\n\n"<<"\t\t\t\t";
            cout<<"游戏曾意外退出，是否恢复先前游戏？ y 是 n 否"<<"\n\n\t\t\t\t\t\t\t";
            while(cin>>num)
            {
                if((num!='y'&&num!='n')||getchar()!='\n') //错误输入判断
                    {while(getchar()!='\n');cout<<"\t\t\t\t\t\t    请重新输入：";continue;}
                break;
            }
            ifstream infile("./cache/now");
            for(int i = 0;i < 8; i++)
                for(int j = 0;j < 8; j++)
                {
                    infile>>chess[i][j];
                }
            infile>>step>>color;//先读入now文件
            infile.close();
            if(num=='n') //如果选择为n则删除cache文件夹内容并初始化chess
            {
                for(int i=step;i>=0;i-=2)
                {
                    char name[20]={"./cache/"};
                    itoa(i,name+8,10);
                    remove(name);
                }
                remove("./cache/now");
                memset(chess,0,256);
            }
        }

        if(num!='y')//进入主菜单
        {
            system("cls");
            cout<<"\n\n\n\n\n\n\n\n\n";
            cout<<"\t\t\t\t\t\t  1  新游戏\n"<<endl<<"\t\t\t\t\t\t  2  读取存档\n"<<endl<<"\t\t\t\t\t\t  3  退出\n"<<endl;
            cout<<"\n\t\t\t\t\t\t请输入您的选项：";
            while(cin>>num)
            {
                if(num=='3') return 0;
                else if(num =='2')
                {
                    list();
                    cout<<"\t\t\t\t\t\t输入 * 返回\n";
                    cout<<"\t\t\t\t\t    请输入要选择的存档名称：";
                    char name[20]={"./save/"};
                    while(cin>>name+7)
                        if(name[7]=='*'||load(chess,&step,&color,name)) //如果输入*或存档名不存在则返回主菜单
                            break;
                    break;
                }
                else if(num=='1') 
                {
                    chess[0][2]=-1; chess[0][5]=-1; chess[2][0]=-1; chess[2][7]=-1;
                    chess[7][2]=1; chess[7][5]=1; chess[5][0]=1; chess[5][7]=1;
                    step=0;//初始化
                    system("cls");
                    output(chess);
                    cout<<"\n\t\t\t\t\t\t    请选择颜色\n\t\t\t\t\t  1为黑子先手，0为白子后手：";
                    cin>>num;
                    while((num!='0'&&num!='1')||getchar()!='\n') {while(getchar()!='\n');cout<<"\t\t\t\t\t\t    请重新输入：";cin>>num;}
                    color=(num=='1')?1:-1;//选择颜色
                    break;
                }
                else cout<<"\t\t\t\t\t      无此选项，请重新输入：";
            }
        }

        while(1)//对局循环
        {
            if(color==0) break;//此处为保证存档读入失败时直接跳出回到主菜单
            if(color==-1&&step==0) //若玩家后手则电脑先下一子
            {
                cout<<"\t\t\t\t\t\t   AI计算中…………"<<endl;
                step++;
                how_to_drop(chess,step,1,0,-10001);
                cout<<"\t\t\t\t\t\t   按回车键继续"<<endl; while(getchar()!='\n');
            }

            char x=0,y=0,xt=0,yt=0,arrow_x=0,arrow_y=0;//x、y存储要移动的棋子位置，xt、yt存储要移动到的位置，arrow-x、arrow-y存储放箭位置
            system("cls");
            output(chess);
            if(lose(chess,color)) {cout<<"\n\t\t\t\t\t\t\t菜\n\n";cout<<"\t\t\t\t\t\t   按回车键继续"; while(getchar()!='\n'); break;}//判断玩家是否输掉对局
            auto_save(chess,step,color);//自动存档至cache文件夹

            cout<<"\t\t\t\t\t    请输入要移动的棋子的位置：";
        loop1://错误输入时回到loop1
            cin>>x;
            if(x=='*') {while(getchar()!='\n'); if(menu(chess,&step,&color)) break; else continue;}//进入菜单，返回1则跳出对局循环，返回0则重新输入
            else if(x=='.') {while(getchar()!='\n'); continue;}//重新输入
            else if(x=='+') //悔棋
            {
                while(getchar()!='\n'); if(step<2) continue;//若步数小于2无法悔棋，重新输入
                char name[20]={"./cache/"}; itoa(step,name+8,10);remove(name);//name存储存档路径，先移除当前步数的自动存档
                step-=2;itoa(step,name+8,10);
                if(!load(chess,&step,&color,name)) //再读入上一个自动存档
                    step+=2;//若上一个自动存档不存在则返回1，就将step变回原值
                continue;
            }
            else cin>>y;
            if(x<'0'||x>'7'||y<'0'||y>'7'||chess[y-'0'][x-'0']!=color||getchar()!='\n') 
                {while(getchar()!='\n');cout<<"\t\t\t\t\t\t位置无效，请重新输入：";goto loop1;}//输入是否合法

            cout<<"\t\t\t\t\t    请输入要移动到的位置：";
        loop2:
            cin>>xt;
            if(xt=='*') {while(getchar()!='\n'); if(menu(chess,&step,&color)) break; else continue;}
            else if(xt=='.') {while(getchar()!='\n'); continue;}
            else if(x=='+') 
            {
                while(getchar()!='\n'); if(step<2) continue;
                char name[20]={"./cache/"};itoa(step,name+8,10);remove(name);
                step-=2;itoa(step,name+8,10);if(!load(chess,&step,&color,name)) step+=2;continue;
            }
            else cin>>yt;
            if(xt<'0'||xt>'7'||yt<'0'||yt>'7'||getchar()!='\n') {while(getchar()!='\n');cout<<"\t\t\t\t\t\t位置无效，请重新输入：";goto loop2;}
            int sign_x=(xt-x>0)-(xt-x<0),sign_y=(yt-y>0)-(yt-y<0);//记录移动方向
            if((sign_x&&sign_y&&x-xt!=y-yt&&x-xt!=yt-y)||(!sign_x&&!sign_y)) {cout<<"\t\t\t\t\t    不符合移动规则，请重新输入："; goto loop2;}
            for(int i=1;i<=sign_x*(xt-x)||i<=sign_y*(yt-y);i++)
                if(chess[y+sign_y*i-'0'][x+sign_x*i-'0'])
                    {cout<<"\t\t\t\t\t  路径含有箭或其他棋子，请重新输入：";goto loop2;}
            
            cout<<"\t\t\t\t\t    请输入要放置箭的位置：";
        loop3:
            cin>>arrow_x;
            if(arrow_x=='*') {while(getchar()!='\n'); if(menu(chess,&step,&color)) break; else continue;}
            else if(arrow_x=='.') {while(getchar()!='\n'); continue;}
            else if(x=='+') 
            {
                while(getchar()!='\n'); if(step<2) continue;
                char name[20]={"./cache/"};itoa(step,name+8,10);remove(name);
                step-=2;itoa(step,name+8,10);if(!load(chess,&step,&color,name)) step+=2;continue;
            }
            else cin>>arrow_y;
            if(arrow_x<'0'||arrow_x>'7'||arrow_y<'0'||arrow_y>'7'||getchar()!='\n') {while(getchar()!='\n');cout<<"\t\t\t\t\t\t位置无效，请重新输入：";goto loop3;}
            int sign_xt=(arrow_x-xt>0)-(arrow_x-xt<0),sign_yt=(arrow_y-yt>0)-(arrow_y-yt<0);//记录移动方向
            if((sign_xt&&sign_yt&&arrow_x-xt!=arrow_y-yt&&arrow_x-xt!=yt-arrow_y)||(!sign_xt&&!sign_yt)) 
                {
                    cout<<"\t\t\t\t\t    不符合放置规则，请重新输入："; 
                    goto loop3;
                }
            for(int i=1;i<=sign_xt*(arrow_x-xt)||i<=sign_yt*(arrow_y-yt);i++)
                if(chess[yt+sign_yt*i-'0'][xt+sign_xt*i-'0']&&(yt+sign_yt*i!=y||xt+sign_xt*i!=x))
                    {cout<<"\t\t\t\t\t  路径含有箭或其他棋子，请重新输入：";goto loop3;}
            
            chess[y-'0'][x-'0']=0; chess[yt-'0'][xt-'0']=color; chess[arrow_y-'0'][arrow_x-'0']=3;
            system("cls");
            output(chess);
            if(lose(chess,-color)) {cout<<"\n\t\t\t\t\t\t   大吉大利，今晚吃鸡\n\n"; cout<<"\t\t\t\t\t\t   按回车键继续"<<endl; while(getchar()!='\n'); break;}//判断玩家是否赢得对局
            cout<<"\t\t\t\t\t\t   AI计算中…………"<<endl;
            step+=2;
            how_to_drop(chess,step,-color,0,-10001);
            cout<<"\t\t\t\t\t\t   按回车键继续"; while(getchar()!='\n');
        }

        for(int i=step;i>=0;i-=2)//一局对局结束后，删除cache文件夹中的内容
        {
            char name[20]={"./cache/"};
            itoa(i,name+8,10);
            remove(name);
        }
        remove("./cache/now");
    }
}

//游戏内菜单
bool menu(int chess[8][8],int*step,int*color)
{
    while(1)
    {
        system("cls");
        cout<<"\n\n\n\n\n\n\n\n\n";
        cout<<"\t\t\t\t\t\t  0  返回游戏\n"<<endl<<"\t\t\t\t\t\t  1  新游戏\n"<<endl<<"\t\t\t\t\t\t  2  查看存档\n"<<endl<<"\t\t\t\t\t\t  3  返回主菜单\n"<<endl;
        cout<<"\n\t\t\t\t\t\t请输入您的选项：";
        char choice=0;//记录选项
        while(cin>>choice)
        {
            if(getchar()!='\n') {while(getchar()!='\n'); cout<<"\t\t\t\t\t\t    请重新输入："; continue;}
            if(choice=='0') return 0;
            if(choice=='1') 
            {
                for(int i=*step;i>=0;i-=2)//删除cache
                {
                    char name[20]={"./cache/"};
                    itoa(i,name+8,10);
                    remove(name);
                }
                remove("./cache/now");
                memset(chess,0,256);
                chess[0][2]=-1; chess[0][5]=-1; chess[2][0]=-1; chess[2][7]=-1;
                chess[7][2]=1; chess[7][5]=1; chess[5][0]=1; chess[5][7]=1;
                *step=0;//初始化
                system("cls");
                output(chess);
                cout<<"\n\t\t\t\t\t\t    请选择颜色\n\t\t\t\t\t  1为黑子先手，0为白子后手：";
                cin>>choice;
                while((choice!='0'&&choice!='1')||getchar()!='\n') {while(getchar()!='\n');cout<<"\t\t\t\t\t\t    请重新输入：";cin>>choice;}
                *color=(choice=='1')?1:-1;//选择颜色
                return 0;
            }
            if(choice=='2') {if(operation(chess,step,color)) return 0; break;}//进入存档操作界面，返回1则操作成功回到对局，返回0则操作失败回到菜单
            if(choice=='3') 
            {
                for(int i=*step;i>=0;i-=2)//删除cache
                {
                    char name[20]={"./cache/"};
                    itoa(i,name+8,10);
                    remove(name);
                }
                remove("./cache/now");
                return 1;//返回1来回到主菜单
            }
            else cout<<"\t\t\t\t\t      无此选项，请重新输入：";
        }
    }
}

//计算是否结束，k=1为黑子失败，k=-1为白子失败
bool lose(int chess[8][8],int k)
{
    int dx[8]={1,-1,0,0,1,1,-1,-1},dy[8]={0,0,1,-1,1,-1,1,-1};
    int count=0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8&&count<4;j++)
            if(chess[i][j]==k)//寻找棋子
            {
                count++;
                for(int k=0;k<8;k++)//判断其八个方向上是否都有棋子
                {
                    if(i+dx[k]>=8||i+dx[k]<0||j+dy[k]>=8||j+dy[k]<0) continue;
                    if(chess[i+dx[k]][j+dy[k]]==0) return 0;
                }               
            }
    return 1;
}