#!/bin/zsh

RED="\e[31m"
GREEN="\e[32m"
MAGENTA="\e[95m"
CYAN="\e[96m"
ENDCOLOR="\e[0m"
BOLDGREEN="\e[1;${GREEN}m"
BOLDRED="\e[1;${RED}m"

print "WELCOME TO THE SHOW!"
print "${MAGENTA}Test 1. FOREVER ALONE${ENDCOLOR}"
print "${GREEN}./philo 1 800 200 200${ENDCOLOR}" ; ./philo 1 800 200 200
print "${MAGENTA}Test 2. LET'S CHECK HOW MANY TIMES THEY EAT${ENDCOLOR}"
print "${GREEN}./philo 5 800 200 200 7 | grep 'Philosopher 5 is eating' | wc -l
${ENDCOLOR}" ; ./philo 5 800 200 200 7 | grep '5 is eating' | wc -l
print "${GREEN}./philo 5 800 200 200 7 | grep 'Philosopher 1 is eating' | wc -l
${ENDCOLOR}" ; ./philo 5 800 200 200 7 | grep '1 is eating' | wc -l
print "${GREEN}./philo 5 800 200 200 7 | grep 'Philosopher 4 is eating' | wc -l
${ENDCOLOR}" ; ./philo 5 800 200 200 7 | grep '4 is eating' | wc -l
print "${MAGENTA}Test 3. DIIIIEEEEE!${ENDCOLOR}"
print "${GREEN}./philo 4 310 200 200${ENDCOLOR}" ; ./philo 4 310 200 200
print "${MAGENTA}Test 4. DEATH DELAY 10 MS${ENDCOLOR}"
print "${GREEN}./philo 2 310 300 200${ENDCOLOR}" ; ./philo 2 310 300 200
print "${MAGENTA}Test 5. SAY NO TO DEATH${ENDCOLOR}"
print "${GREEN}./philo 5 800 200 200${ENDCOLOR}" ; ./philo 5 800 200 200
print "${MAGENTA}Test 6. NORMALLY PHILOSOPHERS SHOULD AVOID DYING${ENDCOLOR}"
print "${GREEN}./philo 4 410 200 200${ENDCOLOR}" ; ./philo 4 410 200 200
