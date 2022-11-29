#include <fstream>
#include <iostream>
#include <memory>

using namespace std;

const char* FILE_NAME = "dump.bin";
const int SIZE = 1024 * 1024;

int main()
{
    srand(time(NULL));

    // 랜덤 값으로 초기화한다.
    shared_ptr<char> data = shared_ptr<char>(new char[SIZE]);
    for (int i = 0; i < SIZE; ++i) {
        data.get()[i] = rand() % 256;
    }

    // checksum 을 계산한다.
    unsigned int sum = 0;
    for (int i = 0; i < SIZE; ++i) {
        sum += data.get()[i];
    }

    // 파일에 쓴다.
    // 파일이 닫히지 않고 같은 파일을 열 경우 stream buffer 내용이 디스크에 없을 수도 있으므로
    // 파일을 닫게끔 scope 을 하나 올린다.
    {
        ofstream ofs(FILE_NAME, ios::binary);
        ofs.write(data.get(), SIZE);
    }

    // 파일을 읽는다.
    ifstream ifs(FILE_NAME, ios::binary);
    shared_ptr<char> data2 = shared_ptr<char>(new char[SIZE]);
    ifs.read(data2.get(), SIZE);

    // sum 을 비교한다.
    unsigned int sum2 = 0;
    for (int i = 0; i < SIZE; ++i) {
        sum2 += data2.get()[i];
    }

    if (sum == sum2) {
        cout << "Matched\n";
    }
    else {
        cout << "Not matched\n";
    }
}