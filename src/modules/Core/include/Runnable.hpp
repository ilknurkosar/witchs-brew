#pragma once

class Runnable{
  public:
  // has to return 1 (true) to continue execution. 0 (false) will either stop updates or the program.
    virtual int Process(double delta) = 0;
};