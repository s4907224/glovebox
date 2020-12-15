# gloveBox

## Overview
 gloveBox is designed to be a lightweight, optimised game engine at _runtime_.  The general ethos of it as a project is to leverage precomputing actions before runtime[^1] - and in cases saving this built data to disk to save on repetetive, expensive pre-runtime calculations.

 As the project is being primarily developed on a MacBook without a dedicated graphics card, the idea is to take advantage of the relatively powerful CPU to lessen the bottleneck of the integrated graphics.

 That being said - gloveBox will eventually be ported onto Windows & Linux based operating systems.

## Current Development Focus
Initial time will be spent on developing a fresh, lightweight rendering pipeline.  Once a basic model can be rendered with phong shading & a basic interactive camera, only then will more complex development occur.

## Long Term Plans
While a large focus on gloveBox will include precomputation and offline optimisation, efforts will be made to increase performance during runtime too, through utiling a LOD system for meshes, along with an improved TAA post process.

Larger long term plans will be revealed when they are set into motion and a proof of concept has been drafted up!

[^1]: (where runtime refers to when the graphics engine is actively rendering).
