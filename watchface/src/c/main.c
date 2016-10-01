#include <pebble.h>
#include "main.h"

static Window *s_main_window;
static TextLayer *s_hello_text;

static unsigned int s_seconds_left;
//10 = buffer size
static char s_buffer[10];

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    s_seconds_left -= units_changed;

    unsigned int last_digit_gone = s_seconds_left;
    unsigned int remaining = s_seconds_left;

    //10 = buffer size
    for(int i = 10; i > 0; i--)
    {
        last_digit_gone = (last_digit_gone / 10) * 10;
        //Should be using last value of last_digit_gone, not s_seconds_left????
        unsigned int last_digit = remaining - last_digit_gone;
        remaining = (remaining /10);
        last_digit_gone = last_digit_gone / 10;

        s_buffer[i-1] = (char)last_digit + '0';
    }

    text_layer_set_text(s_hello_text, s_buffer);
}

static void main_window_load(Window *window)
{
    //window information
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    //text information
    int text_x = 0;
    int text_y = PBL_IF_ROUND_ELSE(58, 52);
    int text_width = bounds.size.w;
    int text_height = 50;

    //create text
    s_hello_text = text_layer_create(
        GRect(text_x, text_y, text_width, text_height)
    );

    //format text
    text_layer_set_background_color(s_hello_text, GColorClear);
    text_layer_set_text_color(s_hello_text, GColorBlack);
    //text_layer_set_text(s_hello_text, "hello");
    text_layer_set_font(s_hello_text, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_text_alignment(s_hello_text, GTextAlignmentCenter);

    //add the text
    layer_add_child(window_layer, text_layer_get_layer(s_hello_text));
}

static void main_window_unload(Window *window)
{

}

static void init()
{
    s_seconds_left = 100000;

    s_main_window = window_create();

    tick_timer_service_subscribe(SECOND_UNIT, tick_handler);

    window_set_window_handlers(s_main_window, (WindowHandlers)
                               {
                                   .load = main_window_load,
                                   .unload = main_window_unload
                               });

    //Push to main window with animated true
    window_stack_push(s_main_window, true);
}

static void deinit()
{
    //todo: fix window_destory
    //window_destory(s_main_window);
    text_layer_destroy(s_hello_text);
}

int main(void)
{
    init();
    app_event_loop();
    deinit();
}
