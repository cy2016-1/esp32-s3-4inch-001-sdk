// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"

// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_Image2;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_Label5;
void ui_event_ImgButton1(lv_event_t * e);
extern lv_obj_t * ui_ImgButton1;
void ui_event_ImgButton2(lv_event_t * e);
extern lv_obj_t * ui_ImgButton2;
extern lv_obj_t * ui____initial_actions0;


LV_IMG_DECLARE(ui_img_1_png);    // assets/1.png
LV_IMG_DECLARE(ui_img_7_png);    // assets/7.png
LV_IMG_DECLARE(ui_img_112_png);    // assets/112.png
LV_IMG_DECLARE(ui_img_772611441);    // assets/6 开 左.png
LV_IMG_DECLARE(ui_img_121_png);    // assets/121.png
LV_IMG_DECLARE(ui_img_247585368);    // assets/8 开 右.png
LV_IMG_DECLARE(ui_img_111_png);    // assets/111.png
LV_IMG_DECLARE(ui_img_122_png);    // assets/122.png
LV_IMG_DECLARE(ui_img_2_png);    // assets/2.png



LV_FONT_DECLARE(ui_font_Font1);
LV_FONT_DECLARE(ui_font_Font2);



void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
