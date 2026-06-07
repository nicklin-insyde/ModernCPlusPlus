#include <iostream>
#include "System.hxx"

using namespace std;

System::System(const int idx) : _idx(idx)
{
    //_cfg = arg._host[idx]; // copy the configuration from class Configuration

    //mStorageContainer.push_back(make_unique<Storage>(_cfg.storage));
    _isInitOk = this->Init();
}

bool System::Init(void)
{
    bool ret = false;
/*
    for (auto &it : mStorageContainer) {
        //
        // refer to Storage::Init()
        //
        ret = it->Init();
        if (ret == false)
            break;
    }
*/
    return ret;
}

bool System::UnInit(void)
{
    return false;
}

System::~System()
{
    cout << "System::~System()" << "_idx = " << _idx << endl;
}
