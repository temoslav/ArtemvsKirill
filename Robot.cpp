/*




*/




#include <iostream>
#include<conio.h>
using namespace std;

enum RobotState {
    ON,
    OFF,
    CLEAN,
    DETECT,
    MOVE,
};

class Move{
private:
    int distance_x;
    int distance_y;
    bool place = false;
public:
    void moveRob(int* graf_x, int* graf_y, int* rob_x, int* rob_y) {
       // distance_x = *rob_x + *graf_x;
        //cout << distance_x;
        //if (distance_x > 0)
        while (place!= true) {
            if (*graf_x == *rob_x || *graf_y == *rob_y) {
                cout << "NA MESTE" << endl;
                place = true;
            }
        }
    }

};

class SprayGun {
public:
    void cleanGraf() {
        bool graf = true;
        if (graf) {
            cout << "Sprey RABOTAET";
        }
        else
            cout << "VSE CHISTO";
    
    };
};

class Camera {
public:
    void detect(int*graf_x,  int* graf_y) {
        *graf_x = 20;
        *graf_y = 30;
    }
};

class Engine {
public:
    void on() {};
    void off() {};
};


class System {
private:
    Camera cm;
    SprayGun gun;
    Move mv;
    Engine en;
    RobotState State;
    int graf_x = 0 , graf_y = 0, rob_x = 20, rob_y = 30;
    bool graf;
public:

    void SetState (RobotState State) {
        this->State = State;
    }

    void StartEndine() {
        en.on();
        cout << "Rabotaet eng";
    }

    void StopEngine() {
        en.off();
    }

    void move() {
        mv.moveRob(&graf_x,&graf_y, &rob_x, &rob_y);
    
   }
    void spray() {
        gun.cleanGraf();
    
    }

    void detect() {
        cm.detect(&graf_x, &graf_y);
        cout << graf_x;
    }

    void command() {
        char a;
        a = _getch();
        switch (a) {
        case 's':
            SetState(RobotState::ON);
            break;
        case 'e':
            SetState(RobotState::OFF);
            break;
        case 'd':
            SetState(RobotState::DETECT);
            break;
        case 'a':
            SetState(RobotState::MOVE);
            break;
        case 'q':
            SetState(RobotState::CLEAN);
            break;
        };
    
    }
  
   
    RobotState GetState() {
        while (State != OFF)
        {
        command();
            switch (State) {
            case RobotState::ON:
                cout << "Rabotaet";
                StartEndine();
                break;

            case RobotState::DETECT:
                detect();
                break;

            case RobotState::MOVE:
                move();
                break;
            case RobotState::CLEAN:
                spray();
                break;
            }
        }
        switch (State) {
        case RobotState::OFF:
            cout << "NE RABOTAET";
            StopEngine();
        }
         return State;
    }  
};


int main()
{
    System st;
    st.command();
    st.GetState();

    return 0;
}