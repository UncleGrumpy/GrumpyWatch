#include "config.h"

lv_chart_series_t *ser1;
lv_obj_t *chart;

uint32_t lastMillis = 0;

void HallRead()
{

  int16_t x, y;
  while (!ttgo->getTouch(x, y)) {

    /*Create a chart*/
    chart = lv_chart_create(lv_scr_act(), NULL);
    lv_obj_set_size(chart, 200, 200);
    lv_obj_align(chart, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_chart_set_type(chart,  LV_CHART_TYPE_LINE);   /*Show lines and points too*/
    lv_chart_set_range(chart, 0, 20);

    /*Add two data series*/
    ser1 = lv_chart_add_series(chart, LV_COLOR_RED);

    /*Set the next points on 'dl1'*/
    lv_chart_set_next(chart, ser1, 10);

    if (millis() - lastMillis > 500) {
        lastMillis = millis();
        //Read the analog value of onboard hall sensor and display it in series
        uint16_t data = hallRead();
        lv_chart_set_next(chart, ser1, data);
    }
    lv_task_handler();
    delay(5);
  }
  ttgo->tft->fillScreen(TFT_BLACK);
}
