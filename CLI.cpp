#include "CLI.h"

bool isInt(string str)
{
    string::const_iterator it = str.begin();
    while (it != str.end() && isdigit(*it))
    {
        ++it;
    }
    return !str.empty() && it == str.end();
}

string CLI::getMenuStr(Command **menu)
{
    string toReturn = "Welcome to the KNN Classifier Server. Please choose an option:";
    for (size_t i = 0; i < OPTIONNUM - 1; i++)
    {
        toReturn += "\n" + to_string(i + 1) + ". " + menu[i]->getDescription();
    }
    toReturn += "\n" + to_string(OPTIONNUM) + ". exit";
    return toReturn;
}

void CLI::start(DefaultIO *dio, int &curr_threads)
{
    curr_threads++;
    Classifier clf;
    Command **menu = new Command *[6];
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
    bool entered1(false), entered3(false);
    for (size_t i = 0; i < OPTIONNUM - 1; i++)
    {
        menu[i]->setClassifier(&clf);
    }
    bool shouldContinue = true;
    do
    {
        this_thread::sleep_for(chrono::milliseconds(100));
        dio->write(getMenuStr(menu));
        this_thread::sleep_for(chrono::milliseconds(100));
        dio->write("please enter a message");
        string userChose(dio->read());
        if (isInt(userChose) && (stoi(userChose) > 0) && (stoi(userChose) < OPTIONNUM))
        {
            if((stoi(userChose)>=3) && (stoi(userChose)<=6) && !entered1) {
                dio->write("please input test and train files first");
                continue;
            }
            if((stoi(userChose)>=4) && (stoi(userChose)<=6) && !entered3) {
                dio->write("please classify files first");
                continue;
            }
            if(stoi(userChose) == 1){
                entered1 = true;
            }
            if(stoi(userChose) == 3){
                entered3 = true;
            }
            if (userChose.compare("5") == 0)
            {
                dio->write("please enter a message");
                string downloadPath(dio->read());
                thread thrd(DownloadCommand::activate, (DownloadCommand *)menu[4], ref(curr_threads), downloadPath);
                thrd.detach();
            }
            else
            {
                menu[stoi(userChose) - 1]->execute();
            }
        }
        else if (isInt(userChose) && (stoi(userChose) == OPTIONNUM))
        {
            shouldContinue = false;
        }
        else
        {
            dio->write("Invalid input.");
        }
    } while (shouldContinue);
    curr_threads--;
    dio->write("terminate");
}
