#include <RingBuffer/RingBuffer.h>

/*inline void RingBuffer ::_commit_command(bool say_ok)
{
    static bool send_ok[4];
    send_ok[cmd_queue_index_w] = say_ok;
    if (++cmd_queue_index_w >= BUFSIZE)
        cmd_queue_index_w = 0;
    commands_in_queue++;
}
inline bool RingBuffer ::_enqueuecommand(const char *cmd, bool say_ok)
{
    if (*cmd == ';' || commands_in_queue >= BUFSIZE)
        return false;
    strcpy(command_queue[cmd_queue_index_w], cmd);
    _commit_command(say_ok);
    return true;
}

// bool RingBuffer ::_full()
// {
//     if (commands_in_queue >= BUFSIZE)
//     {
//         Serial.println("RingBuffer full");
//         cmd_queue_index_w=0;
//         return true;

//     }
// }

*/