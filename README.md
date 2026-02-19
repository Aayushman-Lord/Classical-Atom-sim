# Atomic Simulator (Classical Electric Force Model)

A real-time 2D atomic simulator written in C++ using Raylib.  
This project simulates subatomic particles (protons, neutrons, electrons) using classical physics with Coulomb electric forces.

This is a **classical approximation**, not a quantum simulation.

---
## Important Notice 
This repo is created in c++, MAKEFILE is just used to compile 

---
## Preview

Features stable electron orbit around a proton using correct orbital velocity and inverse-square electric force.

---

## Features

• Real-time particle simulation  
• Coulomb electric force interaction  
• Stable orbital mechanics  
• Multiple particle support  
• Smooth rendering using Raylib  
• Particle trails visualization  
• Elastic collision system (optional)  
• Numerically stabilized force using softening  

---

## Physics Model

This simulator uses classical force equations:

### Coulomb's Law

F = k * (q₁ q₂) / r²

Where:

- F = force
- k = electric constant (scaled)
- q₁, q₂ = particle charges
- r = distance

### Newton's Second Law

a = F / m

### Velocity Update

v = v + a·dt

### Position Update

x = x + v·dt

---

## Stable Orbit Formula

Orbital velocity is calculated using:

v = sqrt(k |q₁ q₂| / (m r))

This ensures stable circular orbit.

---

## Technologies Used

- C++
- Raylib (graphics and rendering)
- Classical mechanics
- Real-time simulation

---


---

## Installation

### Install Raylib

Windows (MinGW):

Download Raylib from:
https://www.raylib.com/

---

### Compile

Press f5 


---

## Controls

Currently automatic simulation.

Future planned controls:

- Spawn particles
- Reset simulation
- Adjust constants

---

## Example Simulation

Simulates:

- Proton at center
- Electron orbiting proton
- Electric force interaction

---

## Limitations

This is a classical simulation.

Real atoms require quantum mechanics.

This project is intended for:

- visualization
- learning physics
- experimentation
- simulation programming

---

## Future Improvements

- Energy visualization
- Field visualization
- GPU acceleration
- Quantum probability visualization

---

## Author

Aayushman

---


## Inspiration

Classical mechanics, atomic models, and physics simulation engines.

---

## Contributing

Pull requests welcome.
Feel free to improve physics accuracy or performance.

---
## LICENSE
MIT License



