#include <pebble.h>
#include "main.h"

static Window *s_main_window;

static unsigned int s_seconds_left;
static unsigned int s_secs_this_min;
static unsigned int s_mins_this_hour;
static unsigned int s_hours_this_day;
static unsigned int s_days;

static TextLayer *s_hello_text;
static TextLayer *s_num_days_text;
static TextLayer *s_hours_mins_secs_text;


//10 = buffer size
static char s_buffer[10];

static void set_times()
{
    unsigned int seconds = s_seconds_left;

    s_secs_this_min = 0;
    s_mins_this_hour = 0;
    s_hours_this_day = 0;
    s_days = 0;

    const unsigned int SECS_IN_MIN = 60;
    const unsigned int MINS_IN_HOUR = 60;
    const unsigned int HOURS_IN_DAY = 24;

    const unsigned int SECS_IN_DAY = SECS_IN_MIN * MINS_IN_HOUR * HOURS_IN_DAY;
    const unsigned int SECS_IN_HOUR = MINS_IN_HOUR * SECS_IN_MIN;


    while(seconds != 0)
    {
        if(seconds >= SECS_IN_DAY)
        {
            seconds -= SECS_IN_DAY;
            s_days++;
        }
        else if(seconds >= SECS_IN_HOUR)
        {
            seconds -= SECS_IN_HOUR;
            s_hours_this_day++;
        }
        else if(seconds >= SECS_IN_MIN)
        {
            seconds -= SECS_IN_MIN;
            s_mins_this_hour++;
        }
        else
        {
            s_secs_this_min = seconds;
            seconds -= s_secs_this_min;
        }
    }
}

static void set_buffer(char * buffer, unsigned int number, int length)
{
    unsigned int last_digit_gone = number;
    unsigned int remaining = number;

    for(int i = length; i > 0; i--)
    {
        last_digit_gone = (last_digit_gone / 10) * 10;
        //Should be using last value of last_digit_gone, not s_seconds_left????
        unsigned int last_digit = remaining - last_digit_gone;
        remaining = (remaining /10);
        last_digit_gone = last_digit_gone / 10;

        buffer[i-1] = (char)last_digit + '0';
    }
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{
    s_seconds_left -= units_changed;
    //todo: delet this
    set_times();

    set_buffer(s_buffer, s_seconds_left, 10);

    char days_buffer[5];
    set_buffer(days_buffer, s_days, 5);

    char hour_buffer[2];
    set_buffer(hour_buffer, s_hours_this_day, 2);
    char min_buffer[2];
    set_buffer(min_buffer, s_mins_this_hour, 2);
    char sec_buffer[2];
    set_buffer(sec_buffer, s_secs_this_min, 2);

    static char time_buffer[9];
    time_buffer[0] = hour_buffer[0];
    time_buffer[1] = hour_buffer[1];
    time_buffer[2] = ':';
    time_buffer[3] = min_buffer[0];
    time_buffer[4] = min_buffer[1];
    time_buffer[5] = ':';
    time_buffer[6] = sec_buffer[0];
    time_buffer[7] = sec_buffer[1];
    time_buffer[8] = ' ';

    text_layer_set_text(s_hours_mins_secs_text, time_buffer);

    text_layer_set_text(s_hello_text, s_buffer);


    static char days_text[10];
    for(int i = 0; i < 5; i++)
    {
        days_text[i] = days_buffer[i];
    }
    days_text[5] = ' ';
    days_text[6] = 'D';
    days_text[7] = 'a';
    days_text[8] = 'y';
    days_text[9] = 's';
    text_layer_set_text(s_num_days_text, days_text);
}

static void main_window_load(Window *window)
{
    //window information
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    //text information
    int text_x = 0;
    int text_y = PBL_IF_ROUND_ELSE(58, 300);
    int text_width = bounds.size.w;
    int text_height = 50;

    //create text
    s_hello_text = text_layer_create(
        GRect(text_x, text_y, text_width, text_height)
    );

    //format text
    text_layer_set_background_color(s_hello_text, GColorClear);
    text_layer_set_text_color(s_hello_text, GColorBlack);
    text_layer_set_text(s_hello_text, "preparing");
    text_layer_set_font(s_hello_text, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_text_alignment(s_hello_text, GTextAlignmentCenter);

    //add the text
    layer_add_child(window_layer, text_layer_get_layer(s_hello_text));

    //days text info /////////////////////////////////////////////////
    int days_x = 0;
    int days_y = PBL_IF_ROUND_ELSE(58, 52);
    int days_width = bounds.size.w;
    int days_height = 50;

    //create text info ///////////////////////////////////////////////
    s_num_days_text = text_layer_create(
        GRect(days_x, days_y, days_width, days_height)
    );

    //format days text ////////////////////////////////////////////
    text_layer_set_background_color(s_num_days_text, GColorClear);
    text_layer_set_text_color(s_num_days_text, GColorBlack);
    text_layer_set_text(s_num_days_text, "preparing");
    text_layer_set_font(s_num_days_text,
        fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_text_alignment(s_num_days_text, GTextAlignmentCenter);

    //add days text ////////////////////////////////////////////
    layer_add_child(window_layer, text_layer_get_layer(s_num_days_text));

    //text information
    int time_x = 0;
    int time_y = PBL_IF_ROUND_ELSE(58, 102);
    int time_width = bounds.size.w;
    int time_height = 50;

    //create text
    s_hours_mins_secs_text = text_layer_create(
        GRect(time_x, time_y, time_width, time_height)
    );

    //format text
    text_layer_set_background_color(s_hours_mins_secs_text, GColorClear);
    text_layer_set_text_color(s_hours_mins_secs_text, GColorBlack);
    text_layer_set_text(s_hours_mins_secs_text, "datetime");
    text_layer_set_font(s_hours_mins_secs_text,
        fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_text_alignment(s_hours_mins_secs_text, GTextAlignmentCenter);

    //add the text
    layer_add_child(window_layer, text_layer_get_layer(s_hours_mins_secs_text));
}

static void main_window_unload(Window *window)
{

}

static void init()
{
    s_seconds_left = 100000;
    set_times();

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
