#include <pebble.h>
#include "main.h"
static Window *s_main_window;

static void main_window_load(Window *window)
{
  
}

static void main_window_unload(Window *window)
{
  
}

static void init()
{
    s_main_window = window_create();
  
    window_set_window_handlers(s_mainWindow, (WindowHandlers)
                               {
                                   .load = main_window_load;
                                   .unload = main_window_unload;
                               });
  
    //Push to main window with animated true
    window_stack_push(s_main_window, true);
}

static void deinit()
{
    window_destory(s_main_window);
}

int main(void)
{
    init();
    app_event_loop();
    deinit();
}