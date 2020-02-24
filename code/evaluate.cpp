#include"find_move.cpp"
#include<cmath>
double evaluate(int chess[8][8],int step,int color);//对color色棋子做评估

//计算如何落子，k记录搜索层数，alpha用于剪枝
double how_to_drop(int chess[8][8],int step,int color,int k,double alpha)
{

    int dx[8]={1,-1,0,0,1,1,-1,-1},dy[8]={0,0,1,-1,1,-1,1,-1};
    int x=0,y=0,xt=0,yt=0,arrow_x=0,arrow_y=0;//记录最终走法
    double max=-10000,temp=0;//初始化
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(chess[i][j]==color)//找棋子
            {
                chess[i][j]=0;
                for(int k1=0;k1<8;k1++)
                    for(int l1=1;;l1++)//找走法
                    {
                        if(i+dx[k1]*l1>=8||j+dy[k1]*l1>=8||i+dx[k1]*l1<0||j+dy[k1]*l1<0) break;
                        if(chess[i+dx[k1]*l1][j+dy[k1]*l1]) break;//判断是否合法
                        chess[i+dx[k1]*l1][j+dy[k1]*l1]=color;
                        for(int k2=1;k2<8;k2++)
                            for(int l2=1;;l2++)//找放箭位置
                            {
                                if(i+dx[k1]*l1+dx[k2]*l2>=8||j+dy[k1]*l1+dy[k2]*l2>=8||i+dx[k1]*l1+dx[k2]*l2<0||j+dy[k1]*l1+dy[k2]*l2<0) break;
                                if(chess[i+dx[k1]*l1+dx[k2]*l2][j+dy[k1]*l1+dy[k2]*l2]) break;//判断是否合法
                                chess[i+dx[k1]*l1+dx[k2]*l2][j+dy[k1]*l1+dy[k2]*l2]=3;

                                if(k>=step/10)//若层数达到一定位置则停止，开始估值
                                    temp=evaluate(chess,step,color);
                                else//否则向下一层继续搜索
                                    temp=-how_to_drop(chess,step+1,-color,k+1,max);
                                if(alpha>=(-temp)) 
                                    {chess[i+dx[k1]*l1+dx[k2]*l2][j+dy[k1]*l1+dy[k2]*l2]=0;chess[i+dx[k1]*l1][j+dy[k1]*l1]=0;chess[i][j]=color;return 9999;}//αβ剪枝并回溯，返回9999为避免终局阶段bug
                                if(max<=temp) //最终取所有分支中得分最大的一个
                                {
                                    max=temp;
                                    if(!k) {x=i;y=j;xt=i+dx[k1]*l1;yt=j+dy[k1]*l1;arrow_x=i+dx[k1]*l1+dx[k2]*l2;arrow_y=j+dy[k1]*l1+dy[k2]*l2;}//若在第0层，则记录下走法
                                }
                                chess[i+dx[k1]*l1+dx[k2]*l2][j+dy[k1]*l1+dy[k2]*l2]=0;//回溯
                            }
                        chess[i+dx[k1]*l1][j+dy[k1]*l1]=0;//回溯
                    }
                chess[i][j]=color;//回溯
            }
    if(!k) {chess[x][y]=0;chess[xt][yt]=color;chess[arrow_x][arrow_y]=3;}//若在第0层，走出最终选择
    return max;//返回这一局面下的评估结果
}
//对color色棋子做评估
double evaluate(int chess[8][8],int step,int color)
{
    double score=0,weight[5]={0};//score记录局面得分，weight为各项权重
    if(step<=13) {weight[0]=0.14;weight[1]=0.37;weight[2]=0.13;weight[3]=0.13;weight[4]=0.2;}
    else if(step>32) {weight[0]=0.8;weight[1]=0.1;weight[2]=0.05;weight[3]=0.05;weight[4]=0;}
    else {weight[0]=0.3;weight[1]=0.25;weight[2]=0.2;weight[3]=0.2;weight[4]=0;}//分开局、中局、残局分阶段赋予权重
    int queen1[8][8]={0},king1[8][8]={0},queen2[8][8]={0},king2[8][8]={0};
    int mobility1=0,mobility2=0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            queen1[i][j]=1000; king1[i][j]=1000;
            queen2[i][j]=1000; king2[i][j]=1000;
        }//初始化步数，以1000为无穷大
    queen_move(chess,queen1,-color); king_move(chess,king1,-color);
    queen_move(chess,queen2,color); king_move(chess,king2,color);//计算queen move与king move
    mobility1=min_mobility(chess,-color); mobility2=min_mobility(chess,color);//计算最小灵活度

    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if(queen1[i][j]<queen2[i][j]) score+=(-weight[0]);
            else if(queen1[i][j]>queen2[i][j]) score+=(weight[0]);
            else if(queen1[i][j]!=1000)  score+=(-weight[0]*0.15);//计算tq，两者相等时取为0.15

            if(king1[i][j]<king2[i][j]) score+=(-weight[1]);
            else if(king1[i][j]>king2[i][j]) score+=(weight[1]);
            else if(king1[i][j]!=1000)  score+=(-weight[1]*0.15);//计算tk

            score+=weight[2]*2*(pow(0.5,queen2[i][j])-pow(0.5,queen1[i][j]));//计算pq
            
            if((king1[i][j]-king2[i][j])/5.0>1) score+=(weight[3]);
            else if((king1[i][j]-king2[i][j])/5.0<-1) score+=(-weight[3]);
            else score+=(weight[3]*(king1[i][j]-king2[i][j])/5.0);//计算pk
        }
    score+=weight[4]*(mobility2-mobility1);//计算m
    return score;
}