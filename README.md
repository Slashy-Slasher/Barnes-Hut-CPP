# Brute force Method of Gravity

<p align="center">
  <img src="videos/Stress-Test-Bruteforce.gif" alt="Quadtree Demo" />
</p>

<p align="center">
  <img src="videos/ID_Demo.gif" alt="Quadtree Demo" />
</p>

<br>https://en.wikipedia.org/wiki/Newton%27s_law_of_universal_gravitation</br>
Largest term in O notation: n ^ 2
At 2000 planets the sim is able to achieve 30fps
At 4000 planets the sim is able to achieve 10fps
The scaling is non-linear but its far faster than python was able to achieve

# Quadtree Partitioning Method(Barnes-Hut)
<br>[Quadtree Wikipedia](https://en.wikipedia.org/wiki/Quadtree)</br>
**Largest term in O notation:** `n log n`

Instead of directly calculating gravitational force between every pair of planets, the simulation recursively partitions space into quadrants. Each quadrant stores its **combined mass** and **center of mass**, allowing distant groups of planets to be approximated as a single body.

- Reduces the number of force calculations dramatically compared to the brute-force `O(n^2)` method.  
- Adaptive subdivision ensures dense regions of space are more finely partitioned, while sparse regions remain aggregated.  
- Enables **real-time interactivity** even as the number of simulated planets grows into the thousands.  

This method, combined with efficient memory management and input handling, makes the simulation significantly more scalable than brute force, while still preserving accurate orbital behavior.

Largest term in O notation: n log n

This project is my 3rd iteration on the concept of a solar simulation and my 2nd iteration on a Barnes-Hut.

While I've already done this project before, this has already proven to have it's own unique challenges.




## CMAKE

CMAKE is a newer concept for me, having used C++ in the past primarily for single file programs I thought it finally time to learn a header/package management system like CMAKE or MAKE.

I chose CMAKE because it functions at a higher level of abstraction than traditional make and allows for better cross-platform support. The C in CMAKE stands for cross-platform.
