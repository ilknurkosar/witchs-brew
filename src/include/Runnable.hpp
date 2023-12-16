#pragma once

class Runnable{
  public:
    virtual void Process(double* delta) = 0;
};