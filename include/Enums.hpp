#pragma once

// If no geometry file is provided in the input file, lid driven cavity case
// will run by default. In the Grid.cpp, geometry will be created following
// PGM convention, which is:
// 0: fluid, 3: fixed wall, 4: moving wall
namespace LidDrivenCavity {
const int moving_wall_id = 8;
const int fixed_wall_id = 4;
const double wall_velocity = 1.0;

} // namespace LidDrivenCavity

// TVR: members for each side of the cavity (boundary perimiter)
enum class border_position {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
};

// TVR: ID for each side of the cavity. Note that this changes for arbitrarily shaped domains, and have to be modifed
// as seen fit. If not required for core functionality, then it can be ignored.
namespace border {
const int TOP = 0;
const int BOTTOM = 1;
const int LEFT = 2;
const int RIGHT = 3;
} // namespace border

// TVR: Does this indicate what the cell is? like a cell may be in a fluid medium, or it may be a part of the BC. Note
// that ghost nodes are given to faciliate the spatial discretization, and also because of the way in which the cell's
// x-velocity, y-velocity, and pressure are defined. What is the type of cell given to a ghost node
enum class cell_type {

    FLUID,
    INFLOW,
    OUTFLOW,
    NO_SLIP,
    MOVING_WALL
   
};

namespace cellID{
    const int FLUID_ID = 0; // Fluid cell in domain
    const int INFLOW_ID = 1; // Ghost cell at inflow (fluid nevertheless)
    const int OUTFLOW_ID = 2; // Ghost cell at outflow (fluid nevertheless)
    const int NO_SLIP_ID = 3; // by default is fixed
    const int MOVING_WALL_ID = 8; // Moving wall
}


