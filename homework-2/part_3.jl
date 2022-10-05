using Plots
using LinearAlgebra

include("part_1.jl")
include("part_2.jl")

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
    v1 = copy(u)
    v2 = copy(u)
    saved_solutions_fe = solve(ForwardEuler(), v1, rhs!, (0, 5), dt[i], [5])
    saved_solutions_em = solve(ExplicitMidpoint(v2), v2, rhs!, (0, 5), dt[i], [5])
    error_fe[i] += norm(saved_solutions_fe[3] - saved_solutions_fe[1])
    error_em[i] += norm(saved_solutions_em[3] - saved_solutions_em[1])
end

p1 = plot()
plot!(p1, dt, error_fe, xaxis=:log, yaxis=:log, label = "Forward Euler", legend=:bottomright)
scatter!(p1, dt, error_fe, label = false)
plot!(p1, dt, error_em, xaxis=:log, yaxis=:log, label = "Explicit Midpoint")
scatter!(p1, dt, error_em, label = false)
xlabel!(p1, "Timestep Size")
title!(p1, "Error vs Timestep Size")
ylabel!(p1, "Error")
png(p1, "Error vs Timestep Size")

p2 = plot()
plot!(p2, Nsteps_fe, error_fe, xaxis=:log, yaxis=:log, label = "Forward Euler", legend=:topright)
scatter!(p2, Nsteps_fe, error_fe, label = false)
plot!(p2, Nsteps_em, error_em, xaxis=:log, yaxis=:log, label = "Explicit Midpoint")
scatter!(p2, Nsteps_em, error_em, label = false)
xlabel!(p2, "# of \"rhs!\" Evaluations")
title!(p2, "Error vs Number of \"rhs!\" Evaluations")
ylabel!(p2, "Error")
png(p2, "Error vs Number of rhs! Evaluations")

v = copy(u)
saved_solutions = solve(ForwardEuler(), v, rhs!, (0, 10), 1/512, [5], num_saved_steps=100)

x = [-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -7/9, -7/9, -7/9, -7/9, -7/9, -7/9, -7/9, -7/9, -7/9, -7/9, -5/9, -5/9, -5/9, -5/9, -5/9, -5/9, -5/9, -5/9, -5/9, -5/9, -3/9, -3/9, -3/9, -3/9, -3/9, -3/9, -3/9, -3/9, -3/9, -3/9, -1/9, -1/9, -1/9, -1/9, -1/9, -1/9, -1/9, -1/9, -1/9, -1/9, 1/9, 1/9, 1/9, 1/9, 1/9, 1/9, 1/9, 1/9, 1/9, 1/9, 3/9, 3/9, 3/9, 3/9, 3/9, 3/9, 3/9, 3/9, 3/9, 3/9, 5/9, 5/9, 5/9, 5/9, 5/9, 5/9, 5/9, 5/9, 5/9, 5/9, 7/9, 7/9, 7/9, 7/9, 7/9, 7/9, 7/9, 7/9, 7/9, 7/9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0]
y = [-1.0, -7/9, -5/9, -3/9, -1/9, 1/9, 3/9, 5/9, 7/9, 1.0, -1.0, -7/9, -5/9, -3/9, -1/9, 1/9, 3/9, 5/9, 7/9, 1.0, -1.0, -7/9, -5/9, -3/9, -1/9, 1/9, 3/9, 5/9, 7/9, 1.0, -1.0, -7/9, -5/9, -3/9, -1/9, 1/9, 3/9, 5/9, 7/9, 1.0, -1.0, -7/9, -5/9, -3/9, -1/9, 1/9, 3/9, 5/9, 7/9, 1.0, -1.0, -7/9, -5/9, -3/9, -1/9, 1/9, 3/9, 5/9, 7/9, 1.0, -1.0, -7/9, -5/9, -3/9, -1/9, 1/9, 3/9, 5/9, 7/9, 1.0, -1.0, -7/9, -5/9, -3/9, -1/9, 1/9, 3/9, 5/9, 7/9, 1.0, -1.0, -7/9, -5/9, -3/9, -1/9, 1/9, 3/9, 5/9, 7/9, 1.0, -1.0, -7/9, -5/9, -3/9, -1/9, 1/9, 3/9, 5/9, 7/9, 1.0]
vx = Vector{Float64}(undef, length(x))
vy = Vector{Float64}(undef, length(y))

Nsteps = ceil(Int, 10 / (1/512))
tiempo = LinRange(0, 10, Nsteps+1)
Pstep = floor(Int, (Nsteps+1) / 101)
if Pstep == 0
    Pstep = 1
end
flag = Nsteps % Pstep == 0
time = Array{Float64}(undef, floor(Int, ((Nsteps+1)/Pstep)+2-flag))
time[1] = tiempo[1]
for i = eachindex(tiempo)
    if i % Pstep == 0
        time[Int(i/Pstep) + 1] = tiempo[i]
    end
end
if !flag
    time[floor(Int, ((Nsteps+1)/Pstep)+2)] = tiempo[Nsteps]
end

anim = @animate for i = eachindex(saved_solutions)
    scatter(saved_solutions[i][1,:], saved_solutions[i][2,:], legend = false, xlims=(-1, 1), ylims=(-1, 1))
    for j = eachindex(x)
        vx[j] = -sin(pi*y[j])*cos(pi*time[i]/5)/10
        vy[j] = sin(pi*x[j])*cos(pi*time[i]/5)/10
    end
    quiver!(x,y,quiver=(vx,vy))
    t = round(time[i], digits = 1)
    title!("Time t = $t")
end
gif(anim)

v = copy(u)
saved_solutions = solve(ExplicitMidpoint(v), v, rhs!, (0, 10), 1/512, [5], num_saved_steps=100)

anim = @animate for i = eachindex(saved_solutions)
    scatter(saved_solutions[i][1,:], saved_solutions[i][2,:], legend = false, xlims=(-1, 1), ylims=(-1, 1))
    for j = eachindex(x)
        vx[j] = -sin(pi*y[j])*cos(pi*time[i]/5)/10
        vy[j] = sin(pi*x[j])*cos(pi*time[i]/5)/10
    end
    quiver!(x,y,quiver=(vx,vy))
    t = round(time[i], digits = 1)
    title!("Time t = $t")
end
gif(anim)