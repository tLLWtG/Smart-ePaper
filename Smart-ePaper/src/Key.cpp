#include "Key.h"
#include "BaseDisplay.h"

void key_right(bool, int, void*)
{
    Serial.println("key_right");
    if (pageStatus == PageStatus_Index)
    {
        switch (Index_sel)
        {
            case PageStatus_MP3_Sel:
                Index_sel = PageStatus_Reader_Sel;
                reDraw = true;
                break;
            case PageStatus_Weather:
                Index_sel = PageStatus_Hitokoto;
                reDraw = true;
                break;
        }
    }
    else if (pageStatus == PageStatus_MP3_Play)
    {
        if (mlist_loc + 1 == music_list.size())
            return;
        reDraw = true;
        mlist_loc = mlist_loc + 1;
        if (mlist_loc > mlist_r)
        {
            ++mlist_l;
            ++mlist_r;
            reDraw = true;
        }
        player.setIndex(mlist_loc);
        player.setActive(true);
    }
    else if (pageStatus == PageStatus_MP3_Sel)
    {
        int t = 8;
        while (t--)
        {
            if (mlist_loc + 1 == music_list.size())
                return;
            reDraw = true;
            mlist_loc = mlist_loc + 1;
            if (mlist_loc > mlist_r)
            {
                ++mlist_l;
                ++mlist_r;
                reDraw = true;
            }
        }
    }
    else if (pageStatus == PageStatus_Reader_Sel)
    {
        int t = 8;
        while (t--)
        {
            if (tlist_loc + 1 == txt_list.size())
                return;
            reDraw = true;
            tlist_loc = tlist_loc + 1;
            if (tlist_loc > tlist_r)
            {
                ++tlist_l;
                ++tlist_r;
                reDraw = true;
            }
        }
    }
}

void key_left(bool, int, void*)
{
    Serial.println("key_left");
    if (pageStatus == PageStatus_Index)
    {
        switch (Index_sel)
        {
            case PageStatus_Reader_Sel:
                Index_sel = PageStatus_MP3_Sel;
                reDraw = true;
                break;
            case PageStatus_Hitokoto:
                Index_sel = PageStatus_Weather;
                reDraw = true;
                break;
        }
    }
    else if (pageStatus == PageStatus_MP3_Play)
    {
        if (mlist_loc == 0)
            return;
        reDraw = true;
        mlist_loc = mlist_loc - 1;
        if (mlist_loc < mlist_l)
        {
            --mlist_l;
            --mlist_r;
        }
        player.setIndex(mlist_loc);
        player.setActive(true);
    }
    else if (pageStatus == PageStatus_Weather || pageStatus == PageStatus_Hitokoto)
    {
        Serial.println("Clear WiFi info.");
        esp_wifi_restore();
    }
    else if (pageStatus == PageStatus_MP3_Sel)
    {
        int t = 8;
        while (t--)
        {
            if (mlist_loc == 0)
                return;
            reDraw = true;
            mlist_loc = mlist_loc - 1;
            if (mlist_loc < mlist_l)
            {
                --mlist_l;
                --mlist_r;
            }
        }
    }
    else if (pageStatus == PageStatus_Reader_Sel)
    {
        int t = 8;
        while (t--)
        {
            if (tlist_loc == 0)
                return;
            reDraw = true;
            tlist_loc = tlist_loc - 1;
            if (tlist_loc < tlist_l)
            {
                --tlist_l;
                --tlist_r;
            }
        }
    }
}

void key_up(bool, int, void*)
{
    Serial.println("key_up");
    if (pageStatus == PageStatus_Index)
    {
        switch (Index_sel)
        {
            case PageStatus_Weather:
                Index_sel = PageStatus_MP3_Sel;
                reDraw = true;
                break;
            case PageStatus_Hitokoto:
                Index_sel = PageStatus_Reader_Sel;
                reDraw = true;
                break;
        }
    }
    else if (pageStatus == PageStatus_MP3_Sel)
    {
        if (mlist_loc == 0)
            return;
        reDraw = true;
        mlist_loc = mlist_loc - 1;
        if (mlist_loc < mlist_l)
        {
            --mlist_l;
            --mlist_r;
        }
    }
    else if (pageStatus == PageStatus_MP3_Play)
    {
        if (fabs(myVolume - 1.0) <= 1e-6)
            return;
        reDraw = true;
        myVolume = myVolume + 0.05;
        player.setVolume(myVolume);
        Serial.printf("Current Volume: %f", myVolume);
        Serial.println();
    }
    else if (pageStatus == PageStatus_Reader_Sel)
    {
        if (tlist_loc == 0)
            return;
        reDraw = true;
        tlist_loc = tlist_loc - 1;
        if (tlist_loc < tlist_l)
        {
            --tlist_l;
            --tlist_r;
        }
    }
}

void key_down(bool, int, void*)
{
    Serial.println("key_down");
    if (pageStatus == PageStatus_Index)
    {
        switch (Index_sel)
        {
            case PageStatus_MP3_Sel:
                Index_sel = PageStatus_Weather;
                reDraw = true;
                break;
            case PageStatus_Reader_Sel:
                Index_sel = PageStatus_Hitokoto;
                reDraw = true;
                break;
        }
    }
    else if (pageStatus == PageStatus_MP3_Sel)
    {
        if (mlist_loc + 1 == music_list.size())
            return;
        reDraw = true;
        mlist_loc = mlist_loc + 1;
        if (mlist_loc > mlist_r)
        {
            ++mlist_l;
            ++mlist_r;
            reDraw = true;
        }
    }
    else if (pageStatus == PageStatus_MP3_Play)
    {
        if (fabs(myVolume - 0.0) <= 1e-6)
            return;
        reDraw = true;
        myVolume = myVolume - 0.05;
        player.setVolume(myVolume);
        Serial.printf("Current Volume: %f", myVolume);
        Serial.println();
    }
    else if (pageStatus == PageStatus_Reader_Sel)
    {
        if (tlist_loc + 1 == txt_list.size())
            return;
        reDraw = true;
        tlist_loc = tlist_loc + 1;
        if (tlist_loc > tlist_r)
        {
            ++tlist_l;
            ++tlist_r;
            reDraw = true;
        }
    }
}

void key_enter(bool, int, void*)
{
    Serial.println("key_enter");
    if (pageStatus == PageStatus_Index)
    {
        reDraw = true;
        switch (Index_sel)
        {
            case PageStatus_Reader_Sel:
                pageStatus = PageStatus_Reader_Sel;
                break;
            case PageStatus_MP3_Sel:
                pageStatus = PageStatus_MP3_Sel;
                break;
            case PageStatus_Weather:
                pageStatus = PageStatus_Weather;
                break;
            case PageStatus_Hitokoto:
                pageStatus = PageStatus_Hitokoto;
                break;
        }
    }
    else if (pageStatus == PageStatus_MP3_Sel)
    {
        reDraw = true;
        pageStatus = PageStatus_MP3_Play;
        // player.setPath((String(startFilePath) + "/" + music_list[mlist_loc]).c_str());
        player.setIndex(mlist_loc);
        player.setActive(true);
    }
    else if (pageStatus == PageStatus_MP3_Play)
    {
        player.setActive(!player.isActive());
        Serial.printf("Current Status: %s", (player.isActive() ? "Active" : "Inactive"));
        Serial.println();
    }
    else if (pageStatus == PageStatus_Reader_Sel)
    {
        reDraw = true;
        pageStatus = PageStatus_Reader;
        // TODO
    }
}

void key_back(bool, int, void*)
{
    Serial.println("key_back");
    if (pageStatus == PageStatus_Index)
    {
        // clear for poweroff
        display_clearScreen();
        display.hibernate();
        return;
    }
    reDraw = true;
    switch (pageStatus)
    {
        case PageStatus_Reader_Sel:
            pageStatus = PageStatus_Index;
            break;
        case PageStatus_MP3_Sel:
            pageStatus = PageStatus_Index;
            break;
        case PageStatus_Weather:
            WiFi.disconnect(true, false);
            pageStatus = PageStatus_Index;
            break;
        case PageStatus_Hitokoto:
            WiFi.disconnect(true, false);
            pageStatus = PageStatus_Index;
            break;
        case PageStatus_MP3_Play:
            player.setActive(false);
            pageStatus = PageStatus_MP3_Sel;
            break;
        case PageStatus_Reader:
            // TODO
            pageStatus = PageStatus_Reader_Sel;
            break;
    }
}

void key_setup()
{
    action.add(15, key_right, AudioActions::ActiveLow);
    action.add(16, key_left, AudioActions::ActiveLow);
    action.add(17, key_up, AudioActions::ActiveLow);
    action.add(18, key_down, AudioActions::ActiveLow);
    action.add(47, key_enter, AudioActions::ActiveLow);
    action.add(2, key_back, AudioActions::ActiveLow);
}
