#include <fstream>
#include <string>
#include "../holiday/holiday.h"

int calculateMults(char* buffer, int length, bool conditonal_statements)
{
    std::string val1str, val2str;
    int val1, val2, res = 0;
    bool fail = false, enabled = true;

    for (int i = 0; i < length - 8; i++)
    {
        if (conditonal_statements)
        {
            if (buffer[i] == 'd' &&
                buffer[i+1] == 'o' &&
                buffer[i+2] == '(' &&
                buffer[i+3] == ')')
            {
                enabled = true;
                i += 4;
            }
            else if (buffer[i] == 'd' &&
                buffer[i+1] == 'o' &&
                buffer[i+2] == 'n' &&
                buffer[i+3] == '\'' &&
                buffer[i+4] == 't' &&
                buffer[i+5] == '(' &&
                buffer[i+6] == ')')
            {
                enabled = false;
                i += 7;
            }
        }

        if (!enabled) continue;

        fail = false;
        if (buffer[i] == 'm' &&
            buffer[i+1] == 'u' &&
            buffer[i+2] == 'l' &&
            buffer[i+3] == '(')
        {
            i += 4;
            val1str = buffer[i];
            if ((int)buffer[i] < 48 || (int)buffer[i] > 57) continue;

            i++;
            while (buffer[i] != ',')
            {
                val1str += buffer[i];
                if ((int)buffer[i] < 48 || (int)buffer[i] > 57) { fail = true; break; }
                i++;
            }

            if (fail) continue;

            i++;
            val2str = buffer[i];
            if ((int)buffer[i] < 48 || (int)buffer[i] > 57) continue;

            i++;
            while (buffer[i] != ')')
            {
                val2str += buffer[i];
                if ((int)buffer[i] < 48 || (int)buffer[i] > 57) { fail = true; break; }
                i++;
            }

            if (fail) continue;
            res += (std::stoi(val1str) * std::stoi(val2str));
        }
    }
    return res;
}

int main ()
{
    std::ifstream in("input.txt");
    in.seekg (0, in.end);
    int length = in.tellg();
    in.seekg (0, in.beg);
    char buffer[length];
    in.read (buffer,length);
    in.close();

    std::ofstream out("output.txt");
    Holiday h;
    h.happyHolidays(3, out);
    out << "Part 1: " << calculateMults(buffer, length, false) << "\n";
    out << "Part 2: " << calculateMults(buffer, length, true) << "\n";

    return 0;
}
