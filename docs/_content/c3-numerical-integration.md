---
layout: post
title: "numerical integration &amp; validation"
permalink: /numerical-integration/
---

The simplest numerical method to solve the *n*-body problem is using an integrator, since the equations of motion are second order ODEs that must be integrated to give the positions of the bodies. Presented in this section are a few different integrators for the gravitational $n$-body problem using Verlet and Runge-Kutta. Most of the integrators are written in C and the analysis scripts are written in R, and can be found here.  


There are a total of 6n equations of motion to solve. The most basic methods are numerical integrators, which involve discretising the time space and using some extrapolation method to estimate the position at the next time interval. These methods are generally reliable, and easy to implement when forces are simple. 


## setup 

In Cartesian coordinates, $\v r = \v r(x,y,z)$, and there are three second order ODEs that must be integrated for each body:

`6n ODEs`

For n bodies there are a total of 3n second order ODEs for the whole problem. Most integrators involve transforming these equations into 6n first order equations, by defining a velocity variable $\v v$: 

\\[
\dv r = \v v 
\\]

where $\v v = \v v(v_x, v_y, v_z)$. Equation (1) can then be written as a first order equation in the form $\dv v = f(\v r, t)$ and the solution for $\v v(t)$ can be recombined to get $\v r(t)$.  

## validation with the two-body problem

Since the two-body problem has an exact analytic solution, it is the best case to test the accuracy of a numerical method. Here is some code that returns the exact orbit coordinates of the two-body problem, as given by the analytic solution. Below is a table showing the accuracy of Verlet and RK4 integrators for the same initial conditions:

`do`

Below are graphs showing the energy stability of the Verlet and RK4 integrators:

`do`

## singularities 

Numerical integrators are completely valid most few-body simulations and yield fairly representative orbit paths. With many-body systems the dynamical complexity of the orbits is harder to model, in particular cases where there are numerical singularities (when particles get close or collide). Here is an example:

`do`

The rapidly oscillating orbit path following the collision is a result of the potential energy exploding as the particles collide. This can be controlled for using regularisation or allowing for non-conservative collision forces to enter the simulation code. Examples of this will be discussed in a later post. 

