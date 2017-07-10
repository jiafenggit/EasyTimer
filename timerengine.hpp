/*
 * EasyTimer: A simple timer in C++.
 * carlos.ferry@undercrawl.org
 */
 
#pragma once

#include <iostream>
#include <map>
#include <time.h>
#include <sys/time.h>

class Timer;
class Manager;

/* 
 * A multimap is used, given that we might have
 * two timers at the same time.
 */

typedef std::multimap<time_t, Timer*> TimerList;

extern Manager* Engine;

class Timer
{
 
 private:
 
	/* The triggering time */
	 
	time_t trigger;

	/* Number of seconds between triggers */
	
	unsigned int interval;

	/* True if this is a repeating timer	 */
	
	bool repeat;

 public:
	
	Timer(unsigned int offset_seconds, bool repeating = false);

	/* Destructor: removes the timer from the timer manager	 */
	
	virtual ~Timer();

	/* Retrieve the current triggering time */
	
	time_t get_trigger() const
	{
		return this->trigger;
	}

	void set_trigger(time_t nexttrigger)
	{
		this->trigger = nexttrigger;
	}

	void set_new_interval(time_t interval);

	/* Runs the timer */
	
	virtual bool Tick(time_t current_time) = 0;

	/* Returns true if this timer is set to repeat	 */
	
	bool is_set_to_repeat() const
	{
		return this->repeat;
	}

	unsigned int get_interval() const
	{
		return this->interval;
	}

	void stop_repeating()
	{
		this->repeat = false;
	}
};

class  TickEngine
{
  
  private:
  	
	/* A list of all pending timers */
	
	TimerList ActiveTimers;

  public:

	/* Constructor */
	
	TickEngine();
	
	/* Destructor removes all pending timers */
	
	~TickEngine();
	
	/* Stops all remaining timers */

	void StopAll();
	
	/* Tick all pending Timers. Current time to be provided (from mainloop). */
	 
	void Synchronize(time_t current_time);

	/* Adds a new Timer */
	
	bool Push(Timer *New);

	/* Removes a Timer */
	
	void remove(Timer* removing);
	
	TimerList GetList()
	{
		return this->ActiveTimers;
	}
};

class Manager
{
    public:

     struct timespec current_time;

     TickEngine Timers;

     Manager();

     /* Retuns current time */

     inline time_t Now() 
     { 
             return this->current_time.tv_sec; 
     }

     void UpdateTime();
     
     void loop();
};

