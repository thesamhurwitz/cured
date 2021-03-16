#ifndef CURED_H
#define CURED_H


#include <stdint.h>
#include <iostream>
#include <string>
#include <sstream>

#if defined(__linux__) || defined(__unix__) 
	#include <sys/ioctl.h>
	#include <unistd.h>
	#include <termios.h>
#endif

// Types

typedef char cured_char;
typedef std::string cured_string;

struct Size {
  uint8_t width;
  uint8_t height;
};

struct Point {
  uint8_t x;
  uint8_t y;
};

enum class Color : uint8_t {
  // --- Transparent -----
  Default = 39,

  // --- Grayscale -----
  Black = 30,
  GrayDark = 90,
  GrayLight = 37,
  White = 97,

  // --- Hue -----
  Blue = 34,
  BlueLight = 94,

  Cyan = 36,
  CyanLight = 96,

  Green = 32,
  GreenLight = 92,

  Magenta = 35,
  MagentaLight = 95,

  Red = 31,
  RedLight = 91,

  Yellow = 33,
  YellowLight = 93,
};

struct Char {
  cured_char Character = ' ';
  bool Blink = false;
  bool Bold = false;
  bool Dim = false;
  bool Inverted = false;
  bool Underlined = false;

  Color BackgroundColor = Color::Default;
  Color ForegroundColor = Color::Default;
};

// Terminal

namespace Terminal {
  Size getSize();

  void init();
  void prepare();
  void restore();

  static struct termios defaultTerm;


  // Cursor
  const cured_char* CURSOR_UP       = "\x1B[1A";
  const cured_char* CURSOR_DOWN     = "\x1B[1B";
  const cured_char* CURSOR_FORWARD  = "\x1B[1C";
  const cured_char* CURSOR_BACK     = "\x1B[1D";

  const cured_char* CARRIAGE_RETURN = "\r";
  const cured_char* NEW_LINE        = "\n";

  const cured_char* ERASE_SCREEN    = "\x1B[2J"; // if 3, will erase scroll buffer
  const cured_char* ERASE_LINE      = "\x1B[2K";

  const cured_char* CURSOR_SHOW     = "\x1B[25h";
  const cured_char* CURSOR_HIDE     = "\x1B[25l";

  const cured_char* AUTO_WRAP_SET   = "\x1B[?7h";
  const cured_char* AUTO_WRAP_RESET = "\x1B[?7l";
  
  const cured_char* ALTERNATIVE_SCREEN = "\x1B[?1049h";
  const cured_char* NORMAL_SCREEN   = "\x1B[?1049l";

  // Select Graphics Rendition
  const cured_char* SGR_NORMAL = "\x1B[m";

  const cured_char* SGR_BOLD_SET = "\x1B[1m";
  const cured_char* SGR_BOLD_RESET = "\x1B[22m";

  const cured_char* SGR_DIM_SET = "\x1B[2m";
  const cured_char* SGR_DIM_RESET = "\x1B[22m";

  const cured_char* SGR_UNDERLINED_SET = "\x1B[4m";
  const cured_char* SGR_UNDERLINED_RESET = "\x1B[24m";

  const cured_char* SGR_BLINK_SET = "\x1B[5m";
  const cured_char* SGR_BLINK_RESET = "\x1B[25m";

  const cured_char* SGR_INVERTED_SET = "\x1B[7m";
  const cured_char* SGR_INVERTED_RESET = "\x1B[27m";

  // TODO: add other styles like strike


  inline cured_string CURSOR_POSITION(int x, int y) {
    // TODO: fix this
    cured_string str = "\x1B[" + std::to_string(y + 1) + ";" + std::to_string(x + 1) + "H";
    return str;
  }

  // TODO color conversions to ascii sequences
  // TODO set window title
}


// Screen

class Screen {
public:
  void Init();
  void Draw();

  inline cured_char& at(int x, int y) {
    return buffer[y * width + x].Character;
  }

  inline Char& charAt(int x, int y) {
    return buffer[y * width + x];
  }

private:
  Char* buffer;

  int width, height;
};


#ifdef CURED_IMPLEMENTATION

// Term Info

Size Terminal::getSize() {
#if defined(__linux__) || defined(__unix__) 
  winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  return { w.ws_col, w.ws_row };
#endif
}

// Fetches terminfo
void Terminal::init() {
  
}

void Terminal::prepare() {
  // std::atexit(restore);
  // TODO save old terminal settings and restore on exit

  // Disable canonical mode, disable echoing, disable line buffering
#if defined(__linux__) || defined(__unix__)
  struct termios term;

  tcgetattr(STDIN_FILENO, &term);
  tcgetattr(STDIN_FILENO, &Terminal::defaultTerm);

  term.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
  term.c_oflag &= ~OPOST;
  term.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  term.c_cflag &= ~(CSIZE | PARENB);
  term.c_cflag |= CS8;

  term.c_cc[VMIN] = 0;
  term.c_cc[VTIME] = 0;

  tcsetattr(STDIN_FILENO, TCSANOW, &term);
#endif

  // Hide cursor, disable line wrap
  std::cout << Terminal::CURSOR_HIDE;
  std::cout << Terminal::AUTO_WRAP_RESET;
  std::cout << std::flush;

  // TODO install signal handlers
}

void Terminal::restore() {
  tcsetattr(STDIN_FILENO, TCSANOW, &Terminal::defaultTerm);
  std::cout << Terminal::CURSOR_SHOW;
  std::cout << Terminal::AUTO_WRAP_SET;
  std::cout << std::flush;
}

// Screen

void Screen::Init() {
  Terminal::init();
  Terminal::prepare();
  
  Size s = Terminal::getSize();
  width = s.width;
  height = s.height;

  // Allocate the buffer
  buffer = new Char[width * height];
}

void Screen::Draw() {
  std::stringstream ss;

  ss << Terminal::CURSOR_POSITION(0, 0);
  ss << Terminal::ERASE_SCREEN; // TODO: test w/o

  for (int y = 0; y < height; ++y) {
    if (y != 0) {
      ss << Terminal::NEW_LINE << Terminal::CARRIAGE_RETURN;
    }

    for (int x = 0; x < width; ++x) {
      auto& c = buffer[y * width + x];
      ss << c.Character;
    }
  }

  std::cout << ss.str();
  std::cout << std::flush;
}

void UpdateCharacterStyle() {

}

#endif // CURED_IMPLEMENTATION
#endif // CURED_H