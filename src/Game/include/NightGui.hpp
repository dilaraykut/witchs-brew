#pragma once
#include "GuiNode.hpp"
#include "raylib.h"
#include <vector>

class NightGui: public GuiNode{
    private:
    std::vector<::Rectangle> boxes;
    public:
    NightGui();
    virtual void display() override;
    private:
    std::vector<::Rectangle> transformBoxes();
};