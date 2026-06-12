# Humbat: Flower Evolution Model Simulation

Author: Kazuki Uchino  

## Research Question
Will flowers evolve in a way so that they will prefer bats or hummingbirds as their pollinators?

## Background Information
Hummingbirds and bats unintentionally pollinate plants while foraging for nectar in tropical and subtropical regions of the Americas. Research (Muchhala, 2007) shows that hummingbirds prefer narrower flowers and are less efficient in pollination, whereas bats forage for wider flowers and are more efficient. Due to higher feedback on pollen production, models indicate potential evolutionary shifts from bird to bat pollination (Muchhala and Thomson, 2010).

This application simulates the pollination processes and tracks how the distribution of flower corolla sizes shifts over generations under varying selective pressures and competition.

## Repository Directory Structure
For a clean GitHub organization, place source and UI configuration files into a dedicated directory:

```text
humbat/
├── humbat.pro               # Qt project configuration file
├── README.md                # Project documentation
└── src/                     # Source code files
    ├── main.cpp             # Application entry point
    ├── mainwindow.cpp       # Main controller and simulation engine logic
    ├── mainwindow.h         # Main window declarations and documentation
    ├── mainwindow.ui        # XML layout declaration for the UI window
    ├── flower.cpp           # Implementation of individual flower behaviors
    ├── flower.h             # Flower class definition and attributes
    ├── landscape.cpp        # Environmental map configuration logic
    └── landscape.h          # Landscape class definitions
```

## Setup and Installation
Dependencies:
- Qt 5 or Qt 6 Framework
- Qt Charts module
- C++17 compliant compiler

## Building from Command Line
1. Clone the repository to your local system.

2. Navigate to the root directory containing humbat.pro.

3. Generate the Makefile and compile:

```text
Bash
qmake humbat.pro
make
```

## Usage
1. Set Up Map: Enter the initial flower population count in the spin box (default: 10) and click Set up. This randomly populates the green 300x300 canvas grid.

2. Configure Selectivity Targets: Modify the minimum and maximum target corolla size bounds for hummingbirds and bats using the provided UI parameter spin boxes.

3. Execute Simulation: Click Start to run the processing loop through generations. The canvas maps positional drift, and the Real-time Chart renders the corolla size trends over time.
