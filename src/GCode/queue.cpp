#include <GCode/queue.h>
//#include <RingBuffer/RingBuffer.h>
#include <macro.h>

GCodeQueue::SerialState GCodeQueue::serial_state[1] = {0}; //!< Serial states for each serial port
Buffer buffer;


inline void Buffer ::_commit_command(bool say_ok)
{
    static bool send_ok[4];
    send_ok[cmd_queue_index_w] = say_ok;
    if (++cmd_queue_index_w >= BUFSIZE)
        cmd_queue_index_w = 0;
    commands_in_queue++;
}

inline bool Buffer ::_enqueuecommand(const char *cmd, bool say_ok)
{
    if (*cmd == ';' || commands_in_queue >= BUFSIZE)
        return false;
    strcpy(command_queue[cmd_queue_index_w], cmd);
    _commit_command(say_ok);
    return true;
}

inline void process_stream_char(const char c, uint8_t &sis, char (&buff)[96], int &ind)
{

    if (sis == PS_EOL)
    {
        return;
    }
    else if (sis >= PS_ESC)
    {
        sis -= PS_ESC;
    }
    else if (c == '\\')
    {
        sis += PS_ESC;
        if (sis == PS_ESC)
        {
            return;
        }
    }
    else if (c == ';')
    {
        sis = PS_EOL;
        return;
    }
    if (c == 0x08)
    {
        if (ind)
        {
            buff[--ind] = '\0';
        }
    }
    else
    {
        buff[ind++] = c;
        if (ind >= 95)
        {

            sis = PS_EOL;
        }
    }
}
inline bool process_line_done(uint8_t &sis, char (&buff)[96], int &ind)
{
    sis = PS_NORMAL;                  // "Normal" Serial Input State
    buff[ind] = '\0';                 // Of course, I'm a Terminator.
    const bool is_empty = (ind == 0); // An empty line?
    if (is_empty)
    {
        // thermalManager.manage_heater();   // Keep sensors satisfied
    }
    else
        ind = 0;     // Start a new line
    return is_empty; // Inform the caller
}

void GCodeQueue ::get_serial_commands()
{

    for (bool hadData = true; hadData;)
    {

        hadData = false;
        for (uint8_t VAR = 0; VAR < 1; VAR++)
        {
            /* if (ring_buffer._full())
             {
                 return;
             }
              */

            if (!Serial1.available())
            {
                continue;
            }

            hadData = true;
            const int c = Serial1.read();
            if (c < 0)
            {
                Serial.println("Serial read error");
            }

            const char serial_char = (char)c;
            SerialState &serial = serial_state[VAR];
            if (ISEOL(serial_char))
            {
                if (process_line_done(serial.input_state, serial.line_buffer, serial.count))
                    continue;

                char *command = serial.line_buffer;
                while (*command == ' ')
                    command++;

                char *npos = strchr(command, 'A');
                if (*npos == 'A')
                {
                    Serial.print("A**");
                }
                char *M = strchr(command, 'B');
                if (*M == 'B')
                {
                    //Serial.print("B**");
                }
                char *L = strchr(command, 'C');
                if (*L == 'C')
                {
                    //Serial.print("C**");
                }
                
            }
            else
            {
                process_stream_char(serial_char, serial.input_state, serial.line_buffer, serial.count);
            }
        } 
    }
}
