#include "main.h"
#include "screen.hpp"

LV_IMG_DECLARE(Spades_No_BG_Small);
LV_FONT_DECLARE(comicsans);

lv_obj_t * mainTabView;
lv_obj_t * autonTabView;
lv_obj_t * blueTabView;
lv_obj_t * redTabView;
lv_obj_t * skillsTabView;

lv_obj_t * currentAuton;
lv_obj_t * debugLabel;

void renderBlueTab(lv_obj_t * blueTab) {
    // Disabled werid padding on tab
    lv_obj_set_style_pad_all(blueTab, 0, 0);

    blueTabView = lv_tabview_create(blueTab, LV_DIR_TOP, 40);
    // lv_obj_set_style_bg_color(blueTabView, lv_color_make(128, 0, 128), 0); // rgb(128, 0, 128)
    lv_obj_set_style_bg_color(blueTabView, lv_color_make(0, 0, 255), 0); // rgb(0, 0, 255)

    lv_obj_t * bluePos = lv_tabview_add_tab(blueTabView, "Blue Pos");
    lv_obj_t * blueNeg = lv_tabview_add_tab(blueTabView, "Blue Neg");

    lv_obj_t * blueLabel = lv_label_create(bluePos);
    lv_label_set_text(blueLabel, "Blue Pos Auton\nBla bla bla");

    blueLabel = lv_label_create(blueNeg);
    lv_label_set_text(blueLabel, "Blue Neg Auton\nBla bla bla");
}

void renderRedTab(lv_obj_t * redTab) {
    // Disabled werid padding on tab
    lv_obj_set_style_pad_all(redTab, 0, 0);

    redTabView = lv_tabview_create(redTab, LV_DIR_TOP, 40);
    // lv_obj_set_style_bg_color(redTabView, lv_color_make(128, 0, 128), 0); // rgb(128, 0, 128)
    lv_obj_set_style_bg_color(redTabView, lv_color_make(255, 0, 0), 0); // rgb(255, 0, 0)

    lv_obj_t * redPos = lv_tabview_add_tab(redTabView, "Red Pos");
    lv_obj_t * redNeg = lv_tabview_add_tab(redTabView, "Red Neg");

    lv_obj_t * redLabel = lv_label_create(redPos);
    lv_label_set_text(redLabel, "Red Pos Auton\nBla bla bla");

    redLabel = lv_label_create(redNeg);
    lv_label_set_text(redLabel, "Red Neg Auton\nBla bla bla");
}

void renderSkillsTab(lv_obj_t * skillsTab) {
    // Disabled werid padding on tab
    lv_obj_set_style_pad_all(skillsTab, 0, 0);

    skillsTabView = lv_tabview_create(skillsTab, LV_DIR_TOP, 40);
    // lv_obj_set_style_bg_color(redTabView, lv_color_make(128, 0, 128), 0); // rgb(128, 0, 128)
    lv_obj_set_style_bg_color(skillsTabView, lv_color_make(204,204,0), 0); // rgb(204,204,0)

    lv_obj_t * skillV2 = lv_tabview_add_tab(skillsTabView, "V2");

    lv_obj_t * skillsLabel = lv_label_create(skillV2);
    lv_label_set_text(skillsLabel, "Skills Auton");
}

void renderAuton(lv_obj_t * autonsTab) {
    lv_obj_set_style_pad_all(autonsTab, 0, 0);

    autonTabView = lv_tabview_create(autonsTab, LV_DIR_LEFT, 55);
    lv_obj_t * tab_content = lv_tabview_get_content(autonTabView);

    lv_obj_clear_flag(tab_content, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(autonTabView, lv_color_make(0, 0, 0), 0); // rgb(0, 0, 0)

    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(autonTabView);

    // lv_obj_set_style_bg_color(tab_btns, lv_color_make(128, 100, 128), 0); // rgb(128, 100, 128)
    // Background when not selected
    // lv_obj_set_style_text_color(tab_btns, lv_color_make(255, 255, 255), 0); // rgb(255, 255, 255)
    // Text color when not selected

    // lv_obj_set_style_bg_color(tab_btns, lv_color_make(255, 0, 0), LV_PART_ITEMS | LV_STATE_CHECKED); // rgb(255, 0, 0)
    // Background when selected
    // lv_obj_set_style_text_color(tab_btns, lv_color_make(255, 255, 0), LV_PART_ITEMS | LV_STATE_CHECKED); // rgb(255, 255, 0)
    // Text color when selected


    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t * blueTab = lv_tabview_add_tab(autonTabView, "Blue");
    lv_obj_t * redTab = lv_tabview_add_tab(autonTabView, "Red");
    lv_obj_t * skillsTab = lv_tabview_add_tab(autonTabView, "Skills");

    // Blue
    renderBlueTab(blueTab);
    // lv_obj_set_style_text_color(blueTab, lv_color_make(0, 0, 255), 0); // rgb(0, 0, 255)

    // Red
    renderRedTab(redTab);

    // Skills
    renderSkillsTab(skillsTab);
}

void renderDebug(lv_obj_t * debugTab) {
    currentAuton = lv_label_create(debugTab);
    lv_label_set_text(currentAuton, "Current None");

    debugLabel = lv_label_create(debugTab);
    lv_obj_align(debugLabel, LV_ALIGN_DEFAULT, 0, 10);

    char buf[1000];
    sprintf(
        buf, "Battery Level: %u\n Battery Draw: %u\nBattery Temp: %u",
        pros::battery::get_capacity(), pros::battery::get_current(), pros::battery::get_temperature()
    );
    lv_label_set_text(debugLabel, buf);
}

void picker::update() {
    char debugBuf[1000];
    sprintf(
        debugBuf, "Battery Level: %u\n Battery Draw: %u\nBattery Temp: %u",
        pros::battery::get_capacity(), pros::battery::get_current(), pros::battery::get_temperature()
    );
    lv_label_set_text(debugLabel, debugBuf);

    picker::getAuton();
}

void picker::render(void) {
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, &comicsans);

    mainTabView = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 30);

    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(mainTabView);

    lv_obj_t * autonsTab = lv_tabview_add_tab(mainTabView, "Autons");
    lv_obj_t * debugTab = lv_tabview_add_tab(mainTabView, "Debug");

    renderAuton(autonsTab);
    renderDebug(debugTab);

    // lv_obj_set_style_text_color(redTab, lv_color_make(255, 0, 0), 0); // rgb(255, 0, 0)

    // Non tab based stuff

    lv_obj_t * img = lv_img_create(lv_scr_act());  // Create an image object on the active screen

    /* Set the image source */
    lv_img_set_src(img, &Spades_No_BG_Small);  // Use the image data declared in SpadesBG.c
    // lv_img_set_src(img, "/usd/Spades_No_BG_Small.png");
    lv_obj_align(img, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
}

std::vector<uint16_t> picker::getAuton() {
    uint16_t active_tab = lv_tabview_get_tab_act(autonTabView);
    uint16_t active_tab_auton;
    // lv_tabview_set_act(tabview, 1, LV_ANIM_OFF);
    switch(active_tab) {
        case 0: {
            active_tab_auton = lv_tabview_get_tab_act(blueTabView);
            break;
        }
        case 1: {
            active_tab_auton = lv_tabview_get_tab_act(redTabView);
            break;
        }
        case 2: {
            active_tab_auton = lv_tabview_get_tab_act(skillsTabView);
            break;
        }
    }

    char buf[50];
    sprintf(buf, "Auton %u %u", active_tab, active_tab_auton);
    lv_label_set_text(currentAuton, buf);

    return { active_tab, active_tab_auton };
}

uint16_t maxAutons = 3;
uint16_t maxBlue = 2;
uint16_t maxRed = 2;

void picker::next() {
    lv_tabview_set_act(mainTabView, 0, LV_ANIM_OFF);

    uint16_t activeAutonTab = lv_tabview_get_tab_act(autonTabView);
    // activeAutonTab++;

    switch (activeAutonTab) {
        case 0: {
            uint16_t activeBlueTab = lv_tabview_get_tab_act(blueTabView);
            activeBlueTab++;
            if (activeBlueTab == maxBlue) {
                lv_tabview_set_act(blueTabView, 0, LV_ANIM_OFF);
                lv_tabview_set_act(autonTabView, 1, LV_ANIM_OFF);
                break;
            } else {
                lv_tabview_set_act(blueTabView, activeBlueTab, LV_ANIM_OFF);
                break;
            }
        }
        case 1: {
            uint16_t activeRedTab = lv_tabview_get_tab_act(redTabView);
            activeRedTab++;
            if (activeRedTab == maxRed) {
                lv_tabview_set_act(redTabView, 0, LV_ANIM_OFF);
                lv_tabview_set_act(autonTabView, 0, LV_ANIM_OFF);
                break;
            } else {
                lv_tabview_set_act(redTabView, activeRedTab, LV_ANIM_OFF);
                break;
            }
        }
    }

    // if (activeAutonTab == maxAutons) return lv_tabview_set_act(autonTabView, 0, LV_ANIM_OFF);
    // lv_tabview_set_act(autonTabView, activeAutonTab, LV_ANIM_OFF);
}