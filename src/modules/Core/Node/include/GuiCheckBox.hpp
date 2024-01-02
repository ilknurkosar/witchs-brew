#pragma once

#include "GuiNode.hpp"
#include "raylib.h"
#include <string>

class GuiCheckBox : public GuiNode{
    protected:
    ::Rectangle shape;
    std::string message;
    void (*handler)(bool) = nullptr;
    bool pressed = true;
    public:
        explicit inline GuiCheckBox() : shape(::Rectangle{0.0,0.0,60.0,20.0}), message("Button") {}
        explicit inline GuiCheckBox(bool pressed): GuiCheckBox() {this->pressed = pressed;}
        explicit inline GuiCheckBox(bool pressed, ::Rectangle shape, std::string message): GuiCheckBox(pressed)
        {
            this->shape = shape;
            this->message = message;
        }
        explicit inline GuiCheckBox(bool pressed, ::Rectangle shape, std::string message, void (*handler)(bool)): GuiCheckBox(pressed,shape,message)
        {
            this->handler = handler;
        }
        inline void setShape(::Rectangle shape){this->shape = shape;}
        inline ::Rectangle& getShape(){return shape;}
        inline void setMessage(std::string message){this->message = message;}
        inline void setHandler(void (*handler)(bool)){this->handler = handler;}
        inline void setPressed(bool pressed){this->pressed = pressed;}
        inline bool isPressed(){return pressed;}
        inline std::string& getMessage(){return message;}
        virtual void display(Matrix transform) override;
        virtual ~GuiCheckBox() = default;
};