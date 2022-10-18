using Plots # used for plotting
using BenchmarkTools # used for @btime
using LinearAlgebra # used for norm() function for error calculations

# importing solve and rhs! functions respectively
include("part_1.jl")
include("part_2.jl")

# Section 1.1
num_particles = 100 # number of particles used in simulation
u = 0.1 .+ 0.45 * rand(2, num_particles) # intitial position of particles
v3 = copy(u) # copying value of initial particle positions
saved_solutions_fe1 = solve(ForwardEuler(), v3, rhs!, (0, 1), 1/512, [5]) # solving for particle positions using Forward Euler method with timespan of 1 sec and dt of 1/512 under a specified velocity field
v4 = copy(u) # copying value of initial particle positions
saved_solutions_em1 = solve(ExplicitMidpoint(v4), v4, rhs!, (0, 1), 1/512, [5]) # solving for particle positions using Explicit Midpoint method with timespan of 1 sec and dt of 1/512 under a specified velocity field

# Plotting 1-second before and after solution using Forward Euler method
p1 = plot()
scatter!(p1, saved_solutions_fe1[1][1,:], saved_solutions_fe1[1][2,:], xlims=(-1, 1), ylims=(-1, 1), label = "t = 0")
scatter!(p1, saved_solutions_fe1[3][1,:], saved_solutions_fe1[3][2,:], xlims=(-1, 1), ylims=(-1, 1), label = "t = 1")
title!(p1, "Forward Euler Initial vs Final Positions")
plot(p1)
#png(p1, "FE_1_second_solution")

# Plotting 1-second before and after solution using Explicit Midpoint method
p2 = plot()
scatter!(p2, saved_solutions_em1[1][1,:], saved_solutions_em1[1][2,:], xlims=(-1, 1), ylims=(-1, 1), label = "t = 0")
scatter!(p2, saved_solutions_em1[3][1,:], saved_solutions_em1[3][2,:], xlims=(-1, 1), ylims=(-1, 1), label = "t = 1")
title!(p2, "Explicit Midpoint Initial vs Final Positions")
plot(p2)
#png(p2, "EM_1_second_solution")

# Section 1.2
num_particles = 100 # number of particles used in simulation
u = 0.1 .+ 0.45 * rand(2, num_particles) # intitial position of particles
dt = [1/16, 1/32, 1/64, 1/128, 1/256, 1/512, 1/1024] # timesteps to test solver functions with
error_fe = zeros(length(dt)) # empty array for storing error associated with Forward Euler method
error_em = zeros(length(dt)) # empty array for storing error associated with Explicit Midpoint method
for i = eachindex(dt)
    v5 = copy(u) # copying value of initial particle positions
    v6 = copy(u) # copying value of initial particle positions
    saved_solutions_fe2 = solve(ForwardEuler(), v5, rhs!, (0, 5), dt[i], [5]) # solving for particle positions using Forward Euler method with timespan of 5 sec and varying dt's under a specified velocity field
    saved_solutions_em2 = solve(ExplicitMidpoint(v6), v6, rhs!, (0, 5), dt[i], [5]) # solving for particle positions using Explicit Midpoint method with timespan of 5 sec and varying dt's under a specified velocity field
    error_fe[i] = norm(saved_solutions_fe2[3] - saved_solutions_fe2[1]) # Calculating error of Forward Euler method by taking the norm of the difference between the final and intitial particle positions
    error_em[i] = norm(saved_solutions_em2[3] - saved_solutions_em2[1]) # Calculating error of Explicit Midpoint method by taking the norm of the difference between the final and intitial particle positions
end

# Plotting Timestep Size vs Error for each solver method
p3 = plot()
plot!(p3, error_fe, dt, xaxis=:log, yaxis=:log, label = "Forward Euler", legend=:topleft)
scatter!(p3, error_fe, dt, label = false)
plot!(p3, error_em, dt, xaxis=:log, yaxis=:log, label = "Explicit Midpoint")
scatter!(p3, error_em, dt, label = false)
ylabel!(p3, "Timestep Size")
title!(p3, "Timestep Size vs Error")
xlabel!(p3, "Error")
plot(p3)
png(p3, "Timestep Size vs Error")

# Section 2.1 & 2.2
num_particles = 100 # number of particles used in simulation
du = zeros(2, num_particles) # array for storing velocity of particles, initialized to zero
u = 0.1 .+ 0.45 * rand(2, num_particles) # intitial position of particles
parameters = [5] # parameter for specified velocity field
t = 1.324 # randomly chosen point in time
@code_warntype rhs!(du, u, parameters, t) # testing type stability with a representative set of inputs defined above
@btime rhs!($du, $u, $parameters, $t) # checking allocations with a representative set of inputs defined above

# Section 3.1
num_particles = 100 # number of particles used in simulation
u = 0.1 .+ 0.45 * rand(2, num_particles) # intitial position of particles
tspan = (0, 5) # randomly chosen time span
dt = 1/512 # randomly chosen time step
parameters = [5] # parameter for specified velocity field
@code_warntype solve(ForwardEuler(), u, rhs!, tspan, dt, parameters) # testing type stability with a representative set of inputs defined above

# Section 3.2
num_particles = 100 # number of particles used in simulation
u = 0.1 .+ 0.45 * rand(2, num_particles) # intitial position of particles

dt = [1/16, 1/32, 1/64, 1/128, 1/256, 1/512, 1/1024] # timesteps to test solver functions with
Nsteps_fe = Vector{Int64}(undef, length(dt)) # empty vector for storing the number of rhs! function calls associated with the Forward Euler method for each timestep
error_fe = zeros(length(dt)) # empty array for storing error associated with Forward Euler method
Nsteps_em = Vector{Int64}(undef, length(dt)) # empty vector for storing the number of rhs! function calls associated with the Explicit Midpoint method for each timestep
error_em = zeros(length(dt)) # empty array for storing error associated with Explicit Midpoint method
for i = eachindex(dt)
    Nsteps_fe[i] = ceil(Int, 5 / dt[i]) + 1 # Calculating number of rhs! function calls associated with the Forward Euler method at the specified dt
    Nsteps_em[i] = ceil(Int, 5 / dt[i])*2 + 1 # Calculating number of rhs! function calls associated with the Explicit Midpoint method at the specified dt
    v7 = copy(u) # copying value of initial particle positions
    v8 = copy(u) # copying value of initial particle positions
    saved_solutions_fe3 = solve(ForwardEuler(), v7, rhs!, (0, 5), dt[i], [5]) # solving for particle positions using Forward Euler method with timespan of 5 sec and varying dt's under a specified velocity field
    saved_solutions_em3 = solve(ExplicitMidpoint(v8), v8, rhs!, (0, 5), dt[i], [5]) # solving for particle positions using Explicit Midpoint method with timespan of 5 sec and varying dt's under a specified velocity field
    error_fe[i] = norm(saved_solutions_fe3[3] - saved_solutions_fe3[1]) # Calculating error of Forward Euler method by taking the norm of the difference between the final and intitial particle positions
    error_em[i] = norm(saved_solutions_em3[3] - saved_solutions_em3[1]) # Calculating error of Explicit Midpoint method by taking the norm of the difference between the final and intitial particle positions
end

# Plotting Number of rhs! Evaluations vs Error for each solver method
p4 = plot()
plot!(p4, error_fe, Nsteps_fe, xaxis=:log, yaxis=:log, label = "Forward Euler", legend=:bottomleft)
scatter!(p4, error_fe, Nsteps_fe, label = false)
plot!(p4, error_em, Nsteps_em, xaxis=:log, yaxis=:log, label = "Explicit Midpoint")
scatter!(p4, error_em, Nsteps_em, label = false)
ylabel!(p4, "# of \"rhs!\" Evaluations")
title!(p4, "Number of \"rhs!\" Evaluations vs Error")
xlabel!(p4, "Error")
plot(p4)
png(p4, "Number of rhs! Evaluations vs Error")