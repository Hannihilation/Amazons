#include"find_move.cpp"
#include<cmath>
double evaluate(int chess[8][8],int step,int color);//��colorɫ����������

//����������ӣ�k��¼����������alpha���ڼ�֦
double how_to_drop(int chess[8][8],int step,int color,int k,double alpha)
{

    int dx[8]={1,-1,0,0,1,1,-1,-1},dy[8]={0,0,1,-1,1,-1,1,-1};
    int x=0,y=0,xt=0,yt=0,arrow_x=0,arrow_y=0;//��¼�����߷�
    double max=-10000,temp=0;//��ʼ��
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(chess[i][j]==color)//������
            {
                chess[i][j]=0;
                for(int k1=0;k1<8;k1++)
                    for(int l1=1;;l1++)//���߷�
                    {
                        if(i+dx[k1]*l1>=8||j+dy[k1]*l1>=8||i+dx[k1]*l1<0||j+dy[k1]*l1<0) break;
                        if(chess[i+dx[k1]*l1][j+dy[k1]*l1]) break;//�ж��Ƿ�Ϸ�
                        chess[i+dx[k1]*l1][j+dy[k1]*l1]=color;
                        for(int k2=1;k2<8;k2++)
                            for(int l2=1;;l2++)//�ҷż�λ��
                            {
                                if(i+dx[k1]*l1+dx[k2]*l2>=8||j+dy[k1]*l1+dy[k2]*l2>=8||i+dx[k1]*l1+dx[k2]*l2<0||j+dy[k1]*l1+dy[k2]*l2<0) break;
                                if(chess[i+dx[k1]*l1+dx[k2]*l2][j+dy[k1]*l1+dy[k2]*l2]) break;//�ж��Ƿ�Ϸ�
                                chess[i+dx[k1]*l1+dx[k2]*l2][j+dy[k1]*l1+dy[k2]*l2]=3;

                                if(k>=step/10)//�������ﵽһ��λ����ֹͣ����ʼ��ֵ
                                    temp=evaluate(chess,step,color);
                                else//��������һ���������
                                    temp=-how_to_drop(chess,step+1,-color,k+1,max);
                                if(alpha>=(-temp)) 
                                    {chess[i+dx[k1]*l1+dx[k2]*l2][j+dy[k1]*l1+dy[k2]*l2]=0;chess[i+dx[k1]*l1][j+dy[k1]*l1]=0;chess[i][j]=color;return 9999;}//���¼�֦�����ݣ�����9999Ϊ�����վֽ׶�bug
                                if(max<=temp) //����ȡ���з�֧�е÷�����һ��
                                {
                                    max=temp;
                                    if(!k) {x=i;y=j;xt=i+dx[k1]*l1;yt=j+dy[k1]*l1;arrow_x=i+dx[k1]*l1+dx[k2]*l2;arrow_y=j+dy[k1]*l1+dy[k2]*l2;}//���ڵ�0�㣬���¼���߷�
                                }
                                chess[i+dx[k1]*l1+dx[k2]*l2][j+dy[k1]*l1+dy[k2]*l2]=0;//����
                            }
                        chess[i+dx[k1]*l1][j+dy[k1]*l1]=0;//����
                    }
                chess[i][j]=color;//����
            }
    if(!k) {chess[x][y]=0;chess[xt][yt]=color;chess[arrow_x][arrow_y]=3;}//���ڵ�0�㣬�߳�����ѡ��
    return max;//������һ�����µ��������
}
//��colorɫ����������
double evaluate(int chess[8][8],int step,int color)
{
    double score=0,weight[5]={0};//score��¼����÷֣�weightΪ����Ȩ��
    if(step<=13) {weight[0]=0.14;weight[1]=0.37;weight[2]=0.13;weight[3]=0.13;weight[4]=0.2;}
    else if(step>32) {weight[0]=0.8;weight[1]=0.1;weight[2]=0.05;weight[3]=0.05;weight[4]=0;}
    else {weight[0]=0.3;weight[1]=0.25;weight[2]=0.2;weight[3]=0.2;weight[4]=0;}//�ֿ��֡��о֡��оַֽ׶θ���Ȩ��
    int queen1[8][8]={0},king1[8][8]={0},queen2[8][8]={0},king2[8][8]={0};
    int mobility1=0,mobility2=0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            queen1[i][j]=1000; king1[i][j]=1000;
            queen2[i][j]=1000; king2[i][j]=1000;
        }//��ʼ����������1000Ϊ�����
    queen_move(chess,queen1,-color); king_move(chess,king1,-color);
    queen_move(chess,queen2,color); king_move(chess,king2,color);//����queen move��king move
    mobility1=min_mobility(chess,-color); mobility2=min_mobility(chess,color);//������С����

    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if(queen1[i][j]<queen2[i][j]) score+=(-weight[0]);
            else if(queen1[i][j]>queen2[i][j]) score+=(weight[0]);
            else if(queen1[i][j]!=1000)  score+=(-weight[0]*0.15);//����tq���������ʱȡΪ0.15

            if(king1[i][j]<king2[i][j]) score+=(-weight[1]);
            else if(king1[i][j]>king2[i][j]) score+=(weight[1]);
            else if(king1[i][j]!=1000)  score+=(-weight[1]*0.15);//����tk

            score+=weight[2]*2*(pow(0.5,queen2[i][j])-pow(0.5,queen1[i][j]));//����pq
            
            if((king1[i][j]-king2[i][j])/5.0>1) score+=(weight[3]);
            else if((king1[i][j]-king2[i][j])/5.0<-1) score+=(-weight[3]);
            else score+=(weight[3]*(king1[i][j]-king2[i][j])/5.0);//����pk
        }
    score+=weight[4]*(mobility2-mobility1);//����m
    return score;
}