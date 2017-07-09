### EasyTimer: A basic timer in C++

This is a basic timer written in C++. You might use it to run and/or repeat 
processes at a later time.

### Compiling:

To compile, run 

```
make -j2
```

### Adding a timer:

```C++
  
  /* 
   * Will run demo class every 2 seconds. 
   * second parameter "true" means that this 
   * timer will repeat.
   */

  Demo* demo1 = new Demo(2, true);

  Engine->Timers.Push(demo1);


```
	
