#include "computethread.h"
#include "calculate.h"
#include <cstdlib>
#include <time.h>
#include <cmath>

int ComputeThread::threadCount = 0;

inline double easyRandom(int ra)
{
     int x = rand()%10; if(x < ra) return 1; return 0;

}

inline double square(double x)
{
    return x * x;
}

inline double lossFunction(vector<double> &result, vector<double> &expect)
{
    double tempResult = 0;
    for(int i = 0; i < 3; ++i)
        tempResult += square(result[i] - expect[i]);
    return sqrt(tempResult);

}

ComputeThread::ComputeThread(vector<double> w, int input1, int input2, int output1, int output2, int output3, int size):
    in1(input1), in2(input2), out1(output1), out2(output2), out3(output3), sizeNum(size), expectResult(w)
{
    srand((unsigned)time(0));
    ComputeThread::threadCount++;
    this->threadId = ComputeThread::threadCount;
    int totalSize = size * (size-1) * 2;
    this->total = totalSize;

}

void ComputeThread::switchPipe(unsigned long index)
{
    if(this->pipeLengths[index] < 0.5)
        pipeLengths[index] = 1;
    else if(this->pipeLengths[index] > 0.5)
        pipeLengths[index] = 0;
}

void ComputeThread::run()
{
    vector<double> testVectors[200], tempResult;
    BackCompute bc;
    double minLoss = 100000, tempLoss = minLoss;
    for(int k = 0; k < 200; ++k) {
        testVectors[k].resize(200);
        int ratioRate = rand()%2 + 8;
        for(int i = 0; i < this->total; ++i)
            testVectors[k].at(i) = easyRandom(ratioRate);
        for(int i = this->total; i < total + 5; ++i)
            testVectors[k].at(i) = 1;
        tempResult = bc.caluconspeed(this->sizeNum, testVectors[k], in1, in2, out1, out2, out3);
        tempLoss = lossFunction(tempResult, expectResult);
        if(tempLoss < minLoss) {
            this->pipeLengths = testVectors[k];
            minLoss = tempLoss;
        }
    }
    double loopLoss;
    for(int j = 0; j < 10; ++j) {
        qDebug("Loop %d started ", j);
        loopLoss = minLoss;
        for(int i = 0; i < this->total; ++i) {
            switchPipe(i);
            tempResult = bc.caluconspeed(this->sizeNum, pipeLengths, in1, in2, out1, out2, out3);
            tempLoss = lossFunction(tempResult, expectResult);
            if(tempLoss < minLoss) {
                minLoss = tempLoss;
                qDebug("Thread %d Loop %d i = %d loss = %lf", this->threadId, j , i, minLoss);
            }
            else switchPipe(i);
        }
        if(abs(minLoss - loopLoss) < 1e-10) {
            qDebug("Will not go");
            qDebug("Now result %lf, %lf, %lf", tempResult[0], tempResult[1], tempResult[2]);
            //this->terminate();
            //this->wait();
            break;
        }
    }
}
