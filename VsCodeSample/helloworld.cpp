#include <iostream>
#include <vector>
#include <string>
#include "System.hxx"

using namespace std;

int main()
{
#define MAX_HOST_COUNT 4
    std::vector<std::unique_ptr<System>> _system;    
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
    cout << "shit" << endl;
    for (int i=0; i<MAX_HOST_COUNT; i++) {
        _system.push_back(make_unique<System>(i));
    }
}