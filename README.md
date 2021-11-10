# Hot Belty
A high temperature conveyor belt low-cost open-source 3d-printer for printing engineering plastics such as PEKK/PEEK/PEI. 

# Current Progress
<img src="/img/xy_gantry_v1.png" alt="drawing" />
XY Gantry Design V1 - incomplete
<img src="/img/drawing1.png" alt="drawing" width="300"/>
<img src="/img/drawing2.png" alt="drawing" width="300"/>
<img src="/img/drawing3.png" alt="drawing" width="300"/>

- [x] Insulation placement and method
- [x] Find improvements from previous Design
- [x] Material selection
- [x] Belt Design
- [ ] CAD design
- [ ] Select enclosure heating element
- [ ] Software
- [ ] Material purchasing

# Printer Specification Goals
## 24V System
Using a higher voltage system allows thinner wires to be used, saving costs. Also, components at 24V are the same cost as 12V components.

## Enclosure Temp
Focus is on printing PEKK/PEEK and PEI, which are best printed at an enclosure temperature between 150C - 200C. It is also achievable with temperature at 135C with very careful tuning. Since the conveyor belt does not provide the most bed adhesion, it is better to have a higher temperature at which the plastic material can be properly 3d-printed to prevent failures and warping. 

## Bed Temperature
A bed temperature of 200C+ is absolutely needed for printing PEKK/PEI, especially since the belt does not transfer all of the heat, the bed heater will need to reach near 250C to ensure bed adhesion. A 1200W 400mm square silicone heater is used to speed up heating and it will be sufficient to heat up the 450mm square aluminum bed. 

# Electronics
The Fysetc Spider will be used for this printer as it offers more than enough stepper drivers and has two output for bed, enabling heating for the bed and the enclosure. Relays will be used to control the bed and enclosure as they will be powered directly from the outlet. Limit switches will be used as endstops for the X and Y axes, the belt will have no end stop. 

# Parts Fabrication 
## Belt Fabrication
1. Tig weld the ends of stainless shim stock
2. Painters' tape on top of the belt

## Frame Parts
Most parts will be 3d-printed using polycarbonate or PETG. 

---
Special thanks to Dr. Pearce and the FAST Laboratory for their help.
