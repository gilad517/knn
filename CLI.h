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
/**
 * @brief The CLI class is the interface the client is shown from the server.
 * 
 */

class CLI {
    private:
        //The number of available options in the menu
        static const int OPTIONNUM = 7;

        /**
         * @brief A method to get the Menu string given the wanted commands in it
         * 
         * @param menu An array of the wanted commands in the menu
         * @return string The menu string
         */
        static string getMenuStr(Command** menu);
    public:
        /**
         * @brief The method that controlls the menu and its operation
         * 
         * @param dio A defualt io to use for all server-client communications
         * @param curr_threads The number of threads currently at work
         */
        static void start(DefaultIO* dio, int& curr_threads);
};
