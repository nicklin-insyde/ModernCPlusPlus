//#include <vector>
#include <memory>

class System
{
public:
    System(const int idx);
    ~System();

    bool check_status(void) { return _isInitOk; }
    bool UnInit();
private:
    int _idx;
    bool _isInitOk;
    //struct system_config _cfg;

    bool Init();
    //vector<unique_ptr<Storage>> mStorageContainer;
};