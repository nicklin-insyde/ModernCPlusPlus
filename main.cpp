#include <iostream>
#include <array>
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string.h>
#include "sync_queue.h"
#include "tree.h"

using namespace std;

vector<int> func1(bool is_odd)
{
    if (is_odd == true) {
        vector<int> data = {1,3,5,7,9};
        return data;
    } else {
        vector<int> data = {2,4,6,8,10};
        return data;
	}
}

void test_array(void)
{
    array<int, 3> test = {100, 200, 300};
    array<array<array<int, 3>, 4>, 2> test1 =
    {
        {
            {
                {
                    { 1,  2,  3},
                    { 4,  5,  6},
                    { 7,  8,  9},
                    {10, 11, 12}
                }
            },
            {
                {
                    {13, 14, 15},
                    {16, 17, 18},
                    {19, 20, 21},
                    {22, 23, 24}
                }
            }
        }
	};
    int i=0, j=0, k=0;
    int a[] = {1,2,3,4,5};
    int *p = a;
    *(p++) += 100;
    *(++p) += 100;

    for (i=0; i<5; i++) {
        cout << "a=" << a[i] << endl;
    }
    for (i=0; i<((int)test.size()); i++) {
        cout << "test[" << i << "] = " << test.at(i) << endl;
    }
    for(i=0;i<2;i++) {
        for(j=0;j<4;j++) {
            for(k=0;k<3;k++) {
                cout << "test[" << i << "][" << j <<"]["<< k << "] = " << test1[i][j][k] << endl;
            }
        }
    }
    for(i=0;i<2;i++) {
        for(j=0;j<4;j++) {
            auto& tmp = test1[i][j];
            cout << "tmp[0] = " << tmp[0] << endl;
            tmp = move(test);
            test[1] = 453;
            //tmp = test;
        }
    }
    cout << "after ...." << endl;
    for(i=0;i<2;i++) {
        for(j=0;j<4;j++) {
            for(k=0;k<3;k++) {
                cout << "test[" << i << "][" << j <<"]["<< k << "] = " << test1[i][j][k] << endl;
            }
        }
    }

    int test10 = 49;
    int test2 = 50;
    int test3 = 51;
    cout << "test10 = " << hex << test10 << ", test2 = " << test2 << endl;
    cout << dec << "test3 = " << test3 << endl;
}

void thread_test(void)
{
    sync_queue obj;
    obj.runThread(3);
    this_thread::sleep_for(chrono::seconds(110));
    obj.terminate();
}

void test_string(void)
{
    string str;
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "/test/test/");
    str.append(buffer);
    cout << "test = "<< str.c_str() << endl;
}

typedef struct XXX {
    char buffer[32];
    char *ptr;
    int English;
    int Chinese;

    XXX ()
    {
        memset(buffer, 0,  sizeof(buffer));
        English = 100;
        Chinese = 50;
        ptr = new char[10];
        for (int i =0; i<10; i++) {
            ptr[i] = i;
        }
       printf("XXX constructor\n");
	}
    ~XXX()
    {
       printf("XXX destructor\n");
        if (ptr) {
            printf("free ptr\n");
            free(ptr);
            ptr = nullptr;
        }
	}
} MyStruct;

std::string function1(char array[])
{
    std::string name = "Nick";
    std::unique_ptr<MyStruct> temp = std::make_unique<MyStruct>();

    array[3] = 0x02;
    temp->English = 90;
    printf("English = %d\n", temp->English);
    printf("Chinese = %d\n", temp->Chinese);
    //return std::move(name);
    return name;
}

void test_smart_pointer(void)
{
    string name;
    std::unique_ptr<char[]> buffer(new char[100]);
    char *p = buffer.get();

    memset(p, 0, sizeof(char)*100);
    p[2] = 0x1;
    printf("p[2] = 0x%X \n", p[2]);
    name = function1(p);
    printf("name = %s \n", name.c_str());
    printf("p[3] = 0x%X \n", p[3]);
}

int main()
{
#if 1
    test_array();
    test_string();
    test_smart_pointer();
#else
    class avlTree tree;
    tree.function1();
    cout << "out mBBUName = " << tree.mBBUName.Value.c_str() << endl;
    if (tree.mBBUName.isPresent == true) {
        cout << "[0] out isPresent = true" << endl;
    } else {
        cout << "[0] out isPresent = false" << endl;
    }
    tree.mBBUName.Reset();
    if (tree.mBBUName.isPresent == true) {
        cout << "[1] out isPresent = true" << endl;
    } else {
        cout << "[1] out isPresent = false" << endl;
    }
#endif
    return 0;
}
