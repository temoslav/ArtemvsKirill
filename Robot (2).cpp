
#include <iostream>
#include<conio.h>
using namespace std;


class CommandStrategy {
public:
    virtual string getCommand() = 0;
};

class ConsolCommandStrategy : public CommandStrategy {
public:
    virtual string getCommand() override {
        string cmd;
        cin >> cmd;
        return cmd;
    }
};

class NetCommandStrategy : public CommandStrategy {
public:
    string getCommand() override {
        string cmd;
        //cmd = recive();
        return cmd;
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
    Robot(CommandStrategy* strat) {}

    RobotState getState() {
        return state;
    }

    void setState(RobotState state) {
        this->state = state;
    }

    string getCommand() {
        string cm;
        cin >> cm;
        return cm;
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

    void move(double distance) {
        cout << "At the destination" << '\n';
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
        cout << "Command completed" << state << '\n';
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
            cin >> distance;
            move(distance);
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
    Robot p(new ConsolCommandStrategy);
    p.setState(RobotState::WHAIT);

    cout << "Waiting for the command" << '\n';
    while (p.getState() == WHAIT) {
        string cm = p.getCommand();
        p.WaitCommand(cm);
    }
}




