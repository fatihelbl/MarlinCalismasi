#pragma once

#include <RingBuffer/RingBuffer.h>

class GCodeQueue
{
private:
   

public:
    static void get_serial_commands();
 
    struct SerialState
    {
        long last_N;
        int count;            //!< Number of characters read in the current line of serial input
        char line_buffer[96]; //!< The current line accumulator
        uint8_t input_state;  //!< The input state
                              ////////////
    };

    static SerialState serial_state[1]; //!< Serial states for each serial port
};

class Buffer   // RingBuffer
{ public:
    char command_queue[BUFSIZE][96]; // Ring buffer write (in) position
    uint8_t commands_in_queue = 0,   // Count of commands in the queue
        cmd_queue_index_r = 0,       // Ring buffer read (out) position
        cmd_queue_index_w = 0;

    inline void _commit_command(bool say_ok);
    inline bool _enqueuecommand(const char *cmd, bool say_ok = false);
    bool _full();
};