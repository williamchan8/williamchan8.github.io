#include <iostream>


using namespace std;

class Queue; 

class Runner {

    public:
        Runner();
        ~Runner(); 
        void addPlayers();
        void start();
        void stop();
    private:
        static void* player(void * param);

};