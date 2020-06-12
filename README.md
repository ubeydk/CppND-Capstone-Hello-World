# CPPND: Capstone : Multithreaded Webcrawler to fetch Pokemon Informations

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

I always wanted code webcrawler, so I decided to code webcrawler for capstone project. I got the fetching pokemons idea from this video:
https://youtu.be/swrjBDQTv6c

Project fetches pokemon informations (name, weight, height and decription) from website (https://www.pokemon.com/) and write it to file (pokemons.txt). Program is fetching and processing websites using multithreads.

## Rubric Points

- Loops, Functions, I/O
- Object Oriented (except inheritance, I did not need inheritance)
- Memory Management (but I did not implement rule of three or five, I didn't need it)
- Concurrency

## Important

Program takes 2 argument variable; first one is number of threads, number of pokemons to be fetched.

For example, you call program like this "./fetch_pokemons 8 40", It will use 8 thread and fetches informations of randomly chosen 40 pokemons. (Actually, there is no implementation about randomization, it comes from the nature of concurrency)

 - I strongly suggest you to limit the number of pokemons to be fetched (40 is okay), otherwise it will take pretty much time to fetch all pokemons.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./fetch_pokemons`.
  - command line arguments `./fetch_pokemons [int:number of threads:default=4] [int:number of pokemons to be fetched:default=INT_MAX]`