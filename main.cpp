#include <unistd.h>
#include "timerengine.hpp"

Manager* Engine = NULL;

Manager::Manager()
{
     Engine = this;
}

void Manager::UpdateTime()
{
       struct timeval tv;
       gettimeofday(&tv, NULL);
       this->current_time.tv_sec = tv.tv_sec;
}

class Demo : public Timer
{
    public:
       
       Demo(unsigned int trigger, bool repeat = true) : Timer(trigger, repeat)
       {
       
       }
       
       bool Tick(time_t current_time)
       {	
               std::string rep;
               
               if (this->is_set_to_repeat())
               {
                     rep = "This timer will repeat";
               }
               else
               {
                     rep = "This is the last time that this timer will run";
               }
               
               std::cout << "Testing demo, interval is set to: " << this->get_interval() << " " << rep << std::endl;
       }
};

void Manager::loop()
{
        this->UpdateTime();
        
        time_t previous_time = this->current_time.tv_sec;

        /* Main loop. Keeps UnderInstance running. */

        do
        {
                this->UpdateTime();
                
                if (this->current_time.tv_sec != previous_time)
                {
                        previous_time = this->current_time.tv_sec;
                        
                        /* Tick timers */

                        this->Timers.Synchronize(this->current_time.tv_sec);
                }
                    
                sleep(1);
        }
        while (true);
}

int main()
{
       new Manager();
       
       /* Meant to run in two seconds from current time. Repeating set to true. */
       
       Demo* demo1 = new Demo(2, true);
       
       /* Adds timer to timer's queue vector */
     
       Engine->Timers.Push(demo1);
       
       Demo* demo2 = new Demo(10, true);
       
       Engine->Timers.Push(demo2);
       
       /* Meant to run in five seconds from now. This timer will only have one cycle */
     
       Demo* demo3 = new Demo(5, false);
       
       Engine->Timers.Push(demo3);
       
       /* Let's loop. */
       
       Engine->loop();
}
