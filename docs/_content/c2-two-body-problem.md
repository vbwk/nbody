---
layout: post
title: "the n-body problem"
permalink: /two-body-problem/
---

The aim of the *n*-body problem is to predict the motion of a system of bodies bound by a central potential field. In these situations all the interaction forces between the bodies are directly derivable from the potential, and depend only on the positions of the bodies. Common examples are the gravitational *n*-body problem, where bodies interact via the attractive gravitational force

\\[
\v F_{ij} = \frac{ G m_i m_j }{ r_{ij}^2 } \hv r_{ij}
\\]

or the electrodynamics problem where particles interact via the electrostatic force

\\[
\v F_{ij} = \frac{ 1 }{ 4 \pi \eo } \frac{ q_i q_j }{ r_{ij}^2 } \hv r_{ij} 
\\] 

The general procedure in solving the problem involves adding up all the interaction forces for each body and integrating its equations of motion. Since all the forces have a specific form, the problem is fairly easy to formulate mathematically, and for few-body systems, fairly easy to simulate.  

But as more bodies are included a system, the number of interactions increases on the order of $n^2$, which creates some challenges: one is computational complexity---that the number of forces to individually compute and add up becomes prohibitively large. 

Another is dynamical complexity: though the individual forces have a simple form, when they add up in large numbers the resultant motion becomes increasingly complex and unpredictable. As a result most *n*-body systems are considered dynamically unstable and have a high propensity to undergo chaotic motion. The only exception is the restricted case when $n=2$ (the two-body problem). It is the only instance of the problem with stable behaviour for all configurations---and for this reason only the two-body problem has been solved completely. Systems with $n \geq 3$ start to exhibit chaotic behaviour, and there are no general analytic methods to solve the problem in these cases. Though the motion can be (and usually is) approximated using numerical solvers, for complex systems there are extra considerations to account for, such as singularities (e.g. divergent trajectories, collisions) and non-conservative forces.

For systems with many bodies the methods of statistical mechanics are often used. Monte Carlo Green functions, particle mesh methods, neural networks.

## properties 

Each body is described by 3 coordinates in 3D Euclidean space, so for a system of $n$ bodies there are 3n coordinates. 

Coordinates/degrees of freedom.  


## the two-body problem

The motion of a two body system is the only case of the $n$-body problem that is dynamically stable enough to have been solved completely. Though the two-body problem is really an approximation, since there aren't really any truly isolated two-body systems, the analytic solution is a "decent" approximation to the motion of "mostly" isolated systems. Many celestial orbits, such as a moon orbiting a planet, or a planet orbiting a star, can in fact be treated as mostly isolated two-body systems, so the problem is still applicable.  

Always begin by treating the two-body problem, since data and methods of two-body systems allow us to determine the interaction between constituents in many-body systems. 

The other reason is that many large systems can be approximated by two-body systems or groupings of two-body systems, e.g. though the solar system is usually understood as an eight or nine-body system, the individual orbits of planets are isolated enough from each other that they can be modelled by two-body systems. 

## kepler's model of planetary orbits

Kepler was the first to properly understand the geometry of planetary orbits, reified in his three laws of planetary motion:

1. planets move in elliptical orbits, with the Sun at one of the two foci
2. a line joining the planet to the Sun sweeps out equal areas in equal amounts of time
3. the orbital period, $\tau$, is related to the semimajor axis of the ellipse, $a$, via the relation $\tau^2 \propto a^3$

The laws can be visualised as follows:
 
`kepler-laws.gif`

At the time (1619) this model of planetary motion was the best fit for the data. The first law gave a consistent geometry for all the observed planets; the second law accounted for Kepler's observation that planets seemed to get faster as they approached the Sun, and vice versa; and the third law related the orbit of one planet to another. But these laws were purely empirical, not physical, and only gave a geometric description of the motion, not a causal one.  

The modern analytic approach to understanding planetary motion was devised by Newton, with the introduction of the laws of motion and universal gravitation (1687). This allowed the problem to be cast as a central force problem. It turned out that Newton's formulation in fact mostly validated Kepler's geometric model. Newtonian mechanics (and other formulations of mechanics) was able to prove that the mathematical equation of a planet's orbit is in fact the equation for an ellipse (derivation in the next section). 

Newtonian mechanics also proved Kepler's second law: in a short time $\d t$ the area swept out by the planet's orbit is:

\\[
\d A = \tfrac 12 | \v r \times \v v \; \d t |
\\] 

Replacing $\v v$ by $\v p / m$ and dividing both sides by $\d t$:

\\[
\dd A t = \frac{ 1 }{ 2m } | \v r \times \v p | = \frac{ 1 }{ 2m } \v l
\\]

since angular momentum $\v l = \v r \times \v p$. Since angular momentum is conserved in an isolated system, $\v l$ is constant, and the rate of change of area $\d A / \d t$ must also be constant.  

The only disagreement was that Newton's third law (equal/opposite forces) required that the gravitational pull of a planet must also cause the Sun to move. In reality both the planet and the Sun orbit aroud their mutual barycentre (centre of mass), but the Sun is so heavy that the motion imparted to it by any planet is essentially negligible. This approximation is only valid if one mass is much heavier than the other (as is often the case in planetary orbits); if the two bodies have similar mass the barycentric motion is more apparent: 

`kepler-equalmasses.gif`

## solving the two-body problem

The two-body problem is the only instance of the *n*-body problem stable enough to be solved in full generality. 

The problem is usually set up in a fixed reference frame where $\boldsymbol r_1$ and $\boldsymbol r_2$ denote the positions of each body, and $m_1$ and $m_2$ their masses: 

`two-body-setup.png`

Note also the following quantities:

* $\cdot$ the system's centre of mass position: 

\\[ \boldsymbol R = \frac{m_1 \boldsymbol r_1 + m_2 \boldsymbol r_2}{m_1 + m_2} \tag{2} \\]

* $\cdot$ the relative position: 

\\[ \boldsymbol r = \boldsymbol r_2 - \boldsymbol r_1 \tag{3} \\]

* $\cdot$ the total mass: 

\\[ M = m_1 + m_2 \tag{4} \\]

Each body exerts a force on the other given by Newton's law of gravitation. The two equations of motion in this reference frame are:

\\[ \boldsymbol F_{1} = m_1 \ddot{\boldsymbol r}_1 = \frac{Gm_1 m_2}{r^3}(\boldsymbol r_2 - \boldsymbol r_1) \tag{5} \\]

\\[ \boldsymbol F_{2} = m_2 \ddot{\boldsymbol r}_2 = \frac{Gm_1 m_2}{r^3}(\boldsymbol r_1 - \boldsymbol r_2) \tag{6} \\]

These are a set of coupled nonlinear differential equations. The goal of the problem is to solve these equations for $\boldsymbol r_1(t)$ and $\boldsymbol r_2(t)$, which will give the trajectories of the two bodies for all time.

Solving the problem analytically requires first uncoupling the equations of motion [in their current form they are considered to be coupled since the two dependent variables $\v r_1$ and $\v r_2$ appear in both equations, meaning they are dependent on each other]. To uncouple the equations they must be recast in terms of a set of independent coordinates. It turns out that in many conservative *n*-body systems, the best choice of coordinates is the centre of mass position $\boldsymbol R$ and the relative position $\boldsymbol r$. The main reason is that they exploit the symmetries and conservation properties of the system to simplify the overall dynamics (more on this in a bit). Crucially, these coordinates still capture the essential dynamics of the system (e.g. total momentum and energy) but are dynamically independent, so using them reduces the formalism without changing the nature of the problem (coordinates of this kind are known as Jacobi coordinates).  

The transformations between the base coordinates and the Jacobi coordinates are as follows:

\\[ \boldsymbol r_1 = \boldsymbol R + \frac{m_2}{M} \boldsymbol r \hspace{2cm} \boldsymbol r_2 = \boldsymbol R - \frac{m_1}{M} \boldsymbol r \tag{7} \\]

Substituting these into equations 5 and 6 gives:

\\[ m_1 \big( \ddot{\boldsymbol{R}} + \tfrac{m_2}{M} \ddot{\boldsymbol{r}} \big) = \frac{G m_1 m_2}{r^3} \bigg[ \big( \boldsymbol{R} - \tfrac{m_1}{M} \boldsymbol{r} \big) - \big( \boldsymbol{R} + \tfrac{m_2}{M} \boldsymbol{r} \big) \bigg] \tag{8} \\]

\\[ m_2 \big( \ddot{\boldsymbol R} - \tfrac{m_1}{M} \ddot{\boldsymbol r} \big) = \frac{G m_1 m_2}{r^3} \bigg[ \big( \boldsymbol R + \tfrac{m_2}{M} \boldsymbol r \big) - \big( \boldsymbol R - \tfrac{m_1}{M} \boldsymbol r \big) \bigg] \tag{9} \\]

Adding and subtracting equations (9) and (9) give the following two equations:

\\[ M \ddot{\boldsymbol R} = 0 \tag{10} \\]  

\\[ \mu \ddot{\boldsymbol r} = \frac{GM}{r^2} \tag{11} \\] 

Equation (10) is an equation of motion for the centre of mass. That it equals zero means the centre of mass behaves like a free particle and does not accelerate. 

Equation (11) is an equation of motion for the relative position. It has the form of Newton's law of gravitation, but for a body of mass $\mu$, which is a new quantity known as the _reduced mass:_ 

\\[ \mu = \frac{m_1 m_2}{m_1 + m_2} \tag{12} \\]

Equations (10) and (11) are uncoupled. The original two-body problem can now be solved as two independent one-body systems, one describing the motion of the centre of mass and the other describing the motion of the relative position. Moreover, since the centre of mass motion is trivial (it travels with constant velocity), it can be solved for all time from just the initial conditions. All that remains is to solve the equation for the relative position. The solutions for $\boldsymbol R(t)$ and $\boldsymbol r(t)$ can be easily substituted back into the original coordinates $\boldsymbol r_1$ and $\boldsymbol r_2$ to give the trajectories of the two bodies.  

## the equation of orbit

solution for $r(\phi)$. 

## dynamical stability

proof of virial theorem for the two body problem. 
