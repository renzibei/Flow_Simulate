#ifndef CALCULATE_H
#define CALCULATE_H

#include <vector>
using std::vector;


class BackCompute {

    struct edge
    {
        double v; //流速
        double leng; //管道长度
        int n1,n2; //边所连接的两个节点，默认从n1流向n2
    }edges[200];
    struct node
    {
        vector<int> elist;  //点所连接的边，按照顺时针的顺序存储下来

    }nodes[200];

    vector< vector<double> > rect = vector< vector<double> >(200);//存储方程组(行列式)

    bool fr[200]; //深度搜索时判断边是否遍历过

    int n,EDGESUM,NODESUM;  //记录网格边长

    void addrect(vector<double> &tmp);

    void setedgelength(int x, double leng);

    int getdirline(int x, int y, int dir);

    bool existdir(int x, int y, int dir);

    void recursionline(int x, int y, int dir, vector<double> &tmp,int end);

    bool recursionrect(int x, int y, vector<double> &tmp,int end);

    void findline(int x, int y,int t);

    void findrect(int x1);

    void initrect();

    void getans();

public:
    vector<double> caluconspeed(int num, vector<double>&length, int i1, int i2, int o1, int o2, int o3);

};
#endif // CALCULATE_H
