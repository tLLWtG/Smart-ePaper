#include "Key.h"

void key_Index_right(bool, int, void*)
{
    Serial.println("key_Index_right");
    switch (Index_sel)
    {
        case PageStatus_Reader:
            Index_sel = PageStatus_MP3_Sel;
            reDraw = true;
        break;
        case PageStatus_Weather:
            Index_sel = PageStatus_Hitokoto;
            reDraw = true;
        break;
    }
}

void key_Index_left(bool, int, void*)
{
    Serial.println("key_Index_left");
    switch (Index_sel)
    {
        case PageStatus_MP3_Sel:
            Index_sel = PageStatus_Reader;
            reDraw = true;
        break;
        case PageStatus_Hitokoto:
            Index_sel = PageStatus_Weather;
            reDraw = true;
        break;
    }
}

void key_Index_up(bool, int, void*)
{
    Serial.println("key_Index_up");
    switch (Index_sel)
    {
        case PageStatus_Weather:
            Index_sel = PageStatus_Reader;
            reDraw = true;
        break;
        case PageStatus_Hitokoto:
            Index_sel = PageStatus_MP3_Sel;
            reDraw = true;
        break;
    }
}

void key_Index_down(bool, int, void*)
{
    Serial.println("key_Index_down");
    switch (Index_sel)
    {
        case PageStatus_Reader:
            Index_sel = PageStatus_Weather;
            reDraw = true;
        break;
        case PageStatus_MP3_Sel:
            Index_sel = PageStatus_Hitokoto;
            reDraw = true;
        break;
    }
}

void key_Index_enter(bool, int, void*)
{
    Serial.println("key_Index_enter");
    partDrawCnt = 10;
    switch (Index_sel)
    {
        case PageStatus_Reader:
            pageStatus = PageStatus_Reader;
            reDraw = true;
        break;
        case PageStatus_MP3_Sel:
            pageStatus = PageStatus_MP3_Sel;
            reDraw = true;
        break;
        case PageStatus_Weather:
            pageStatus = PageStatus_Weather;
            reDraw = true;
        break;
        case PageStatus_Hitokoto:
            pageStatus = PageStatus_Hitokoto;
            reDraw = true;
        break;
    }
}

void key_Index_setup()
{
    Index_action.add(15, key_Index_right, AudioActions::ActiveLow);
    Index_action.add(16, key_Index_left, AudioActions::ActiveLow);
    Index_action.add(17, key_Index_up, AudioActions::ActiveLow);
    Index_action.add(18, key_Index_down, AudioActions::ActiveLow);
    Index_action.add(47, key_Index_enter, AudioActions::ActiveLow);
}
