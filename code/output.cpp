#include<iostream>
using namespace std;
//输出棋盘
void output(int chess[8][8])
{
    cout<<"\t\t\t\t\t\t坐标无需以空格隔开"<<endl<<"\t\t\t\t\t  *进入菜单 +悔棋 .重新选择棋子";//棋盘上的小帮助
    cout<<"\n\n\t\t\t\t\t";cout<<"  ";
    for(int i=0;i<8;i++)
        cout<<' '<<i<<"  ";
    cout<<endl<<' '<<"\t\t\t\t";//输出第一行x坐标
    for(int i=0;i<8;i++)
    {
        if(!i) cout<<"\t ┌";
        cout<<"─"<<"─"<<"─";
        if(i==7) cout<<"┐"<<endl;
        else cout<<"┬";
    }//输出棋盘第一行的线
    for(int i=0;i<8;i++)
    {
        if(i) 
            for(int k=0;k<8;k++)
            {
                if(!k) cout<<endl<<"\t\t\t\t"<<' '<<"\t ├";
                cout<<"─"<<"─"<<"─";
                if(k==7) cout<<"┤"<<endl;
                else cout<<"┼";
            }//输出两行间的线
        cout<<"\t\t\t\t"<<'\t'<<i<<"│";
        for(int j=0;j<8;j++)
        {
            switch(chess[i][j])
            {
                case 1:
                cout<<" ●";break;
                case -1:
                cout<<" ○";break;
                case 3:
                cout<<" ⅹ";break;
                default:
                cout<<"   ";break;
            }
            cout<<"│";
        }
        cout<<' '<<i;
        //输出第i行
    }
    for(int i=0;i<8;i++)
    {
        if(!i) cout<<endl<<"\t\t\t\t"<<' '<<"\t └";
        cout<<"─"<<"─"<<"─";
        if(i==7) cout<<"┘"<<endl;
        else cout<<"┴";
    }//输出最后一行的线
    cout<<"\t\t\t\t\t";cout<<"  ";
    for(int i=0;i<8;i++)
        cout<<" "<<i<<"  ";//输出最下方x坐标
    cout<<endl<<endl;
    return;
}