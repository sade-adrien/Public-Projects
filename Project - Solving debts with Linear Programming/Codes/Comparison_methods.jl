#This program create a random debts problem (by generating a group of persons and an associated debts matrix (float)),
#then finds the optimal continuous solution in terms of the total flow exchanged using the Gurobi solver (minimizing)
#and the optimal continuous solution in terms of number of exchanges using the Gurobi solver (minimizing)

using JuMP, Gurobi

trials = 1000
Max_persons = 7
Max_debt = 50

Nbr_persons = Max_persons #rand(2:Max_persons)
Final_transitions_matrix_FLOW = zeros(Nbr_persons,Nbr_persons)
Final_transitions_matrix_EXCHANGES = zeros(Nbr_persons,Nbr_persons)


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

function solving_debts_problem_flow(Debts_matrix,Nbr_persons,Final_transitions_matrix_FLOW)
    model = Model(Gurobi.Optimizer)

    @variable(model, Transitions_matrix[1:Nbr_persons,1:Nbr_persons] >= 0)
    @constraint(model, sum(Transitions_matrix-transpose(Transitions_matrix),dims=2) .== sum(Debts_matrix-transpose(Debts_matrix),dims=2))
    for i in 1:Nbr_persons
        @constraint(model, Transitions_matrix[i,i] == 0)
    end

    @objective(model, Min, sum(Transitions_matrix))

    JuMP.optimize!(model)

    for i in 1:Nbr_persons
        for j in 1:Nbr_persons
            Final_transitions_matrix_FLOW[i,j] = round(JuMP.value(Transitions_matrix[i,j])*100)/100
        end
    end
    return JuMP.objective_value(model)
    print(" ")                                         #for unknown reasons, needed to use the output later
end

function solving_debts_problem_exchanges(Debts_matrix,Nbr_persons,Final_transitions_matrix_EXCHANGES)
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
            Final_transitions_matrix_EXCHANGES[i,j] = round(JuMP.value(Transitions_matrix[i,j])*100)/100
        end
    end
    return JuMP.objective_value(model)
    print(" ")                                         #for unknown reasons, needed to use the output later
end



for i in 1:trials
    if i==1
        global compteur = 0
    end

    #Debts_matrix = [0 0 0 0 0 0 0 0; 0 0 0 0 0 0 0 0; 0 0 0 0 0 0 0 0; 0 0 0 0 0 0 0 0; 10 0 10 0 0 0 0 0; 0 5 0 5 0 0 0 0; 0 0 0 0 0 0 0 0; 0 0 0 0 0 0 10 0]
    global Debts_matrix = generate_random_debts(Nbr_persons)

    Final_flow1 = round(solving_debts_problem_flow(Debts_matrix,Nbr_persons,Final_transitions_matrix_FLOW)*100)/100
    Final_exchanges2 = solving_debts_problem_exchanges(Debts_matrix,Nbr_persons,Final_transitions_matrix_EXCHANGES)
    Final_flow2 = sum(Final_transitions_matrix_EXCHANGES)
    global Final_exchanges1 = 0
    for i in 1:Nbr_persons
        for j in 1:Nbr_persons
            if Final_transitions_matrix_FLOW[i,j] > 0
                global Final_exchanges1 = Final_exchanges1 + 1
            end
        end
    end


    println(" ")
    println("************** trial number ", i, " ****************")
    println("Debts matrix is: ", Debts_matrix)
    println("\n")
    println("**************** Optimal Flow Solution ********************")
    println("Optimal (flow) transitions matrix: ", Final_transitions_matrix_FLOW)
    println("The total flow is: ", Final_flow1)
    println("The total number of exchanges is: ", Final_exchanges1)
    println("\n")
    println("**************** Optimal Exchanges Solution ********************")
    println("Optimal (exchanges) transitions matrix: ", Final_transitions_matrix_EXCHANGES)
    println("The total flow is: ", Final_flow2)
    println("The total number of exchanges is: ", Final_exchanges2)
    println("\n")
    println("**************** NP/LP equivalence ? ********************")
    println((sum(Final_transitions_matrix_FLOW)==sum(Final_transitions_matrix_EXCHANGES)) || (Final_exchanges1 == Final_exchanges2))

    if (sum(Final_transitions_matrix_FLOW)==sum(Final_transitions_matrix_EXCHANGES)) || (Final_exchanges1 == Final_exchanges2)
        compteur = compteur + 1
    else
        break
    end


end

println("The equivalence was verified in ", float(compteur)/float(trials)*100, "% of the cases for ", Max_persons, " persons.")
