#pragma once

class Runnable{
  public:
    virtual void process(double delta) = 0;
    Runnable() = default;
    virtual ~Runnable() = default;
};