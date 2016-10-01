#include <pebble.h>
#include "main.h"

static Window *s_main_window;
static TextLayer *s_hello_text;

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
    text_layer_set_text(s_hello_text, "00000:00:00:00");
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
    s_main_window = window_create();

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
