//寻找k玩家到各点所需要的最小queen步数，存储至move数组
void queen_move(int chess[8][8],int move[8][8],int k)
{
    int count=0,mark=0;
    for(int i=0;i<8;i++)//先找到棋子位置，0步可以到达
        for(int j=0;j<8;j++)
            if(chess[i][j]==k)
            {
                move[i][j]=0;
            }
    while(++count)
    {
        mark=0;//记录是否存在count-1步可到达的位置
        for(int i=0;i<8;i++)//从count-1步可到达的位置找到count步可到达位置
            for(int j=0;j<8;j++)
            {
                if(move[i][j]==count-1)
                {
                    mark=1;
                    //向八个方向走
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
        if(!mark) break;//若不存在则跳出
    }
    return;
}
//寻找k玩家到各点所需要的最小king步数
void king_move(int chess[8][8],int move[8][8],int k)
{
    int count=0,mark=0;//同上
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
//计算color色四个棋子中最小灵活度
int min_mobility(int chess[8][8],int color)
{
    int ans=10000,temp=0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(chess[i][j]==color)//寻找棋子
            {
                temp=0;//初始化
                for(int k=0;k<8;k++)//找其可能的走法
                    for(int l=1;;l++)
                    {
                        if(i+dx[k]*l>=8||j+dy[k]*l>=8||i+dx[k]*l<0||j+dy[k]*l<0) break;
                        if(chess[i+dx[k]*l][j+dy[k]*l]) break;
                        temp++;//找到一个走法temp加一
                    }
                ans=(ans<temp)?ans:temp;//若temp比ans小则改ans的值为temp
            }
    return ans;
}