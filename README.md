# CPPND: Udacity Capstone Project : Multithreaded Webcrawler to fetch Pokemon Informations

It fetches pokemon informations (name, weight, height and decription) from website (https://www.pokemon.com/) and writes it to file (pokemons.txt). I got this idea from: https://youtu.be/swrjBDQTv6c

Program takes 2 optional argument variable; the first one is number of threads, the second one is number of pokemons to be fetched.

For example, if you run program using this command `./fetch_pokemons 8 40`, It will use 8 thread and fetches informations of randomly chosen 40 pokemons. (Actually, there is no implementation about randomization, it comes from the nature of concurrency)

## Dependencies for Running Locally

* cmake >= 3.7
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
* gcc/g++ >= 9.3
* libcurl (c++ library, package name is 'libcurl-devel' in linux) >= 7.66

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./fetch_pokemons`.
  - command line arguments `./fetch_pokemons [int:number of threads:default=4] [int:number of pokemons to be fetched:default=100]`