#This program create a random debts problem (by generating a group of persons and an associated debts matrix (float)),
#then finds the optimal continuous solution in terms of number of exchanges using the Gurobi solver (minimizing)
using JuMP, Gurobi

Max_persons = 5
Max_debt = 50

Nbr_persons = 8 #rand(2:Max_persons)
Final_transitions_matrix = zeros(Nbr_persons,Nbr_persons)

function generate_random_debts(Nbr_persons)
    Debts_matrix = rand(Float64, Nbr_persons, Nbr_persons)*Max_debt*100
    for i in 1:Nbr_persons
        for j in 1:Nbr_persons
            if i==j
                Debts_matrix[i,j] = 0
            else
                Debts_matrix[i,j] = round(Debts_matrix[i,j])
            end
        end
    end
    Debts_matrix = Debts_matrix/100
    return Debts_matrix
end

function solving_debts_problem_exchanges(Debts_matrix,Nbr_persons,Final_transitions_matrix)
    model = Model(Gurobi.Optimizer)

    @variable(model, Transitions_matrix[1:Nbr_persons,1:Nbr_persons] >= 0)
    @variable(model, Exchanges_binary_matrix[1:Nbr_persons,1:Nbr_persons], Bin)

    @constraint(model, sum(Transitions_matrix-transpose(Transitions_matrix),dims=2) .== sum(Debts_matrix-transpose(Debts_matrix),dims=2))
    for i in 1:Nbr_persons
        @constraint(model, Transitions_matrix[i,i] == 0)
    end
    for i in 1:Nbr_persons
        for j in 1:Nbr_persons
            @constraint(model, Exchanges_binary_matrix[i,j] >= Transitions_matrix[i,j]/sum(Debts_matrix))
        end
    end

    @objective(model, Min, sum(Exchanges_binary_matrix))

    JuMP.optimize!(model)

    for i in 1:Nbr_persons
        for j in 1:Nbr_persons
            Final_transitions_matrix[i,j] = round(JuMP.value(Transitions_matrix[i,j])*100)/100
        end
    end
    return JuMP.objective_value(model)
    print(" ")                                         #for unknown reasons, needed to use the output later
end

Debts_matrix = generate_random_debts(Nbr_persons)
Final_exchanges = solving_debts_problem_exchanges(Debts_matrix,Nbr_persons,Final_transitions_matrix)

println("Debts matrix is: ", Debts_matrix)
println("Optimal (exchanges) transitions matrix: ", Final_transitions_matrix)
println("The total number of exchanges is: ", Final_exchanges)
println("\n")
