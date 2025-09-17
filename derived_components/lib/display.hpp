/*******************************************
 * @file display.hpp
 *
 * @brief Implementation of Display.
 *******************************************/
// Includes:
#include "wordmicrocircuit.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <unistd.h>  // POSIX write()

// Header Guards:
#ifndef DISPLAY_H
#define DISPLAY_H

namespace Virtual{

/**
 * @brief Display allows for writing words to a std::vector which can be flushed to display them to std::cout.
 *
 * Display defines a class which takes an arbitrarily long list of words in and upon flushing it displays the words
 *   as lines of an image, where the lowest bit is displayed on the left and increasing order to the right.
 *   This allows for an image of size 32xL where L is the number of words inputted before flushing. The component
 *   can be easily adjusted to allow for displaying 64xL or larger sizes. A bit value of 1 corresponds to a white square
 *   being outputted. Starting the display into the alternative screen buffer initially can be done by flushing with
 *   an empty display_memory_.
 */
class Display : public wordMicroCircuit<2,0,1,0,0,0,0> {

  protected:
    /**
     * @brief display_memory_ saves the output before flushing.
     */
    std::vector<word_t> display_memory_;

    /**
     * @brief SPF_ or seconds per frame sets the maximum frame rate for the display output.
     */
    double SPF_;

    /**
     * @brief t_last_frame_ is the time at which the last frame was displayed.
     */
    std::chrono::time_point<std::chrono::high_resolution_clock> t_last_frame_;

  public:
    /**
     * @brief Constructor for Display where the two ptr_t inputs toggle the saving of the input word and flushing additionally setting the max FPS.
     * @param save determines whether the input word is to be saved to display_memory_.
     * @param flush determines whether the display_memory is to be flushed to std::cout.
     * @param input is the word which is a line of the display output to be saved.
     * @param SPF the minimum secs per frame or max FPS for the display output.
     */
    Display( ptr_t save=ground, ptr_t flush=ground, ptr32_t input=ground32, double SPF=1.0 );

    /**
     * @brief Destructor for Display resets all escape codes to return terminal to original layout.
     */
    ~Display() override;
    
    /**
     * @brief compute_output checks whether the memory is to be flushed and whether the input is to be saved.
     * @note if the flush toggle is on, the save toggle will be ignored (no saving during flushing).
     */
    void compute_output();

    /**
     * @brief printMemory prints display_memory_ (for debugging).
     */
    void printMemory();

    static const std::string gate_name;
};

} //namespace Virtual

#endif
