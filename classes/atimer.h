///
/// Developed by mrybs
///
#include <ctime>
#include <iostream>
#include <limits>

#pragma once


class ADuration {

public:
    void start(){
        seconds = time(NULL);
    }
    void end(){
        seconds = UINT64_MAX;
    }
    ulong getDuration() {
        if(seconds == NULL)
            seconds = time(NULL);
        return time(NULL) - seconds;
    }

private:
    ulong seconds;
};
