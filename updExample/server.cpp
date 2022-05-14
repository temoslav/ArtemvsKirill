

#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

using namespace std;


class CommandStrategy {
public:
    virtual string getCommand()  = 0;
};

class ConsolCommandStrategy : public CommandStrategy {
public:
     string getCommand() override {
        string cmd;
        cin >> cmd;
        return cmd;
    }
};

class NetCommandStrategy : public CommandStrategy {
private:
    SOCKADDR_IN addr;
    int sListen;
    int newConnection;
    char msg[256];


public:


    NetCommandStrategy() {
        //WSAStartup
        WSAData wsaData;
        WORD DLLVersion = MAKEWORD(2, 1);
        if (WSAStartup(DLLVersion, &wsaData) != 0) {
            cout << "Error" << '\n';
            // return 1;
        };


        SOCKADDR_IN addr;
        int sizeofaddr = sizeof(addr);
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        addr.sin_port = htons(3425);
        addr.sin_family = AF_INET;


         sListen = socket(AF_INET, SOCK_STREAM, NULL);

        bind(sListen, (SOCKADDR*)&addr, sizeof(addr));


        listen(sListen, SOMAXCONN);


         newConnection;
        newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
        if (newConnection == 0) {
            cout << "Error soedin";
        }
        else {
            cout << "Client Connection!!" << '\n';
        };

    }

     string getCommand() override {
        string cmd;
        recv(newConnection, msg, sizeof(msg), NULL);
        cmd = msg;
        return cmd;
    
    }

    string recive() {
        char msg[256];
        char maa[] = "VVEDITE COMANDY";
        recv(newConnection, msg, sizeof(msg), NULL);
        cout << msg;
        return msg;

    }



};

enum RobotState {
    WHAIT,
    ON,
    OFF,
    CLEAN,
    DETECT,
    TURN,
    MOVE,
};

class Robot {
private:
    RobotState state;
    CommandStrategy* strat;
public:
    Robot(CommandStrategy* pstrat): state(WHAIT), strat(pstrat) {}
    ~Robot() {
        delete strat;
    }

    RobotState getState() {
        return state;
    }

    void setState(RobotState state) {
        this->state = state;
    }

    string setCommand() {
        return strat->getCommand();
    }


    void engineOn() {
        cout << "Engine ON " << '\n';
    }

    void engineOFF() {
        cout << "Engine OFF " << '\n';
    }

    void clean() {
        cout << "Clean" << '\n';
    }

    void move() {
        cout << "Arrived at the destination" << '\n';
    }

    void turn(double angle) {
        cout << "Turn " << angle << " degrees" << '\n';
    }


    void WaitCommand(const string& command) {
        if (command == "ON") {
            state = RobotState::ON;
            processEvent(state);
        }
        if (command == "CLEAN") {
            state = RobotState::CLEAN;
            processEvent(state);
        }
        if (command == "TURN") {
            state = RobotState::TURN;
            processEvent(state);
        }
        if (command == "MOVE") {
            state = RobotState::MOVE;
            processEvent(state);
        }
        if (command == "OFF") {
            state = RobotState::OFF;
            processEvent(state);
        }
    }

    void nextWaitCommand(RobotState& nstate) {
        cout << "Command completed"  << '\n';
        state = WHAIT;
        cout << '\n' << "Waiting for the command" << '\n';
    }

    void processEvent(RobotState& state) {
        string;
        switch (state) {
        case ON:
            engineOn();
            nextWaitCommand(state);
            break;
        case CLEAN:
            clean();
            nextWaitCommand(state);
            break;
        case MOVE:
            double distance;
            //setCommand();
            //cin >> distance;
            move();
            nextWaitCommand(state);
            break;
        case TURN:
            double angle;
            cin >> angle;
            turn(angle);
            nextWaitCommand(state);
            break;
        case OFF:
            engineOFF();
            break;
        }

    }
};



int main()
{
    Robot* p;
    p = new Robot (new NetCommandStrategy());

    p->setState(RobotState::WHAIT);

    cout << "Waiting for the command" << '\n';
    while (p->getState() == WHAIT) {
        string cm = p->setCommand();
        p->WaitCommand(cm);
    }
    return 0;
}




