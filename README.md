# OOPD-Project

# Used Libraries
  * `#include <thread>`
  * `#include <unistd.h>`
  * `#include <filesystem>`

# Usage of special some function
  * `getopt`
       -> variable `optind` used to points to next argument in argv

# Commands Implemented
* cd 
    * Usage:-> cd DEST\n or: cd -h\n
                -h   Get help text
                Change current path to the given one.
       
* mv 
   * Usage:-> mv [OPTION] SRC DEST\n" or: mv [OPTION] SRC... DIRECTORY\n"
              ->Renames SRC to DEST or moves all SRC to DIRECTORY.
                -h   Get help text
                -f   Forcibly overwrite
                -i   Prompt before overwrite
* rm
    * Usage:-> rm [OPTION]... FILE...\n
               Remove(unlink) the FILE.\n\n
               -h   Get help text
               -r   Recursively delete directories
               -v   Get description of each step(implicitly recursive)
               -i   Get prompts before every file deletion(implicitly recursive)
* ls 
   * Usage:-> ls [OPTION] [DEST]\n
              List directories and files in DEST.
               -a   List all directories
               -h   Get help text
* cp
    * Usage:-> cp [OPTION] SRC DEST\n
               Copies contents from  SRC to DEST.
               -h   Get help text
               -r   Recursively copy directories
               -v   Get description of each step(implicitly recursive)

# Multi threaded version available of following commands
* cp
* rm

# profiling of the code Without Multithreadeing 
* ![Alt text](<readme 1-1.png>)

# Profiling of code with Multithreading
* ![Alt text](<readme 2 with thread.png>)




