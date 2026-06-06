#pragma once

#include <string>

std::string escape(std::string code, std::string esc = "m");
std::string color(unsigned char color, bool bg = false, bool bright = false);

void message(std::string title, std::string message, int title_color = 0b110);
void  ok (std::string message);
void busy(std::string message);
void info(std::string message);
void warn(std::string message);
void fail(std::string message, std::string details = "");
void done(std::string message);
void clear_line(int mode = 2, bool ret = true);

void progress();