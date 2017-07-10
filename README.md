### EasyTimer: A basic, yet useful timer.

This is a timer written in C++. You might use it in order to run and/or repeat 
processes at a later time.

### Compiling:

To compile, run 

```
make 
```

### Example (main.cpp):

```C++
 
 class Demo : public Timer
 {
    public:

       Demo(unsigned int trigger, bool repeat = true) : Timer(trigger, repeat)
       {

       }

       bool Tick(time_t current_time)
       {
               std::cout << "Testing demo, interval is set to: " << this->get_interval() << std::endl;
       }
 };

  /* 
   * Will run Demo class every 2 seconds. 
   * Second parameter is set to "true", which means 
   * that this timer will unlimitedly repeat. If set to false,
   * it will only run once before being removed
   * from pending timers.
   */

  Demo* demo1 = new Demo(2, true);

  Engine->Timers.Push(demo1);


```
	
