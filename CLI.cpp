#include "Commands/ClassifyingCommand.h"
#include "Commands/ConfusionMatrixCommand.h"
#include "Commands/DownloadCommand.h"
#include "Commands/PrintingCommand.h"
#include "Commands/SettingsCommand.h"
#include "Commands/UploadCommand.h"
#include "DefaultIO.h"
#include "StandardIO.h"
using namespace std;

class CLI {
    private:
        static const int OPTIONNUM = 7;
        static bool isInt(string str) {
            string::const_iterator it = str.begin();
            while (it != str.end() && isdigit(*it)) {
                ++it;
            }
            return !str.empty() && it == str.end();
        }

        static string getMenuStr(Command** menu) {
            string toReturn = "Welcome to the KNN Classifier Server. Please choose an option:";
            for (size_t i = 0; i < OPTIONNUM-1; i++)
            {
                toReturn+="\n" + to_string(i+1) + ". " + menu[i]->getDescription();
            }
            toReturn+="\n" + to_string(OPTIONNUM) + ". exit";
            return toReturn;
        }
    public:
        static void start(DefaultIO *dio) {
            Classifier clf;
            Command** menu = new Command*[6];
            UploadCommand uploadCommand(dio);
            SettingsCommand settingsCommand(dio);
            ClassifyingCommand classifyingCommand(dio);
            PrintingCommand printingCommand(dio);
            DownloadCommand downloadCommand(dio);
            ConfusionMatrixCommand confusionMatrixCommand(dio);
            menu[0] = &uploadCommand;
            menu[1] = &settingsCommand;
            menu[2] = &classifyingCommand;
            menu[3] = &printingCommand;
            menu[4] = &downloadCommand;
            menu[5] = &confusionMatrixCommand;
            for (size_t i = 0; i < OPTIONNUM-1; i++)
            {
                menu[i]->setClassifier(&clf);
            }
            bool shouldContinue = true;
            do
            {
                dio->write(getMenuStr(menu));
                string userChose(dio->read());
                if(isInt(userChose)&&(stoi(userChose)>0)&&(stoi(userChose)<OPTIONNUM))
                {
                    menu[stoi(userChose) - 1]->execute();
                }
                else if (isInt(userChose)&&(stoi(userChose)==OPTIONNUM))
                {
                    shouldContinue = false;
                }
                else {
                    dio->write("Invalid input.");
                }
            } while (shouldContinue);
        }
};

int main(){
    StandardIO sio;
    CLI::start(&sio);
}