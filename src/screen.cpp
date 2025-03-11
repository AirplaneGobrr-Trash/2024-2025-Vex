#include "main.h"

#include "screen.hpp"
#include "globals.hpp"
#include "autons.hpp"
#include "utils.hpp"

LV_IMG_DECLARE(Spades_No_BG_Small);
LV_FONT_DECLARE(comicsans);

lv_obj_t * mainTabView;
lv_obj_t * autonTabView;

lv_obj_t * currentAuton;
lv_obj_t * debugLabel;

uint16_t maxBlue = 2;
uint16_t maxRed = 2;
uint16_t maxSkills = 1;

std::vector<std::pair<std::string, lv_obj_t *>> tabs = {};

void renderAuton(lv_obj_t * autonsTab) {
    lv_obj_set_style_pad_all(autonsTab, 0, 0);

    autonTabView = lv_tabview_create(autonsTab, LV_DIR_LEFT, 55);
    lv_obj_t * tab_content = lv_tabview_get_content(autonTabView);

    lv_obj_clear_flag(tab_content, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(autonTabView, lv_color_make(0, 0, 0), 0); // rgb(0, 0, 0)

    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(autonTabView);

    std::vector<AutonHelper> autons = utils::getAutons();
    
    for (const auto& autonInfo : autons) {
        std::string name = autonInfo.getName();
        lv_obj_t * tab = lv_tabview_add_tab(autonTabView, name.c_str());
        lv_obj_set_style_pad_all(tab, 0, 0);

        lv_obj_t * tabView = lv_tabview_create(tab, LV_DIR_TOP, 40);
        tabs.emplace_back(name, tabView);

        auto [r, g, b] = autonInfo.getRGB();
        lv_obj_set_style_bg_color(tabView, lv_color_make(r, g, b), 0);

        if (name == "Blue") maxBlue = autonInfo.getCount();
        if (name == "Red") maxRed = autonInfo.getCount();
        if (name == "Skills") maxSkills = autonInfo.getCount();


        // Add pos, neg, etc... autons to tabs
        for (const auto& auton : autonInfo.getAutons()) {
            lv_obj_t * autonTab = lv_tabview_add_tab(tabView, auton.first.c_str());
    
            lv_obj_t * autonLabel = lv_label_create(autonTab);
            lv_label_set_text(autonLabel, autonInfo.getAutonDesc(auton.first).c_str());
            pros::delay(1);
        }
        pros::delay(5);
    }

}

void old(){

    // lv_obj_set_style_bg_color(tab_btns, lv_color_make(128, 100, 128), 0); // rgb(128, 100, 128)
    // Background when not selected
    // lv_obj_set_style_text_color(tab_btns, lv_color_make(255, 255, 255), 0); // rgb(255, 255, 255)
    // Text color when not selected

    // lv_obj_set_style_bg_color(tab_btns, lv_color_make(255, 0, 0), LV_PART_ITEMS | LV_STATE_CHECKED); // rgb(255, 0, 0)
    // Background when selected
    // lv_obj_set_style_text_color(tab_btns, lv_color_make(255, 255, 0), LV_PART_ITEMS | LV_STATE_CHECKED); // rgb(255, 255, 0)
    // Text color when selected

    // Old code:

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    // lv_obj_t * blueTab = lv_tabview_add_tab(autonTabView, "Blue");
    // lv_obj_t * redTab = lv_tabview_add_tab(autonTabView, "Red");
    // lv_obj_t * skillsTab = lv_tabview_add_tab(autonTabView, "Skills");

    // Blue
    // renderBlueTab(blueTab);
    // lv_obj_set_style_text_color(blueTab, lv_color_make(0, 0, 255), 0); // rgb(0, 0, 255)

    // Red
    // renderRedTab(redTab);

    // Skills
    // renderSkillsTab(skillsTab);
}

void setDebugText() {
    char buf[5000];
    snprintf(buf, sizeof(buf), "Battery Level: %2.f\n Battery Draw: %u\nBattery Temp: %2.f\nTwobarRot:%u\nX:%2.f\nY:%2.f",
        pros::battery::get_capacity(), 
        pros::battery::get_current(), 
        pros::battery::get_temperature(),
        twoBarRot.get_angle(),
        chassis.odom_x_get(), 
        chassis.odom_y_get()
    );
    lv_label_set_text(debugLabel, buf);
}


void renderDebug(lv_obj_t * debugTab) {
    currentAuton = lv_label_create(debugTab);
    lv_label_set_text(currentAuton, "Current None");

    debugLabel = lv_label_create(debugTab);
    lv_obj_align(debugLabel, LV_ALIGN_DEFAULT, 0, 15);
    
    setDebugText();
}

void picker::update() {
    setDebugText();

    picker::getAuton();
}

void updater(){
    while (true){
        picker::update();
        pros::delay(50);
    }
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

    // Non tab based stuff

    lv_obj_t * img = lv_img_create(lv_scr_act());  // Create an image object on the active screen

    /* Set the image source */
    lv_img_set_src(img, &Spades_No_BG_Small);  // Use the image data declared in SpadesBG.c
    lv_obj_align(img, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    pros::Task::create(updater);
}

std::vector<uint16_t> picker::getAuton() {
    uint16_t active_tab = lv_tabview_get_tab_act(autonTabView);
    uint16_t active_tab_auton;
    // lv_tabview_set_act(tabview, 1, LV_ANIM_OFF);
    switch(active_tab) {
        case 0: {
            active_tab_auton = lv_tabview_get_tab_act(tabs[0].second);
            break;
        }
        case 1: {
            active_tab_auton = lv_tabview_get_tab_act(tabs[1].second);
            break;
        }
        case 2: {
            active_tab_auton = lv_tabview_get_tab_act(tabs[2].second);
            break;
        }
    }

    char buf[50];
    sprintf(buf, "Auton %u %u", active_tab, active_tab_auton);
    lv_label_set_text(currentAuton, buf);

    return { active_tab, active_tab_auton };
}

void picker::next() {
    lv_tabview_set_act(mainTabView, 0, LV_ANIM_OFF);

    uint16_t activeAutonTab = lv_tabview_get_tab_act(autonTabView);
    // activeAutonTab++;

    switch (activeAutonTab) {
        case 0: {
            lv_obj_t * blueTab = tabs[0].second;
            uint16_t activeBlueTab = lv_tabview_get_tab_act(blueTab);
            activeBlueTab++;
            if (activeBlueTab == maxBlue) {
                lv_tabview_set_act(blueTab, 0, LV_ANIM_OFF);
                lv_tabview_set_act(autonTabView, 1, LV_ANIM_OFF);
                break;
            } else {
                lv_tabview_set_act(blueTab, activeBlueTab, LV_ANIM_OFF);
                break;
            }
        }
        case 1: {
            lv_obj_t * redTab = tabs[1].second;
            uint16_t activeRedTab = lv_tabview_get_tab_act(redTab);
            activeRedTab++;
            if (activeRedTab == maxRed) {
                lv_tabview_set_act(redTab, 0, LV_ANIM_OFF);
                lv_tabview_set_act(autonTabView, 2, LV_ANIM_OFF);
                break;
            } else {
                lv_tabview_set_act(redTab, activeRedTab, LV_ANIM_OFF);
                break;
            }
        }
        case 2: {
            lv_obj_t * skillsTab = tabs[2].second;
            uint16_t activeSkillsTab = lv_tabview_get_tab_act(skillsTab);
            activeSkillsTab++;
            if (activeSkillsTab == maxSkills) {
                lv_tabview_set_act(skillsTab, 0, LV_ANIM_OFF);
                lv_tabview_set_act(autonTabView, 0, LV_ANIM_OFF);
                break;
            } else {
                lv_tabview_set_act(skillsTab, activeSkillsTab, LV_ANIM_OFF);
                break;
            }
        }
    }
}