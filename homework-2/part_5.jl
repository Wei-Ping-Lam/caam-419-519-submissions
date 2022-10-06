using Plots
using BenchmarkTools

include("part_1.jl")
include("part_2.jl")

# Section 1.1
num_particles = 100
u = 0.1 .+ 0.45 * rand(2, num_particles)
v3 = copy(u)
saved_solutions_fe1 = solve(ForwardEuler(), v3, rhs!, (0, 1), 1/512, [5])
v4 = copy(u)
saved_solutions_em1 = solve(ExplicitMidpoint(v4), v4, rhs!, (0, 1), 1/512, [5])

p1 = plot()
scatter!(p1, saved_solutions_fe1[1][1,:], saved_solutions_fe1[1][2,:], xlims=(-1, 1), ylims=(-1, 1), label = "t = 0")
scatter!(p1, saved_solutions_fe1[3][1,:], saved_solutions_fe1[3][2,:], xlims=(-1, 1), ylims=(-1, 1), label = "t = 1")
title!(p1, "Forward Euler Initial vs Final Positions")
plot(p1)
#png(p1, "FE_1_second_solution")

p2 = plot()
scatter!(p2, saved_solutions_em1[1][1,:], saved_solutions_em1[1][2,:], xlims=(-1, 1), ylims=(-1, 1), label = "t = 0")
scatter!(p2, saved_solutions_em1[3][1,:], saved_solutions_em1[3][2,:], xlims=(-1, 1), ylims=(-1, 1), label = "t = 1")
title!(p2, "Explicit Midpoint Initial vs Final Positions")
plot(p2)
#png(p2, "EM_1_second_solution")

# Section 1.2
num_particles = 100
u = 0.1 .+ 0.45 * rand(2, num_particles)
dt = [1/16, 1/32, 1/64, 1/128, 1/256, 1/512, 1/1024]
error_fe = zeros(length(dt))
error_em = zeros(length(dt))
for i = eachindex(dt)
    v5 = copy(u)
    v6 = copy(u)
    saved_solutions_fe2 = solve(ForwardEuler(), v5, rhs!, (0, 5), dt[i], [5])
    saved_solutions_em2 = solve(ExplicitMidpoint(v6), v6, rhs!, (0, 5), dt[i], [5])
    error_fe[i] = norm(saved_solutions_fe2[3] - saved_solutions_fe2[1])
    error_em[i] = norm(saved_solutions_em2[3] - saved_solutions_em2[1])
end

p3 = plot()
plot!(p3, dt, error_fe, xaxis=:log, yaxis=:log, label = "Forward Euler", legend=:bottomright)
scatter!(p3, dt, error_fe, label = false)
plot!(p3, dt, error_em, xaxis=:log, yaxis=:log, label = "Explicit Midpoint")
scatter!(p3, dt, error_em, label = false)
xlabel!(p3, "Timestep Size")
title!(p3, "Error vs Timestep Size")
ylabel!(p3, "Error")
plot(p3)
#png(p3, "Error vs Timestep Size")

# Section 2.1 & 2.2
num_particles = 100
du = zeros(2, num_particles)
u = 0.1 .+ 0.45 * rand(2, num_particles)
parameters = [5]
t = 1.324
@code_warntype rhs!(du, u, parameters, t)
@btime rhs!($du, $u, $parameters, $t)

# Section 3.1
num_particles = 100
u = 0.1 .+ 0.45 * rand(2, num_particles)
tspan = (0, 5)
dt = 1/512
parameters = [5]
@code_warntype solve(ForwardEuler(), u, rhs!, tspan, dt, parameters)

# Section 3.2
num_particles = 100
u = 0.1 .+ 0.45 * rand(2, num_particles)

dt = [1/16, 1/32, 1/64, 1/128, 1/256, 1/512, 1/1024]
Nsteps_fe = Vector{Int64}(undef, length(dt))
error_fe = zeros(length(dt))
Nsteps_em = Vector{Int64}(undef, length(dt))
error_em = zeros(length(dt))
for i = eachindex(dt)
    Nsteps_fe[i] = ceil(Int, 5 / dt[i])
    Nsteps_em[i] = ceil(Int, 5 / dt[i])*2
    v7 = copy(u)
    v8 = copy(u)
    saved_solutions_fe3 = solve(ForwardEuler(), v7, rhs!, (0, 5), dt[i], [5])
    saved_solutions_em3 = solve(ExplicitMidpoint(v8), v8, rhs!, (0, 5), dt[i], [5])
    error_fe[i] += norm(saved_solutions_fe3[3] - saved_solutions_fe3[1])
    error_em[i] += norm(saved_solutions_em3[3] - saved_solutions_em3[1])
end

p4 = plot()
plot!(p4, Nsteps_fe, error_fe, xaxis=:log, yaxis=:log, label = "Forward Euler", legend=:topright)
scatter!(p4, Nsteps_fe, error_fe, label = false)
plot!(p4, Nsteps_em, error_em, xaxis=:log, yaxis=:log, label = "Explicit Midpoint")
scatter!(p4, Nsteps_em, error_em, label = false)
xlabel!(p4, "# of \"rhs!\" Evaluations")
title!(p4, "Error vs Number of \"rhs!\" Evaluations")
ylabel!(p4, "Error")
plot(p4)
#png(p4, "Error vs Number of rhs! Evaluations")