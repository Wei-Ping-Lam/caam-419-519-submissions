function rhs!(du, u, parameters, t) 
    C = parameters[1]
    N = size(u, 2)
    for i = 1:N
        du[1, i] = -sin(pi*u[2, i])*cos(pi*t/C)
        du[2, i] = sin(pi*u[1, i])*cos(pi*t/C)
    end
end