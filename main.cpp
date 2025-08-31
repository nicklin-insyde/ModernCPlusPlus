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
            printf("delete ptr\n");
            delete ptr;
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

void test_string_to_char(void)
{
    vector<string> id;
    const char *test[3] = {"String1", "String2", "String3"};

    id.push_back("mId0000");
    id.push_back("mId0001");
    id.push_back("mId0002");
    id.push_back("mId0003");
    id.push_back("mId0004");

    for (auto it = id.begin(); it != id.end(); ++it) {
        std::cout << *it << std::endl;
    }
    for (const char*& it : test) {
        printf("test string[%s]\n", it);
    }

    vector<const char*> target;
    for (const std::string& it : id) {
        target.push_back(it.c_str());
    }
    for (const char*& it : target) {
        printf("string = %s\n", it);
    }
}
struct dimm_info
{
#define MAX_SIZE 10
    int smart_ptr_size;
    unsigned char serial_number;
    unsigned char data1;
    unsigned char data2;
    unsigned char data3;
    unsigned char data4;
    unsigned char data5;
    char *ptr;
    std::unique_ptr<char[]> smart_ptr;
    std::string number;

    dimm_info(unsigned char sn, unsigned char arg1, unsigned char arg2, const int max_size):dimm_info(sn, arg1, arg2)
    {
        smart_ptr_size = max_size;
        smart_ptr = make_unique<char[]>(smart_ptr_size);
        char *p = smart_ptr.get();
        for (int i=0; i<smart_ptr_size; i++) {
            p[i] = i;
        }
        printf("dimm_info constructor 3 - sn[0x%02X] - [0x%02X, 0x%02X, 0x%02X]\n",
                                                       serial_number, data1, data2, max_size);
    }

    dimm_info(unsigned char sn, unsigned char arg1, unsigned char arg2):dimm_info()
    {
        serial_number = sn;
        data1 = arg1;
        data2 = arg2;
        printf("dimm_info constructor 2 - sn[0x%02X] - [0x%02X, 0x%02X]\n",
                                                       serial_number, data1, data2);
    }

    dimm_info()
    {
        smart_ptr_size = 0;
        serial_number = 0;
        data1 = 0;
        data2 = 1;
        data3 = 2;
        data4 = 3;
        data5 = 4;
        number = "16627697";
        smart_ptr = nullptr;
        ptr = new char[MAX_SIZE];
        for (int i =0; i<MAX_SIZE; i++) {
            ptr[i] = i;
        }
        printf("dimm_info constructor 1\n");
    }
    ~dimm_info()
    {
        printf("dimm_info deconstructor - 0x%02X\n", serial_number);
        if (ptr) {
            printf("delete ptr\n");
            delete ptr;
            ptr = nullptr;
        }
    }
};

class Controller
{
public:
    Controller()
    {
        printf("Controller constructor\n");
    }

    ~Controller()
    {
        printf("Controller deconstructor\n");
    }

    void add_dimm1(std::unique_ptr<struct dimm_info> &info) { _dimm.push_back(std::move(info)); }
    void add_dimm2(std::unique_ptr<struct dimm_info>  info) { _dimm.push_back(std::move(info)); }
    void traversal(void)
    {
        printf("traversal ---\n");
        for (auto &it : _dimm) {
            printf("Start -----------\n");
            printf("(sn, 1, 2, 3, 4, 5) = (0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X)\n",
                                         it->serial_number, it->data1, it->data2, it->data3, it->data4, it->data5);
            if (it->ptr) {
                for (int i=0; i<MAX_SIZE; i++) {
                    printf("ptr[%d]=0x%02X\n", i, it->ptr[i]);
                }
            }
            char *p = it->smart_ptr.get();
            if (p == nullptr) {
                printf("smart_ptr is nullptr\n");
            } else {
                printf("size = %ld\n", strlen(p));
                for (int i=0; i<it->smart_ptr_size; i++) {
                    printf("smart_ptr[%d]=0x%02X\n", i, p[i]);
                }
            }
            printf("End -----------\n");
        }
    }

private:
    std::vector<std::unique_ptr<struct dimm_info>> _dimm;
};


void test_smart_pointer_and_vector(void)
{
    std::unique_ptr<Controller> raid = std::make_unique<Controller>();
    std::unique_ptr<struct dimm_info> p0 = std::make_unique<struct dimm_info>();
    std::unique_ptr<struct dimm_info> p1 = std::make_unique<struct dimm_info>(0x20, 0x01, 0x02);
    raid->add_dimm1(p0);
    raid->add_dimm1(p1);
    raid->add_dimm2(std::make_unique<struct dimm_info>(0x21, 0x08, 0x09));
    raid->add_dimm2(std::make_unique<struct dimm_info>(0x22, 0x0A, 0x0B, 16));
    if ((p0 == nullptr) && (p1 == nullptr)) {
        printf("OOOPS! \n");
    }
    raid->traversal();
}

int main()
{
#if 1
    //test_array();
    //test_string();
    //test_smart_pointer();
    test_string_to_char();
    test_smart_pointer_and_vector();
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
