#include "timerengine.hpp"

void Timer::set_new_interval(time_t newinterval)
{
	/* As we set a new interval, this timer must be deleted first */
	
	Engine->Timers.remove(this);
	
	/* Re-sets new interval period */
	
	this->interval = newinterval;
	this->set_trigger(Engine->Now() + newinterval);

	/* Re-adds a new timer, with a new interval */
		
	Engine->Timers.Push(this);
}

Timer::Timer(unsigned int offset_seconds, bool repeating) : trigger(Engine->Now() + offset_seconds),
							    interval(offset_seconds), repeat(repeating)
{

}

Timer::~Timer()
{
	Engine->Timers.remove(this);
}

void TickEngine::StopAll()
{
	for (TimerList::iterator i = this->ActiveTimers.begin(); i != this->ActiveTimers.end(); )
        {
                this->ActiveTimers.erase(i++);
        }
}

TickEngine::TickEngine() 
{

}

TickEngine::~TickEngine()
{	
	this->StopAll();
}

void TickEngine::Synchronize(time_t current_time)
{
	for (TimerList::iterator i = this->ActiveTimers.begin(); i != this->ActiveTimers.end(); )
	{
		Timer* sync = i->second;
		
		/* Breaks if this trigger is not yet to be called */
		
		if (sync->get_trigger() > current_time)
		{
			break;
		}

		this->ActiveTimers.erase(i++);

		if (!sync->Tick(current_time))
		{
			continue;
		}

		if (sync->is_set_to_repeat())
		{
			sync->set_trigger(current_time + sync->get_interval());
			this->Push(sync);
		}
	}
}

void TickEngine::remove(Timer* removing)
{
	std::pair<TimerList::iterator, TimerList::iterator> itpair = ActiveTimers.equal_range(removing->get_trigger());

	for (TimerList::iterator i = itpair.first; i != itpair.second; ++i)
	{
		if (i->second == removing)
		{
			this->ActiveTimers.erase(i);
			break;
		}
	}
}

bool TickEngine::Push(Timer *New)
{
	this->ActiveTimers.insert(std::make_pair(New->get_trigger(), New));
	return true;
}
