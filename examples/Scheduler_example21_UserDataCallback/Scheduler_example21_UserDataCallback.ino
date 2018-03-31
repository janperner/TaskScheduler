/** 
 *  TaskScheduler Test w/ user_data void * in the timer callback
 */

#include <TaskScheduler.h>

// Callback methods prototypes
void t1Callback(void *userData);

//Tasks

Scheduler runner;
Task t1(2000, TASK_FOREVER, &t1Callback, NULL, false, NULL, NULL, &runner);

void t1Callback(void *userData)
{
    Serial.print("t1: ");
    Serial.println(millis());
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Scheduler TEST");

    runner.init();
    Serial.println("Initialized scheduler");

    runner.addTask(t1);
    Serial.println("added t1");

    t1.enable();
    Serial.println("Enabled t1");
}

void loop()
{
    runner.execute();
}