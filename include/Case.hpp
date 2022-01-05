#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Boundary.hpp"
#include "Discretization.hpp"
#include "Domain.hpp"
#include "Fields.hpp"
#include "Grid.hpp"
#include "PressureSolver.hpp"
/**
 * @brief Class to hold and orchestrate the simulation flow.
 *
 */
class Case {
  public:
    /**
     * @brief Parallel constructor for the Case.
     *
     * Reads input file, creates Fields, Grid, Boundary, Solver and sets
     * Discretization parameters Creates output directory
     *
     * @param[in] Input file name
     */
    Case(std::string file_name, int argn, char **args);

    /**
     * @brief Main function to simulate the flow until the end time.
     *
     * Calculates the fluxes
     * Calculates the right hand side
     * Solves pressure
     * Calculates velocities
     * Outputs the solution files
     */
    void simulate();

  private:
    /// Plain case name without paths
    std::string _case_name;
    /// Output directiory name
    std::string _dict_name;
    /// Geometry file name
    std::string _geom_name{"NONE"};
    /// Relative input file path
    std::string _prefix;
  


    /// Simulation time
    double _t_end;
    /// Solution file outputting frequency
    double _output_freq;

    Fields _field;
    Grid _grid;
    Discretization _discretization;
    std::unique_ptr<PressureSolver> _pressure_solver;
    std::vector<std::unique_ptr<Boundary>> _boundaries;
    //solver type
    std::string _pressure_solver_type;
    // vector of pairs storing the solvers, and unique pointers to the same
    std::map<std::string, std::shared_ptr<PressureSolver>> _map_solver_pointer;
    
    /// Solver convergence tolerance
    double _tolerance;

    /// Inlet pressure
    double _PIN;

    /// INlet Velocity
    double _UInflow;

    /// Maximum number of iterations for the solver
    int _max_iter;

    //introduce xlength 
    double _xlength;

    //introduce ylength
    double _ylength;

    // Switching frequency and starting solver
    std::string _start_solver;
    int _switching_frequency;
    int _is_adaptive = 0;

    /// A variable that sets oscillation on or of
    bool oscillation{false};
    
    /// Oscillation frequency
    double oscillation_frequency{0};


    /**
     * @brief Creating file names from given input data file
     *
     * Extracts path of the case file and creates code-readable file names
     * for outputting directory and geometry file.
     *
     * @param[in] input data file
     */
    void set_file_names(std::string file_name);

    /**
     * @brief Solution file outputter
     *
     * Outputs the solution files in .vtk format. Ghost cells are excluded.
     * Pressure is cell variable while velocity is point variable while being
     * interpolated to the cell faces
     *
     * @param[in] Timestep of the solution
     */
    void output_vtk(int t, int my_rank = 0);

    void build_domain(Domain &domain, int imax_domain, int jmax_domain);
};
