#pragma once
#include <Arduino.h>
#include <macro.h>

class RingBuffer
{
private:
    char command_queue[BUFSIZE][96]; // Ring buffer write (in) position
    uint8_t commands_in_queue = 0,   // Count of commands in the queue
        cmd_queue_index_r = 0,       // Ring buffer read (out) position
        cmd_queue_index_w = 0;
    static bool send_ok[4];

public:
    inline void _commit_command(bool say_ok);
    inline bool _enqueuecommand(const char *cmd, bool say_ok = false);
    bool _full();
};
