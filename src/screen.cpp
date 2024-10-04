#include "main.h"

LV_IMG_DECLARE(Spadesremovebg);

void lv_example_tabview_2(void)
{
    /*Create a Tab view object*/
    lv_obj_t * tabview;
    tabview = lv_tabview_create(lv_scr_act(), LV_DIR_LEFT, 80);

    lv_obj_set_style_bg_color(tabview, lv_color_make(128, 0, 128), 0);

    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);

    lv_obj_set_style_bg_color(tab_btns, lv_color_make(128, 100, 128), 0);  // Change tab button background to red
    lv_obj_set_style_text_color(tab_btns, lv_color_make(255, 0, 0), 0);
    // lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_GREY, 3), 0);
    // lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
    // lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "Tab 1");
    lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "Tab 2");
    lv_obj_t * tab3 = lv_tabview_add_tab(tabview, "Tab 3");
    lv_obj_t * tab4 = lv_tabview_add_tab(tabview, "Tab 4");
    lv_obj_t * tab5 = lv_tabview_add_tab(tabview, "Tab 5");

    // lv_obj_set_style_bg_color(tab1, lv_color_make(128, 0, 128), 0);

    // lv_obj_set_style_bg_color(tab2, lv_palette_lighten(LV_PALETTE_AMBER, 3), 0);
    lv_obj_set_style_bg_opa(tab2, LV_OPA_COVER, 0);

    lv_obj_t * currentTab = lv_label_create(lv_scr_act());
    lv_label_set_text(currentTab, "First tab");
    lv_obj_align(currentTab, LV_ALIGN_CENTER, 0, 0);

    /*Add content to the tabs*/
    lv_obj_t * label = lv_label_create(tab1);
    lv_label_set_text(label, "First tab");

    label = lv_label_create(tab1);
    lv_label_set_text(label, "help me");
    lv_obj_align(label, LV_ALIGN_DEFAULT, 0, 15);

    label = lv_label_create(tab2);
    lv_label_set_text(label, "Second tab");

    label = lv_label_create(tab3);
    lv_label_set_text(label, "Third tab");

    label = lv_label_create(tab4);
    lv_label_set_text(label, "Forth tab");

    label = lv_label_create(tab5);
    lv_label_set_text(label, "Fifth tab");

    lv_obj_clear_flag(lv_tabview_get_content(tabview), LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t * img = lv_img_create(lv_scr_act());  // Create an image object on the active screen
    
    /* Set the image source */
    lv_img_set_src(img, &Spadesremovebg);  // Use the image data declared in SpadesBG.c
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

    while (true) {
        uint16_t active_tab = lv_tabview_get_tab_act(tabview) +1;
        char buf[50];
        sprintf(buf, "First tab %u", active_tab);
        lv_label_set_text(currentTab, buf);
        pros::delay(10);
    }
}

void test(void) {
    lv_example_tabview_2();
}