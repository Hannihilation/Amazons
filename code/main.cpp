#include"save&load.cpp"
#include"output.cpp"
#include"evaluate.cpp"
using namespace std;

bool menu(int chess[8][8],int*step,int*color);//����˵�
bool lose(int chess[8][8],int k);//�����Ƿ������k=1Ϊ����ʧ�ܣ�k=-1Ϊ����ʧ��
int main()
{
    system("color 70");
    while(1)
    {
        system("cls");
        char num=0;//����ѡ��
        int chess[8][8]={0};//�洢����λ�ã�1������ӣ��ȣ���-1������ӣ��󣩣�3�����ϰ���0����������
        int step=0,color=0;//�洢���������ִ����ɫ
        
        if(!access("./cache/now",0))//�ж��Ƿ����now�ļ����Ƿ������˳�
        {
            cout<<"\n\n\n\n\n\n\n\n\n"<<"\t\t\t\t";
            cout<<"��Ϸ�������˳����Ƿ�ָ���ǰ��Ϸ�� y �� n ��"<<"\n\n\t\t\t\t\t\t\t";
            while(cin>>num)
            {
                if((num!='y'&&num!='n')||getchar()!='\n') //���������ж�
                    {while(getchar()!='\n');cout<<"\t\t\t\t\t\t    ���������룺";continue;}
                break;
            }
            ifstream infile("./cache/now");
            for(int i = 0;i < 8; i++)
                for(int j = 0;j < 8; j++)
                {
                    infile>>chess[i][j];
                }
            infile>>step>>color;//�ȶ���now�ļ�
            infile.close();
            if(num=='n') //���ѡ��Ϊn��ɾ��cache�ļ������ݲ���ʼ��chess
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

        if(num!='y')//�������˵�
        {
            system("cls");
            cout<<"\n\n\n\n\n\n\n\n\n";
            cout<<"\t\t\t\t\t\t  1  ����Ϸ\n"<<endl<<"\t\t\t\t\t\t  2  ��ȡ�浵\n"<<endl<<"\t\t\t\t\t\t  3  �˳�\n"<<endl;
            cout<<"\n\t\t\t\t\t\t����������ѡ�";
            while(cin>>num)
            {
                if(num=='3') return 0;
                else if(num =='2')
                {
                    list();
                    cout<<"\t\t\t\t\t\t���� * ����\n";
                    cout<<"\t\t\t\t\t    ������Ҫѡ��Ĵ浵���ƣ�";
                    char name[20]={"./save/"};
                    while(cin>>name+7)
                        if(name[7]=='*'||load(chess,&step,&color,name)) //�������*��浵���������򷵻����˵�
                            break;
                    break;
                }
                else if(num=='1') 
                {
                    chess[0][2]=-1; chess[0][5]=-1; chess[2][0]=-1; chess[2][7]=-1;
                    chess[7][2]=1; chess[7][5]=1; chess[5][0]=1; chess[5][7]=1;
                    step=0;//��ʼ��
                    system("cls");
                    output(chess);
                    cout<<"\n\t\t\t\t\t\t    ��ѡ����ɫ\n\t\t\t\t\t  1Ϊ�������֣�0Ϊ���Ӻ��֣�";
                    cin>>num;
                    while((num!='0'&&num!='1')||getchar()!='\n') {while(getchar()!='\n');cout<<"\t\t\t\t\t\t    ���������룺";cin>>num;}
                    color=(num=='1')?1:-1;//ѡ����ɫ
                    break;
                }
                else cout<<"\t\t\t\t\t      �޴�ѡ����������룺";
            }
        }

        while(1)//�Ծ�ѭ��
        {
            if(color==0) break;//�˴�Ϊ��֤�浵����ʧ��ʱֱ�������ص����˵�
            if(color==-1&&step==0) //����Һ������������һ��
            {
                cout<<"\t\t\t\t\t\t   AI�����С�������"<<endl;
                step++;
                how_to_drop(chess,step,1,0,-10001);
                cout<<"\t\t\t\t\t\t   ���س�������"<<endl; while(getchar()!='\n');
            }

            char x=0,y=0,xt=0,yt=0,arrow_x=0,arrow_y=0;//x��y�洢Ҫ�ƶ�������λ�ã�xt��yt�洢Ҫ�ƶ�����λ�ã�arrow-x��arrow-y�洢�ż�λ��
            system("cls");
            output(chess);
            if(lose(chess,color)) {cout<<"\n\t\t\t\t\t\t\t��\n\n";cout<<"\t\t\t\t\t\t   ���س�������"; while(getchar()!='\n'); break;}//�ж�����Ƿ�����Ծ�
            auto_save(chess,step,color);//�Զ��浵��cache�ļ���

            cout<<"\t\t\t\t\t    ������Ҫ�ƶ������ӵ�λ�ã�";
        loop1://��������ʱ�ص�loop1
            cin>>x;
            if(x=='*') {while(getchar()!='\n'); if(menu(chess,&step,&color)) break; else continue;}//����˵�������1�������Ծ�ѭ��������0����������
            else if(x=='.') {while(getchar()!='\n'); continue;}//��������
            else if(x=='+') //����
            {
                while(getchar()!='\n'); if(step<2) continue;//������С��2�޷����壬��������
                char name[20]={"./cache/"}; itoa(step,name+8,10);remove(name);//name�洢�浵·�������Ƴ���ǰ�������Զ��浵
                step-=2;itoa(step,name+8,10);
                if(!load(chess,&step,&color,name)) //�ٶ�����һ���Զ��浵
                    step+=2;//����һ���Զ��浵�������򷵻�1���ͽ�step���ԭֵ
                continue;
            }
            else cin>>y;
            if(x<'0'||x>'7'||y<'0'||y>'7'||chess[y-'0'][x-'0']!=color||getchar()!='\n') 
                {while(getchar()!='\n');cout<<"\t\t\t\t\t\tλ����Ч�����������룺";goto loop1;}//�����Ƿ�Ϸ�

            cout<<"\t\t\t\t\t    ������Ҫ�ƶ�����λ�ã�";
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
            if(xt<'0'||xt>'7'||yt<'0'||yt>'7'||getchar()!='\n') {while(getchar()!='\n');cout<<"\t\t\t\t\t\tλ����Ч�����������룺";goto loop2;}
            int sign_x=(xt-x>0)-(xt-x<0),sign_y=(yt-y>0)-(yt-y<0);//��¼�ƶ�����
            if((sign_x&&sign_y&&x-xt!=y-yt&&x-xt!=yt-y)||(!sign_x&&!sign_y)) {cout<<"\t\t\t\t\t    �������ƶ��������������룺"; goto loop2;}
            for(int i=1;i<=sign_x*(xt-x)||i<=sign_y*(yt-y);i++)
                if(chess[y+sign_y*i-'0'][x+sign_x*i-'0'])
                    {cout<<"\t\t\t\t\t  ·�����м����������ӣ����������룺";goto loop2;}
            
            cout<<"\t\t\t\t\t    ������Ҫ���ü���λ�ã�";
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
            if(arrow_x<'0'||arrow_x>'7'||arrow_y<'0'||arrow_y>'7'||getchar()!='\n') {while(getchar()!='\n');cout<<"\t\t\t\t\t\tλ����Ч�����������룺";goto loop3;}
            int sign_xt=(arrow_x-xt>0)-(arrow_x-xt<0),sign_yt=(arrow_y-yt>0)-(arrow_y-yt<0);//��¼�ƶ�����
            if((sign_xt&&sign_yt&&arrow_x-xt!=arrow_y-yt&&arrow_x-xt!=yt-arrow_y)||(!sign_xt&&!sign_yt)) 
                {
                    cout<<"\t\t\t\t\t    �����Ϸ��ù������������룺"; 
                    goto loop3;
                }
            for(int i=1;i<=sign_xt*(arrow_x-xt)||i<=sign_yt*(arrow_y-yt);i++)
                if(chess[yt+sign_yt*i-'0'][xt+sign_xt*i-'0']&&(yt+sign_yt*i!=y||xt+sign_xt*i!=x))
                    {cout<<"\t\t\t\t\t  ·�����м����������ӣ����������룺";goto loop3;}
            
            chess[y-'0'][x-'0']=0; chess[yt-'0'][xt-'0']=color; chess[arrow_y-'0'][arrow_x-'0']=3;
            system("cls");
            output(chess);
            if(lose(chess,-color)) {cout<<"\n\t\t\t\t\t\t   �󼪴���������Լ�\n\n"; cout<<"\t\t\t\t\t\t   ���س�������"<<endl; while(getchar()!='\n'); break;}//�ж�����Ƿ�Ӯ�öԾ�
            cout<<"\t\t\t\t\t\t   AI�����С�������"<<endl;
            step+=2;
            how_to_drop(chess,step,-color,0,-10001);
            cout<<"\t\t\t\t\t\t   ���س�������"; while(getchar()!='\n');
        }

        for(int i=step;i>=0;i-=2)//һ�ֶԾֽ�����ɾ��cache�ļ����е�����
        {
            char name[20]={"./cache/"};
            itoa(i,name+8,10);
            remove(name);
        }
        remove("./cache/now");
    }
}

//��Ϸ�ڲ˵�
bool menu(int chess[8][8],int*step,int*color)
{
    while(1)
    {
        system("cls");
        cout<<"\n\n\n\n\n\n\n\n\n";
        cout<<"\t\t\t\t\t\t  0  ������Ϸ\n"<<endl<<"\t\t\t\t\t\t  1  ����Ϸ\n"<<endl<<"\t\t\t\t\t\t  2  �鿴�浵\n"<<endl<<"\t\t\t\t\t\t  3  �������˵�\n"<<endl;
        cout<<"\n\t\t\t\t\t\t����������ѡ�";
        char choice=0;//��¼ѡ��
        while(cin>>choice)
        {
            if(getchar()!='\n') {while(getchar()!='\n'); cout<<"\t\t\t\t\t\t    ���������룺"; continue;}
            if(choice=='0') return 0;
            if(choice=='1') 
            {
                for(int i=*step;i>=0;i-=2)//ɾ��cache
                {
                    char name[20]={"./cache/"};
                    itoa(i,name+8,10);
                    remove(name);
                }
                remove("./cache/now");
                memset(chess,0,256);
                chess[0][2]=-1; chess[0][5]=-1; chess[2][0]=-1; chess[2][7]=-1;
                chess[7][2]=1; chess[7][5]=1; chess[5][0]=1; chess[5][7]=1;
                *step=0;//��ʼ��
                system("cls");
                output(chess);
                cout<<"\n\t\t\t\t\t\t    ��ѡ����ɫ\n\t\t\t\t\t  1Ϊ�������֣�0Ϊ���Ӻ��֣�";
                cin>>choice;
                while((choice!='0'&&choice!='1')||getchar()!='\n') {while(getchar()!='\n');cout<<"\t\t\t\t\t\t    ���������룺";cin>>choice;}
                *color=(choice=='1')?1:-1;//ѡ����ɫ
                return 0;
            }
            if(choice=='2') {if(operation(chess,step,color)) return 0; break;}//����浵�������棬����1������ɹ��ص��Ծ֣�����0�����ʧ�ܻص��˵�
            if(choice=='3') 
            {
                for(int i=*step;i>=0;i-=2)//ɾ��cache
                {
                    char name[20]={"./cache/"};
                    itoa(i,name+8,10);
                    remove(name);
                }
                remove("./cache/now");
                return 1;//����1���ص����˵�
            }
            else cout<<"\t\t\t\t\t      �޴�ѡ����������룺";
        }
    }
}

//�����Ƿ������k=1Ϊ����ʧ�ܣ�k=-1Ϊ����ʧ��
bool lose(int chess[8][8],int k)
{
    int dx[8]={1,-1,0,0,1,1,-1,-1},dy[8]={0,0,1,-1,1,-1,1,-1};
    int count=0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8&&count<4;j++)
            if(chess[i][j]==k)//Ѱ������
            {
                count++;
                for(int k=0;k<8;k++)//�ж���˸��������Ƿ�������
                {
                    if(i+dx[k]>=8||i+dx[k]<0||j+dy[k]>=8||j+dy[k]<0) continue;
                    if(chess[i+dx[k]][j+dy[k]]==0) return 0;
                }               
            }
    return 1;
}