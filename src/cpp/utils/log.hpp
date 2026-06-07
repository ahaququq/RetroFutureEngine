#pragma once

#include <string>

std::string escape(const std::string &code, const std::string &esc = "m");
std::string color(unsigned char color, bool bg = false, bool bright = false);

inline void message(const std::string &title, const std::string &message, int title_color = 0b110, bool new_line = true);
void  ok (const std::string &msg);
void busy(const std::string &msg);
void info(const std::string &msg);
void warn(const std::string &msg);
void done(const std::string &msg);
void fail(const std::string &msg, const std::string &details = "");
void clear_line(int mode = 2, bool ret = true);

void progress();