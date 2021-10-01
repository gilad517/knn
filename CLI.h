#include "Commands/ClassifyingCommand.h"
#include "Commands/ConfusionMatrixCommand.h"
#include "Commands/DownloadCommand.h"
#include "Commands/PrintingCommand.h"
#include "Commands/SettingsCommand.h"
#include "Commands/UploadCommand.h"
#include "DefaultIO.h"
#include "StandardIO.h"
#include <chrono>
#include <thread>
using namespace std;

class CLI {
    private:
        static const int OPTIONNUM = 7;
        static string getMenuStr(Command** menu);
    public:
        static void start(DefaultIO* dio, int& curr_threads);
};
