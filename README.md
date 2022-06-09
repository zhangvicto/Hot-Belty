# Hot Belty
A high temperature conveyor belt low-cost open-source 3d-printer for printing engineering plastics such as PEKK/PEEK/PEI. 

# Current Progress
<img src="/img/render.png" alt="drawing" />
<img src="/img/motion.gif" alt="gif">
https://www.youtube.com/shorts/wCqyctF1fq8

- [x] Find improvements from previous Design
- [x] Part Selection
- [x] Belt Design
- [x] CAD design
- [x] Material purchasing
- [x] Testing Enclosure Heating
- [x] Building
- [x] Firmware Software Implementation
- [x] Enclosure Software
- [ ] Troubleshooting and Tuning (5%)
- [ ] Enclosure Extension Design (20%)

# Printer Specification Goals
## 24V System
Since 24V components cost the same as 12V, we can use thinner wires which are cheaper. 24V components are also more readily available compared to 12V.

## Enclosure Temp
The focus is on printing PEKK/PEEK and PEI, which are best printed at an enclosure temperature between 150C - 200C. It is also achievable with temperature of 135C with very careful tuning. Since the conveyor belt does not provide the best bed adhesion, it is better to have a higher temperature at which the plastic material can be properly 3d-printed to prevent failures and warping. 

## Bed Temperature
A bed temperature of 200C+ is absolutely needed for printing PEKK/PEEK/PEI, especially since the belt does not transfer all of the heat, the bed heater will need to reach near 250C to ensure bed adhesion. A 1200W AC 120V 400mm square silicone heater is used to speed up heating and it will be sufficient to heat up the 450mm square aluminum bed. The bed heats up to 60C in around 20 seconds. 

# Electronics
An off-the-shelf 3d-printer motherboard/controller will be used for this printer. Relays will be used to control the bed and enclosure as they are powered directly from mains. Limit switches will be used as end stops for the X and Y axes, the belt will have no end stop. 

## Design Methodology
# Iterative & Simple
The goal of the design is to come close to a finalized machine as possible before actual fabrication. During this design phase, the parts will be designed at first to be minimally viable, then optimized in terms of appearance and weight. The optimization is either done through a combination between finite element analysis (FEA) and using design for manufacturing and assembly. 

# Parts Fabrication 
## Belt Fabrication
1. Cut to size with aviation snips. 
2. Tape the ends together with Kapton tape. 

## Frame Parts
Most parts will be 3d-printed in polycarbonate, nylon, or PETG. 

## Open-Source Licenses
<img src="/img/oshw_facts.png" alt="OS"/>

---
Special thanks to Dr. Pearce and the FAST Laboratory.
