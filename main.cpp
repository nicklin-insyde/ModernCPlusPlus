#include <iostream>
#include <array>
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string.h>
#include <semaphore.h>
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
    vector<int> id_int;
    vector<string> id;
    const char *test[3] = {"String1", "String2", "String3"};

    id.push_back("mId0000");
    id.push_back("mId0001");
    id.push_back("mId0002");
    id.push_back("mId0003");
    id.push_back("mId0004");

    id_int.push_back(1);
    id_int.push_back(2);
    id_int.push_back(3);
    id_int.push_back(4);

    for (auto it : id_int) {
        std::cout << "int = " << it << std::endl;
    }

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

typedef struct {
    int test1;
    int test2;
    int test3;
    int test4;
} MR8_BITMAP;

class Controller
{
public:
    Controller()
    {
        bitmap = nullptr;
        printf("Controller constructor\n");
    }

    ~Controller()
    {
        printf("Controller deconstructor\n");
        while (!_dimm_old.empty()) {
            struct dimm_info *p = _dimm_old.back();
            _dimm_old.pop_back();
            if (p != nullptr){
                printf("delete _dimm_old sn[0x%02X] \n", p->serial_number);
                delete p;
                p = nullptr;
            }
        }
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

    void add_dimm3(struct dimm_info *p) { _dimm_old.push_back(p); }

    void traversal_dimm_old(void)
    {
        for(auto it : _dimm_old) {
            printf("it->sn = 0x%02X\n", it->serial_number);
        }
    }

    void create_MR8_BITMAP(void)
    {
        std::unique_ptr<MR8_BITMAP> local = std::make_unique<MR8_BITMAP>();
        local->test1 = 1;
        local->test2 = 2;
        local->test3 = 3;
        local->test4 = 4;
        printf("local->test1 = %d\n", local->test1);
        printf("local->test2 = %d\n", local->test2);
        printf("local->test3 = %d\n", local->test3);
        printf("local->test4 = %d\n", local->test4);
        bitmap = std::move(local);
        if (local == nullptr) {
            printf("local is nullptr\n");
        } else {
            printf("local is NOT nullptr\n");
        }
    }

    void show_bitmap(void)
    {
        if (bitmap == nullptr) {
            printf("bitmap is nullptr\n");
            return;
        }
        bitmap->test1 = 234;
        printf("bitmap->test1 = %d\n", bitmap->test1);
        printf("bitmap->test2 = %d\n", bitmap->test2);
        printf("bitmap->test3 = %d\n", bitmap->test3);
        printf("bitmap->test4 = %d\n", bitmap->test4);
    }

private:
    std::unique_ptr<MR8_BITMAP> bitmap;

    std::vector<std::unique_ptr<struct dimm_info>> _dimm;
    std::vector<struct dimm_info *> _dimm_old;
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
    struct dimm_info *test1 = new struct dimm_info(0x23, 0x0F, 0x0E, 23);
    struct dimm_info *test2 = new struct dimm_info(0x24, 0xFF, 0x1E, 25);
    raid->add_dimm3(test1);
    raid->add_dimm3(test2);
    raid->traversal_dimm_old();
}

void test_transfer_ownership_of_unique_ptr()
{
    std::unique_ptr<Controller> controller = std::make_unique<Controller>();
    controller->show_bitmap();
    controller->create_MR8_BITMAP();
    controller->show_bitmap();
}

int CreateThread(void * (*entry_function)(void*), void *arg)
{
    int rval = -1, ret = 0;
    pthread_t       p_thread;
    pthread_attr_t  attr;
 
    //Have to create threads as daemon (in detached state) otherwise hit a limit in Linux
    if(0 == (ret = pthread_attr_init(&attr))) {
        if(0 == (ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))) {
            if( 0 == (ret = pthread_create(&p_thread, &attr, entry_function, (void *)arg))) {
                rval = 0;
            } else {
                printf("%s: pthread_create failed, ret:0x%x, errno:0x%x", __func__, ret, errno);
            }
        } else {
            printf("%s: pthread_attr_setdetachstate failed, ret:0x%x, errno:0x%x", __func__, ret, errno);
        }
        if (0 != (ret = pthread_attr_destroy(&attr))) {
            printf("%s: pthread_attr_destroy failed, ret:0x%x, errno:0x%x", __func__, ret, errno);
        }
    } else {
        printf("%s: pthread_attr_init failed, ret:0x%x, errno:0x%x", __func__, ret, errno);
    }
    return rval;
}

typedef struct _ThreadArgs {
    int argc;
    void *argv[32];
    sem_t sem;
} ThreadArgs;

void *ControllerFWUpdateThread(void *pArg)
{
    ThreadArgs *tmp = (ThreadArgs *)pArg;
    int argc = tmp->argc;
    printf("argc=%d\n", argc);
    for (int i=0; i<argc; i++) {
        printf("[%d/%d] - %s\n", i, argc, (char *)tmp->argv[i]);
    }
    printf("[1] b4 sema_post\n");
    sem_post(&tmp->sem);
    printf("[1] aft sema_post\n");
    return NULL;
}

void test_pthread()
{
    int ret = 0;
    ThreadArgs *args = (ThreadArgs *)malloc(sizeof(ThreadArgs));
    memset(args, 0, sizeof(ThreadArgs));
    args->argc = 3;
    args->argv[0] = (void *) strdup("test one");
    args->argv[1] = (void *) strdup("test two");
    args->argv[2] = (void *) strdup("test three");
    ret = CreateThread(ControllerFWUpdateThread, (void *)args);
    if (ret != 0) {
        printf("failed to create pthread\n");
    } else {
        printf("pthread is created - OK\n");
        printf("[0] b4 sem_wait\n");
        sem_wait(&args->sem);
        printf("[0] after sem_wait\n");
    }
    //
    // garbage clean
    //
    for (int i=0; i<3; i++) {
        if (args->argv[i]) {
            free(args->argv[i]);
            args->argv[i] = nullptr;
        }
    }
    free(args);
    args = nullptr;
}

int main()
{
#if 1
    //test_array();
    //test_string();
    //test_smart_pointer();
    //test_string_to_char();
    //test_smart_pointer_and_vector();
    //test_transfer_ownership_of_unique_ptr();
    test_pthread();
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
