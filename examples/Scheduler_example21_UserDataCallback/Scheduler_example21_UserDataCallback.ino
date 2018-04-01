/**
 *  TaskScheduler Test w/ user_data void * in the timer callback
 */

#include <TaskScheduler.h>

namespace  // anonymous namespace
{
    void foo_task_cb(void *userData);

    class Foo
    {
    public:
        Foo(uint32_t id,
            uint32_t interval,
            uint32_t iterations,
            Scheduler &scheduler)
            : _id(id),
              _fooTask(interval,
                       iterations,
                       &foo_task_cb,
                       &scheduler,
                       true,
                       NULL,
                       NULL,
                       this)
        {
        }

    public:
        void enable()
        {
            _fooTask.enable();
        }

        void incrementCounter()
        {
            ++_counter;

            Serial.print("Counter [");
            Serial.print(_id);
            Serial.print("]: ");
            Serial.println(_counter);
        }

    private:
        uint32_t _id;
        Task _fooTask;
        uint32_t _counter{};
    };

    void foo_task_cb(void *userData)
    {
        reinterpret_cast<Foo *>(userData)->incrementCounter();
    }

    Scheduler g_scheduler;
}

void setup()
{
    Serial.begin(9600);
    Serial.println("Scheduler TEST");

    g_scheduler.init();
    Serial.println("Initialized scheduler");

    new Foo(1, 2000, 5, g_scheduler);
    new Foo(2, 1500, 4, g_scheduler);
}

void loop()
{
    g_scheduler.execute();
}