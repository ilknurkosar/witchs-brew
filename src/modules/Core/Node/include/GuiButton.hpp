#pragma once

#include "GuiNode.hpp"
#include "raylib.h"
#include <string>

class GuiButton : public GuiNode{
    protected:
    ::Rectangle shape;
    std::string message;
    void (*handler)() = nullptr;
    public:
        explicit inline GuiButton() : shape(::Rectangle{0.0,0.0,60.0,20.0}), message("Button") {}
        inline void setShape(::Rectangle shape){this->shape = shape;}
        inline ::Rectangle& getShape(){return shape;}
        inline void setMessage(std::string message){this->message = message;}
        inline void setHandler(void (*handler)()){this->handler = handler;}
        inline std::string& getMessage(){return message;}
        virtual void display(Matrix transform) override;
        virtual ~GuiButton() = default;
};