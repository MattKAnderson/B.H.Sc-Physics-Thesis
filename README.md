# B.H.Sc-Thesis
During the 2017-18 academic year at McMaster university I completed an undergraduate thesis in the physisc department on a computational statistical physics topic. See MA_THESIS.pdf for the paper submitted. The simulation code was written in c++ in visual studio 2017. In the simulation code folder I have included all the .cpp and .h files.


**Some useful background knowledge for understanding:**

The goal of my undergraduate thesis was to do a Monte Carlo simulation of a Helicene chain (a chain of 6-carbon atom rings linked together) using a simple statistical physics model. The model assumes there is only 1 interaction between rings in the chain, the bending angle between rings. From this single interaction, the energy of a given conformation (aka permutation or state) of the chain is defined. The energy defines a probabilistic weight for the conformation. The probability of being in a conformation is then the weight over the weighted sum of all conformations (known as the partition function). Similarly, the probability that a given propery such as the end-to-end distance of the molecule has a particular value is the weighted sum of all conformations that have that value over the partition function (as many conformations may have the same value for a given propert). However, the total number of conformations is infinite, and the partition function cannot be numerically computed exactly if you cannot integrate the energy function over the phase space of the system for an analytic expression (which becomes unfeasible even for the simple model when the dimensions of phase space (i.e. number of angles between adjacent rings) increases).

A solution to this is to use a monte carlo method to approximate the evaluation of the integral. In particular I used the **metropolis-hastings algorithm.** In statistical physics the weight given to a conformation is the boltzmann factor which is an exponential function of the negative of the energy. So, when energy is high, the boltzmann factor is tiny and the probability of that conformation existing is tiny (as it should be). The metropolis-hastings algorithm takes advantage of this to avoid sampling (most of the time) the phase space of the integral where the integrand is essentially zero. The algorithm selectively samples the phase space by taking the difference of the energy of the proposed next conformation and the current conformation, taking the boltzmann factor of that energy difference, then using that as the probability that the proposed next conformation is the next sample point. This results in the algorithm preferentially sampling points that have decreasing energy (thus preferentially sampling the greatest contributor to the value of an integral)


**Some useful explanation of how the model was implemented**







Link to thesis supervisor page: https://www.physics.mcmaster.ca/component/comprofiler/userprofile/shi.html?Itemid=351
