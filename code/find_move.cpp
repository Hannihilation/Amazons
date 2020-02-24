//Ѱ��k��ҵ���������Ҫ����Сqueen�������洢��move����
void queen_move(int chess[8][8],int move[8][8],int k)
{
    int count=0,mark=0;
    for(int i=0;i<8;i++)//���ҵ�����λ�ã�0�����Ե���
        for(int j=0;j<8;j++)
            if(chess[i][j]==k)
            {
                move[i][j]=0;
            }
    while(++count)
    {
        mark=0;//��¼�Ƿ����count-1���ɵ����λ��
        for(int i=0;i<8;i++)//��count-1���ɵ����λ���ҵ�count���ɵ���λ��
            for(int j=0;j<8;j++)
            {
                if(move[i][j]==count-1)
                {
                    mark=1;
                    //��˸�������
                    for(int a=i-1;a>=0;a--)
                        {if(chess[a][j]) break; if(move[a][j]==1000) move[a][j]=count;}
                    for(int a=i+1;a<8;a++)
                        {if(chess[a][j]) break; if(move[a][j]==1000) move[a][j]=count;}
                    for(int a=j-1;a>=0;a--)
                        {if(chess[i][a]) break; if(move[i][a]==1000) move[i][a]=count;}
                    for(int a=j+1;a<8;a++)
                        {if(chess[i][a]) break; if(move[i][a]==1000) move[i][a]=count;}
                    for(int a=1;i-a>=0&&j-a>=0;a++)
                        {if(chess[i-a][j-a]) break; if(move[i-a][j-a]==1000) move[i-a][j-a]=count;}
                    for(int a=1;i+a<8&&j+a<8;a++)
                        {if(chess[i+a][j+a]) break; if(move[i+a][j+a]==1000) move[i+a][j+a]=count;}
                    for(int a=1;i-a>=0&&j+a<8;a++)
                        {if(chess[i-a][j+a]) break; if(move[i-a][j+a]==1000) move[i-a][j+a]=count;}
                    for(int a=1;i+a<8&&j-a>=0;a++)
                        {if(chess[i+a][j-a]) break; if(move[i+a][j-a]==1000) move[i+a][j-a]=count;}
                }
            }
        if(!mark) break;//��������������
    }
    return;
}
//Ѱ��k��ҵ���������Ҫ����Сking����
void king_move(int chess[8][8],int move[8][8],int k)
{
    int count=0,mark=0;//ͬ��
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(chess[i][j]==k)
            {
                move[i][j]=0;
            }
    while(++count)
    {
        mark=0;
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(move[i][j]==count-1)
                {
                    mark=1;
                    for(int a=-1;a<=1;a++)
                        for(int b=-1;b<=1;b++)
                            if(i+a>=0&&i+a<8&&j+b>=0&&j+b<8&&!chess[i+a][j+b]&&move[i+a][j+b]==1000)
                                move[i+a][j+b]=count;
                }
        if(!mark) break;
    }
    return;
}
int dx[8]={1,-1,0,0,1,1,-1,-1},dy[8]={0,0,1,-1,1,-1,1,-1};
//����colorɫ�ĸ���������С����
int min_mobility(int chess[8][8],int color)
{
    int ans=10000,temp=0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(chess[i][j]==color)//Ѱ������
            {
                temp=0;//��ʼ��
                for(int k=0;k<8;k++)//������ܵ��߷�
                    for(int l=1;;l++)
                    {
                        if(i+dx[k]*l>=8||j+dy[k]*l>=8||i+dx[k]*l<0||j+dy[k]*l<0) break;
                        if(chess[i+dx[k]*l][j+dy[k]*l]) break;
                        temp++;//�ҵ�һ���߷�temp��һ
                    }
                ans=(ans<temp)?ans:temp;//��temp��ansС���ans��ֵΪtemp
            }
    return ans;
}