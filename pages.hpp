#ifndef _PAGES_
#define _PAGES_

extern GtkWidget* pwm_page;
extern GtkWidget* robot_control_page;
extern GtkWidget* chat_page;

extern GtkWidget * action_items;

void pwm_setup();
void robot_setup();
void chat_setup();

void action_buttons_setup();


#endif
