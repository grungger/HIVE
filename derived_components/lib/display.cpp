#include "display.hpp"

namespace Virtual{

Display::Display(ptr_t save, ptr_t flush, ptr32_t input, double SPF) {
  input_pointers_[0] = save;
  input_pointers_[1] = flush;
  word_input_pointers_[0] = input;
  SPF_ = SPF;
  t_last_frame_ = std::chrono::high_resolution_clock::now(); // maybe not necessary
}

Display::~Display() {
  bool debug = false;
  if (not debug) {
    const char* reset = "\x1b[?1049l\x1b[?25h";
    ::write(STDOUT_FILENO, reset, std::strlen(reset));
  }
}

void Display::compute_output() {
  bool debug = false;
  // Display startup
  if (*input_pointers_[1] and display_memory_.size()==0) {
    if (not debug) {
      std::cout << "\x1b[?1049h\x1b[?25l";
      std::cout << "\x1b[H";
      std::cout.flush();
    }
    t_last_frame_ = std::chrono::high_resolution_clock::now();
    return;
  }
  // Display flush
  else if (*input_pointers_[1]) {
    if (not debug) {
      std::cout << "\x1b[H";
    }
    if (display_memory_.size()%2!=0) {
      display_memory_.push_back(0);
    }
    for (size_t i=0; i<display_memory_.size()/2; i++) {
      for (int j=0; j<32; j++) {
        std::cout << (display_memory_[2*i].value & (1u << j) ? (display_memory_[2*i+1].value & (1u << j) ? "\u2588" : "\u2580")
						       : (display_memory_[2*i+1].value & (1u << j) ? "\u2584" : " ") );
      }
      std::cout << "\n";
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> time_now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_since = time_now - t_last_frame_;
    if (time_since.count() < SPF_) {
      std::this_thread::sleep_for(std::chrono::duration<double>(SPF_)-time_since);
    }
    std::cout.flush();
    t_last_frame_ = std::chrono::high_resolution_clock::now();
    display_memory_.clear();
    return;
  }
  else if (*input_pointers_[0]) {
    display_memory_.push_back(*word_input_pointers_[0]);
    return;
  }
  else {
    return;
  }
}

void Display::printMemory() {
  for (auto it=display_memory_.begin(); it<display_memory_.end(); it++) {
    std::cout << (*it) << " ";
  }
  std::cout << std::endl;
}


const std::string Display::gate_name = "Display";

} //namespace Virtual
