#include<iostream>
using namespace std;
//�������
void output(int chess[8][8])
{
    cout<<"\t\t\t\t\t\t���������Կո����"<<endl<<"\t\t\t\t\t  *����˵� +���� .����ѡ������";//�����ϵ�С����
    cout<<"\n\n\t\t\t\t\t";cout<<"  ";
    for(int i=0;i<8;i++)
        cout<<' '<<i<<"  ";
    cout<<endl<<' '<<"\t\t\t\t";//�����һ��x����
    for(int i=0;i<8;i++)
    {
        if(!i) cout<<"\t ��";
        cout<<"��"<<"��"<<"��";
        if(i==7) cout<<"��"<<endl;
        else cout<<"��";
    }//������̵�һ�е���
    for(int i=0;i<8;i++)
    {
        if(i) 
            for(int k=0;k<8;k++)
            {
                if(!k) cout<<endl<<"\t\t\t\t"<<' '<<"\t ��";
                cout<<"��"<<"��"<<"��";
                if(k==7) cout<<"��"<<endl;
                else cout<<"��";
            }//������м����
        cout<<"\t\t\t\t"<<'\t'<<i<<"��";
        for(int j=0;j<8;j++)
        {
            switch(chess[i][j])
            {
                case 1:
                cout<<" ��";break;
                case -1:
                cout<<" ��";break;
                case 3:
                cout<<" ��";break;
                default:
                cout<<"   ";break;
            }
            cout<<"��";
        }
        cout<<' '<<i;
        //�����i��
    }
    for(int i=0;i<8;i++)
    {
        if(!i) cout<<endl<<"\t\t\t\t"<<' '<<"\t ��";
        cout<<"��"<<"��"<<"��";
        if(i==7) cout<<"��"<<endl;
        else cout<<"��";
    }//������һ�е���
    cout<<"\t\t\t\t\t";cout<<"  ";
    for(int i=0;i<8;i++)
        cout<<" "<<i<<"  ";//������·�x����
    cout<<endl<<endl;
    return;
}