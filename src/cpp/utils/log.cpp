#include "log.hpp"

#include <iostream>

std::string escape(const std::string &code, const std::string &esc) {
	return std::string("\033[") + code + esc;
}

std::string color(const unsigned char color, const bool bg, const bool bright) {
	return escape(std::to_string(30 + bg * 10 + bright * 60 + color));
}

inline void message(const std::string &title, const std::string &message, const int title_color, const bool new_line) {
	clear_line();
	std::cout << color(0b111, false, true) << "[" << color(title_color) << title << color(0b111, false, true) << "] " << escape("0") << message;
	if (new_line) std::cout << "\n";
	std::cout << std::flush;
}

void  ok (const std::string &msg) { message("  OK  ", msg, 0b010); }
void busy(const std::string &msg) { message(" BUSY ", msg, 0b110, false); }
void info(const std::string &msg) { message(" INFO ", msg, 0b100); }
void warn(const std::string &msg) { message(" WARN ", msg, 0b011); }
void done(const std::string &msg) { message(" DONE ", msg, 0b010); }
void fail(const std::string &msg, const std::string &details) {
	message("FAILED", msg, 0b001);
	// message("FAILED", details, 0b001);
	if (!details.empty()) std::cerr << "[FAILED] Error message: \n  " << details << "\n" << std::flush;
}

void clear_line(const int mode, const bool ret) {
	std::cout << (ret ? "\r" : "") << escape(std::to_string(mode), "K");
}

int progress_counter = 0;
int progress_subcounter = 0;

void progress() {
	clear_line();
	std::cout << color(0b111, false, true) << "[" << color(0b110);
	
	switch (progress_counter) {
		case 0: std::cout << "*    *"; break;
		case 1: std::cout << "**    "; break;
		case 2: std::cout << "***   "; break;
		case 3: std::cout << " ***  "; break;
		case 4: std::cout << "  *** "; break;
		case 5: std::cout << "   ***"; break;
		case 6: std::cout << "    **"; break;
		default: break;
	}
	
	std::cout << color(0b111, false, true) << "] " << escape("0");
	
	if (progress_subcounter++ >= 10) {
		progress_counter++;
		progress_subcounter = 0;
		
		if (progress_counter > 6) {
			progress_counter = 0;
		}
	}
}