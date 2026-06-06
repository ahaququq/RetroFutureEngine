#include "log.hpp"

#include <iostream>

std::string escape(std::string code, std::string esc) {
	return std::string("\033[") + code + esc;
}

std::string color(unsigned char color, bool bg, bool bright) {
	return escape(std::to_string(30 + bg * 10 + bright * 60 + color));
}

void clear_line(int mode, bool ret) {
	std::cout << (ret ? "\r" : "") << escape(std::to_string(mode), "K");
}

void message(std::string title, std::string message, int title_color) {
    clear_line();
    std::cout << color(0b111, false, true) << "[" << color(title_color) << title << color(0b111) << "] " << escape("0") << message << "\n" << std::flush;
}

void  ok (std::string msg) { message("  OK  ", msg, 0b010); }
void busy(std::string msg) { message(" BUSY ", msg, 0b110); }
void done(std::string msg) { message(" DONE ", msg, 0b010); }
void info(std::string msg) { message(" INFO ", msg, 0b100); }
void warn(std::string msg) { message(" WARN ", msg, 0b011); }

void fail(std::string msg, std::string details) {
    message("FAILED", msg, 0b001);
	if (details != "") std::cerr << "[FAILED] \n  Err: " << message << std::flush;
}

int progress_counter = 0;
int progress_subcounter = 0;

void progress() {
	std::cout << "\r" << color(0b111, false, true) << "[" << color(0b110);
	
	switch (progress_counter) {
		case 0: std::cout << "*    *"; break;
		case 1: std::cout << "**    "; break;
		case 2: std::cout << "***   "; break;
		case 3: std::cout << " ***  "; break;
		case 4: std::cout << "  *** "; break;
		case 5: std::cout << "   ***"; break;
		case 6: std::cout << "    **"; break;
	}
	
	std::cout << color(0b111) << "] " << escape("0");
	
	if (progress_subcounter++ >= 10) {
		progress_counter++;
		progress_subcounter = 0;
		
		if (progress_counter > 6) {
			progress_counter = 0;
		}
	}
}