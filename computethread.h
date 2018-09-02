#ifndef COMPUTETHREAD_H
#define COMPUTETHREAD_H

#include <QObject>
#include <QThread>
#include <vector>


using std::vector;

class ComputeThread : public QThread
{
    Q_OBJECT
public:
    ComputeThread(vector<double> w, int input1, int input2, int output1, int output2, int output3, int size);

protected:
    int in1, in2, out1, out2, out3, sizeNum, total;
    static int threadCount;
    int threadId;
    void run();
    void switchPipe(unsigned long index);
    vector<double> pipeLengths, expectResult;
};

#endif // COMPUTETHREAD_H
