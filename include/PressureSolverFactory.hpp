#include<cassert>
#include<memory>
#include<string>
#include "PressureSolver.hpp"
#include<cassert>
#include<utility>
    
inline void CreatePressureSolver(std::unique_ptr<PressureSolver>& p_pressure_solver,
                                                            const double& sor_omega,
                                                            const int& v1,
                                                            const int& v2,
                                                            const std::string& solver_type,
                                                            const Domain& domain)
{
    if(solver_type == "SOR")
    {
        p_pressure_solver = std::make_unique<SOR>(sor_omega);
    }
    else if(solver_type == "JAC")
    {
        p_pressure_solver = std::make_unique<JAC>();
    }
    else if(solver_type == "GAS")
    {
        p_pressure_solver = std::make_unique<GAS>();
    }
    else if(solver_type == "MGV")
    {
        p_pressure_solver = std::make_unique<MGV>(v1,v2);
    }
    else if(solver_type == "MGW")
    {
        p_pressure_solver = std::make_unique<MGW>(v1,v2);
    }
    else if(solver_type == "CG")
    {
        p_pressure_solver = std::make_unique<CG>(domain);
    }
    else 
    {
        if(solver_type.empty())
        {
            std::cout<< "No solver input, by default SOR is chosen!"<<std::endl;
            p_pressure_solver = std::make_unique<SOR>(sor_omega);
        }
        
        else
        {
            std::cout<<"Solver input: "<<solver_type<<" is invalid."<<std::endl;
            std::cout<<" SOR is chosen as solver!"<<std::endl;
            p_pressure_solver = std::make_unique<SOR>(sor_omega);
        }
    }

}

// Creates a map of solvers, and unique pointers to them. This is only initialized for adaptive solver functionality
// first -> solver name
// second -> unique pointer to the solver
inline void CreatePressureSolverMapForAdaptiveMethod(std::map<std::string, std::shared_ptr<PressureSolver>>& _map_solver_pointer,
                                                            const double& sor_omega,
                                                            const int& v1,
                                                            const int& v2,
                                                            const Domain& domain)
{
    // vector of solvers
    std::vector<std::string> solvers;
    solvers.push_back("JAC");
    solvers.push_back("GAS");
    solvers.push_back("SOR");
    solvers.push_back("MGV");
    solvers.push_back("MGW");
    solvers.push_back("CG");

    // Making the pointer unique, and inserting the <solver type, unique pointer> pair into the map
    for(int i = 0; i<solvers.size(); i++)
    {
        // Creating a unique pointer for the pressure
        std::unique_ptr<PressureSolver> pCurrentSolver;
        // Make unique        
        CreatePressureSolver(pCurrentSolver, sor_omega, v1, v2, solvers[i], domain);
        // Perform move operation for easier map usage
        std::shared_ptr<PressureSolver> pSharedCurrentSolver = std::move(pCurrentSolver);
        // insert shared pointer
        _map_solver_pointer.insert({solvers[i], pSharedCurrentSolver});
    }
}


