#include <lvgl.h>
#include <TFT_eSPI.h>
/*If you want to use the LVGL examples,
  make sure to install the lv_examples Arduino library
  and uncomment the following line.
#include <lv_examples.h>
*/

#include <lv_demo.h>

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */

/*屏幕的宽高在这里修改*/
static const uint32_t screenWidth  = 240;
static const uint32_t screenHeight = 320;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

//开启日志后调用的函数，启用该功能需要修改lvgl_conf.h的对应功能
#if LV_USE_LOG != 0
/* Serial debugging */s
void my_print( lv_log_level_t level, const char * file, uint32_t line, const char * fn_name, const char * dsc )
{
   Serial.printf( "%s(%s)@%d->%s\r\n", file, fn_name, line, dsc );
   Serial.flush();
}
#endif

/* 刷新屏幕 */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
   uint32_t w = ( area->x2 - area->x1 + 1 );
   uint32_t h = ( area->y2 - area->y1 + 1 );

   tft.startWrite();
   tft.setAddrWindow( area->x1, area->y1, w, h );
   tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
   tft.endWrite();

   lv_disp_flush_ready( disp );
}


void setup()
{
   Serial.begin( 115200 ); /* prepare for possible serial debug */
   Serial.println( "Hello Arduino! (V8.0.X)" );
   Serial.println( "I am LVGL_Arduino" );

   lv_init();

#if LV_USE_LOG != 0
   lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

   tft.begin();          /* TFT init */
   tft.setRotation( 3 ); /* 旋转屏幕，n * 90度 ，3表示270度*/

  // 建立一个屏幕宽*10大小的缓冲区
   lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );

   /*初识化屏幕*/
   static lv_disp_drv_t disp_drv;
   lv_disp_drv_init( &disp_drv );
   /*Change the following line to your display resolution*/
   disp_drv.hor_res = screenWidth;
   disp_drv.ver_res = screenHeight;
   disp_drv.flush_cb = my_disp_flush;
   disp_drv.draw_buf = &draw_buf;
   lv_disp_drv_register( &disp_drv );

   /*初识化输入设备*/
   static lv_indev_drv_t indev_drv;
   lv_indev_drv_init( &indev_drv );
   indev_drv.type = LV_INDEV_TYPE_POINTER;
   lv_indev_drv_register( &indev_drv );

#if 0  //取消注释会在屏幕中显示文字
   /* Create simple label */
   lv_obj_t *label = lv_label_create( lv_scr_act() );
   lv_label_set_text( label, "Hello Arduino! (V8.0.X)" );
   lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
#else

   // 取消注释会启用对应的案例
   lv_demo_widgets();            // OK
   // lv_demo_benchmark();          // OK
   // lv_demo_keypad_encoder();     // works, but I haven't an encoder
   // lv_demo_music();              // NOK
   // lv_demo_printer();
   // lv_demo_stress();             // seems to be OK
#endif
   Serial.println( "Setup done" );
}

void loop()
{
   lv_timer_handler(); /* 在循环中让lvgl处理一些相应的事件 */
   delay( 5 );
}
