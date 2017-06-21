# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

Manual Tuning Kp Ki Kd :
I took the code from repo and first ran the PID with some values for KP KI KD to check
the project setup.
I saw the value of CTE passed to simulator  and returned from simultaor.
I also noted that for CTE > 2.5  the car goes off Track.
So first tested the reset command working, By sedning reset command after evey 100 messages.
Then I took the rough values of Kp Ki and Kd from sebastins Lessons and checked how the cte is
moving.

So once this setup was ready now I wanted to tune manually kp ki kd such that I drove
till the bridge smoothly.
For that I searched how to manually tune PIDs
https://robotics.stackexchange.com/questions/167/what-are-good-strategies-for-tuning-pid-loops
Then followed these Instructions.
    Set all gains to zero.
    Increase the P gain until the response to a disturbance is steady oscillation.
    Increase the D gain until the the oscillations go away (i.e. it's critically damped).
    Repeat steps 2 and 3 until increasing the D gain does not stop the oscillations.

  Started with sebastins KP KI KD value increased Kp  until car is oscillation on track
  then increased Kd such we damp oscillations and then finally tried to make offset err to
  0 using Ki.

  I got Kp = 0.2;
        Ki = 0.004;
        Kd = 5.01;
Self Tuning using Twiddle:

   Then I started Twiddle to tune more.
   What was tricky in twiddle was there could not be for loop and while in here
   as we did in our lessons with sebastin.

   So made my own state transition machine and got twiddle running.
   The Prog flow is as follows.
   Initalize the program with  manual Kp Ki kd
   Check if you want to run twiddle or just run with assigned valued Kp kid kd
   using tune_param
   Then run the car for refrence count as defined by twiddle_run_ref.
   Here I initally choose this value to be 100 but realized that turning fails at sharp
   turns.so went from 100 to 200 and then finally 400.
   The algo runs for 400 steps accumlates err after 400 for other 400 steps.
   and save the average err.
   This err is compared with best_err .
   And twiddle stops when best_err is less than 0.02.
   Then the car keeps running with best choosen Kp Ki kd


   These are params initalized manually
    Kp = 0.2,Ki = 0.004,Kd = 5.01  avergae err is 0.2

   These are params derived from Twiddle
       Kp = 0.3,Ki = 0.104,Kd = 5.11  avergae err is 0.008

   For further improvement twiddle Algorithm (Implemented by me )needs tweak.
   It cannot start with Kp Ki Kd as 0 and attain some meaningful Kp Ki kd.







## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./
