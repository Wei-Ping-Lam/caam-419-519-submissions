struct ForwardEuler end

function solve(method::ForwardEuler, u0, rhs!, tspan, dt, parameters; num_saved_steps=1)
    Nsteps = ceil(Int, (tspan[2] - tspan[1]) / dt) # 2560
    dt = (tspan[2]-tspan[1]) / Nsteps # 1/512
    num_particles = size(u0, 2)
    du = Matrix{Float64}(undef, 2, num_particles)
    tiempo = LinRange(tspan[1], tspan[2], Nsteps+1) # (0, 5, 1/512)
    Pstep = floor(Int, (Nsteps+1) / (1+num_saved_steps)) # (2561/101)=25
    if Pstep == 0
        Pstep = 1
    end
    flag = Nsteps % Pstep == 0
    saved_solutions = Array{Matrix{Float64}}(undef, floor(Int, ((Nsteps+1)/Pstep)+2-flag))
    saved_solutions[1] = copy(u0)
    for i = eachindex(tiempo)
        rhs!(du, u0, parameters, tiempo[i])
        @. u0 = u0 + dt * du
        if i % Pstep == 0
            saved_solutions[Int(i/Pstep) + 1] = copy(u0)
        end
    end
    if !flag
        saved_solutions[floor(Int, ((Nsteps+1)/Pstep)+2)] = copy(u0)
    end
    return saved_solutions
end

struct ExplicitMidpoint{T}
    u_tmp::T
    # This is a custom constructor which initializes "u_tmp" based on an initial condition "u"
    ExplicitMidpoint(u) = new{typeof(u)}(similar(u))
end

function solve(method::ExplicitMidpoint, u0, rhs!, tspan, dt, parameters; num_saved_steps=1)
    Nsteps = ceil(Int, (tspan[2] - tspan[1]) / dt)
    dt = (tspan[2]-tspan[1]) / Nsteps
    num_particles = size(u0, 2)
    du = Matrix{Float64}(undef, 2, num_particles)
    tiempo = LinRange(tspan[1], tspan[2], Nsteps+1)
    Pstep = floor(Int, (Nsteps+1) / (1+num_saved_steps))
    if Pstep == 0
        Pstep = 1
    end
    flag = Nsteps % Pstep == 0
    saved_solutions = Array{Matrix{Float64}}(undef, floor(Int, ((Nsteps+1)/Pstep)+2-flag))
    saved_solutions[1] = copy(u0)
    for i = eachindex(tiempo)
        rhs!(du, u0, parameters, tiempo[i])
        @. method.u_tmp = u0 .+ 0.5*dt*du
        rhs!(du, method.u_tmp, parameters, tiempo[i] + 0.5*dt)
        @. u0 = u0 + dt*du
        if i % Pstep == 0
            saved_solutions[Int(i/Pstep) + 1] = copy(u0)
        end
    end
    if !flag
        saved_solutions[floor(Int, ((Nsteps+1)/Pstep)+2)] = copy(u0)
    end
    return saved_solutions
end