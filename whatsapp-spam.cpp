#include <string>
#include <unistd.h>

void send_msg(const std::string& str){
    std::string command="xdotool key ";
    for(int i=0;i<str.size();i++){
        command+=std::string(" ")+str[i];
    }
    command+=std::string(" Return");
    system(command.c_str());
    usleep(450000);
}

int main(){
    sleep(2); //wait 2 seconds
    std::string message="Hello World";
    for(int i=1;i<=100;i++){
        send_msg(message);
    }
}