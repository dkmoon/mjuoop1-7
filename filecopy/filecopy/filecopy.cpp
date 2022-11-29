#include <fstream>
#include <string>
#include <iostream>


using namespace std;


int main(int argc, char* argv[]) {
	// argv[0]: 경로포함 실행 파일 이름
	// argv[1]: 원본 파일
	// argv[2]: 복사될 파일
	// 따라서 argc 는 3이어야 한다.
	if (argc != 3) {
		cerr << "Not enough arguments\n";

		// 정상 종료가 아닐 때는 0 이 아닌 오류 코드를 반환하는 것이 관례다.
		// 보통 오류에 따라 1, 2, 3, ... 이렇게 올려간다.
		// 정수 숫자 자체를 쓰고 싶지 않으면 enum 이나 const int 로 지정해서 쓸 것
		return 1;
	}

	string src{ argv[1] };
	string dst{ argv[2] };

	ifstream ifs(src, ios::binary);
	ofstream ofs(dst, ios::binary);


#if true
	// 방법1: get() 과 put() 을 써서 한 바이트씩 읽고 쓴다.
	char c;
	while (ifs.get(c)) {
		ofs.put(c);
	}
#endif


#if false
	// 방법2: read() 와 write() 로 여러 바이트를 읽는다.
	//        이 때 마지막 부분에는 원하는 바이트 만큼 못 읽고 EOF 를 읽게 되면
	//        while 문을 탈출하게 되니 최종적으로 읽은 것이 있는지 확인해서 그것까지 써준다.
	char buf[4096];
	while (true) {
		ifs.read(buf, sizeof(buf));
		// sizeof(buf) 만큼 읽으라고 요청했으나 그 이하일 수도 있다.
		// 따라서 gcount 로 실제 읽은만큼만 ofs 에 쓴다.
		int numRead = ifs.gcount();
		ofs.write(buf, numRead);

		// 일부 데이터를 읽고 EOF 를 만났을 수도 있다.
		if (!ifs) {
			break;
		}
	}
#endif


#if false
	// 방법3: file size 를 미리 알아내서 그 만큼의 buffer 를 확보한 후 쓰기

	// ifstream 의 seekg(ios::end) 를 호출하면 file 의 맨 끝으로 이동한다.
	ifs.seekg(0, ios::end);

	// tellg() 는 현재 위치가 파일의 어디쯤인지 byte 단위로 반환한다.
	// 따라서 seekg(ios::end) 후에 tellg() 를 하면 file 사이즈를 알 수 있다.
	int numBytes = ifs.tellg();
	cout << numBytes << endl;

	// 다시 file 의 처음(= beg)으로 이동한다.
	ifs.seekg(0, ios::beg);

	char* data = new char[numBytes];
	ifs.read(data, numBytes);
	ofs.write(data, numBytes);
#endif
}