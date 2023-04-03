#ifdef _WIN32
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <functional>
#include <thread>
#include <chrono>
#include <windows.h>

#define KEY_A 0x41
#define KEY_0 0x30

void sendEnter()
{

    keybd_event(VK_RETURN, 0, 0, 0);
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
}
void sendSpace()
{

    keybd_event(VK_SPACE, 0, 0, 0);
    keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
}

void sendChar(char ch)
{
    if (ch <= 'z' && ch >= 'a')
    {
        int num{ch - 'a'};
        BYTE key{static_cast<BYTE>(num + KEY_A)};
        keybd_event(key, 0, 0, 0);
        keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
    }
    else if (ch <= 'Z' && ch >= 'A')
    {
        int num{ch - 'A'};
        BYTE key{static_cast<BYTE>(num + KEY_A)};
        keybd_event(VK_LSHIFT, 0, 0, 0);
        keybd_event(key, 0, 0, 0);
        keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
        keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);
    }
    else if (ch <= '9' && ch >= '0')
    {
        int num{ch - '0'};
        BYTE key{static_cast<BYTE>(num + KEY_0)};
        keybd_event(key, 0, 0, 0);
        keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
    }
    else
    {
        switch (ch)
        {
        case ' ':
            sendSpace();
            break;
        case '\n':
            sendEnter();
            break;
        default:
            std::cout << "cant send key  : " << ch << std::endl;
        }
    }
}

void sendString(const std::string &str)
{
    for (const char &ch : str)
    {
        sendChar(ch);
    }
}

int main(int argc, char **argv)
{
    using namespace std::literals;
    if (argc <= 2)
    {
        std::cout << "usage : \n ./" << *argv << " <number of messagse> <string to send>";
        return -1;
    }

    std::stringstream ss;
    ss << *(argv + 1);
    int num_times{};
    ss >> num_times;
    if (ss.fail())
    {
        std::cout << "Second parameter is not a number. \nusage : \n ./" << *argv << " <number of messagse> <string to send>";
    }

    std::string str{""};
    for (int i{2}; i < argc; i++)
    {
        str += *(argv + i);
        str += " ";
    }
    str += "\n";

    std::cout << "shift to whatsapp web now by pressing alt+tab ? \n sending " << str.substr(0, str.length() - 1) << "in" << 3 << " ";
    std::this_thread::sleep_for(1s);
    std::cout << 2 << " ";
    std::this_thread::sleep_for(1s);
    std::cout << 1 << std::endl;
    std::this_thread::sleep_for(1s);

    while (num_times--)
        sendString(str);

    std::cout << "Victim Died xD \n press enter to exit ;)";
    std::cin.get();
}

#else // _WIN32
#include <string>
#include <unistd.h>

void send_msg(const std::string& str){
    std::string command="xdotool key ";
    for(int i=0;i<str.size();i++){
        command+=std::string(" ")+str[i];
    }
    command+=std::string(" Return");
    system(command.c_str());
    usleep(450000); // delay between each message
}

int main(){
    sleep(2); //wait 2 seconds
    std::string message="Hello World";
    for(int i=1;i<=100;i++){
        send_msg(message);
    }
}

#endif
