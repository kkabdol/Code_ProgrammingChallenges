ACM Online Judge 개발 가이드

Command Line Utility 프로젝트에서 파일 입력 사용하는 방법

1. Target -> Build Phrases -> Copy Files
    - Destination : Executables
    - Subpath : ""
    - 입력받고자 하는 파일을 등록. 예:testcase.txt
    
2. fstream 참조
#ifndef ONLINE_JUDGE
#include <fstream>
#endif

using namespace std;

3. istream in 생성 
int main()
{
    istream in(cin.rdbuf());
#ifndef ONLINE_JUDGE
    ifstream fin("testcase.txt");  // declarations of streams fp_in and fp_out
    if (fin) {
        in.rdbuf(fin.rdbuf());
    } else {
        cout << "can not read testcase.txt" << endl;
    }
    
#endif

    ...

#ifndef ONLINE_JUDGE
    fin.close();
#endif
}

4. cin 대신 in으로 입력받기
    while(in >> n >> m) {
        if (n == 0 && m == 0) {
            break;
        }
        
        ...
        
        cout << endl;
    }
    
