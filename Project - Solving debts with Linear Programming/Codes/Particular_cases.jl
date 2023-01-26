#This program is creating particular exemples (under different functions) and solve those cases
#with the LP modelization (optimal solutions) and with the heuristic established before
using JuMP, Gurobi

Max_debt = 50
Nbr_persons = 6

############################################ creating debts ##########################################################

function case_circular_debts(Nbr_persons)   #circular debts: A owes to B, B owes to C, C owes to A (only)
    Debts_matrix = rand(Float64, Nbr_persons, Nbr_persons)*Max_debt*100
    for i in 1:Nbr_persons
        for j in 1:Nbr_persons
            if j==mod(i,Nbr_persons)+1
                Debts_matrix[i,j] = round(Debts_matrix[i,j])
            else
                Debts_matrix[i,j] = 0
            end
        end
    end
    Debts_matrix = Debts_matrix/100
    return Debts_matrix
end

function case_forgot_my_wallet(Nbr_persons, Nbr_wallets_forgotten)   #some people have forgotten their wallets and can't pay, they are in debts without advancing money ever: the last columns are =0
    Debts_matrix = rand(Float64, Nbr_persons, Nbr_persons)*Max_debt*100
    for i in 1:Nbr_persons
        for j in 1:Nbr_persons
            if i==j || j > Nbr_persons - Nbr_wallets_forgotten
                Debts_matrix[i,j] = 0
            else
                Debts_matrix[i,j] = round(Debts_matrix[i,j])
            end
        end
    end
    Debts_matrix = Debts_matrix/100
    return Debts_matrix
end

function case_tandem(Nbr_persons)            #in a group even, people pair up to manage their finances (for exemple, they alternativaly pay for each other as to avoid taking their wallet every night)
    if mod(Nbr_persons,2) == 1
        print("Odd group")
        return 0
    end

    Debts_matrix = zeros(Nbr_persons,Nbr_persons)
    for i in 1:Nbr_persons
        if mod(i,2) == 1
            Debts_matrix[i,i+1] = round(first(rand(Float64,1)*Max_debt*100))
        else
            Debts_matrix[i,i-1] = round(first(rand(Float64,1)*Max_debt*100))
        end
    end
    Debts_matrix = Debts_matrix/100
    return Debts_matrix
end
############################################ solving ##########################################################

function solving_debts_problem_flow(Debts_matrix)  #We admit that for our problem (N is small enough) to consider that sol_exchanges=sol_flows
    Nbr_persons = size(Debts_matrix)[1]
    Final_transitions_matrix = zeros(Nbr_persons,Nbr_persons)
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
            Final_transitions_matrix[i,j] = round(JuMP.value(Transitions_matrix[i,j])*100)/100
        end
    end
    return Final_transitions_matrix
    print(" ")                                         #for unknown reasons, needed to use the output later
end

function heuristic_1(Debts_matrix)
    n = size(Debts_matrix)[1]
    Transitions_matrix = zeros(n,n)
    vector_of_algebraic_debts = zeros(n,1)

    for i in 1:n
        for j in 1:n
            vector_of_algebraic_debts[i] += Debts_matrix[i,j]    #debts i owns on the i-the row
            vector_of_algebraic_debts[i] -= Debts_matrix[j,i]    #debts i is owned on the i-th column
        end
    end

    Indebteds = Array{Int64,1}(undef,0)
    Lenders = Array{Int64,1}(undef,0)

    for i in 1:n
        if vector_of_algebraic_debts[i] > 0
            push!(Indebteds,i)
        else
            push!(Lenders,i)
        end
    end

    Indebteds = sort(Indebteds)
    Lenders = sort(Lenders)


    while length(Indebteds) > 0
        current_indebted = pop!(Indebteds)

        while vector_of_algebraic_debts[current_indebted] > 0 && length(Lenders) > 0
            current_lender = pop!(Lenders)

            transaction = min(vector_of_algebraic_debts[current_indebted],abs(vector_of_algebraic_debts[current_lender]))
            Transitions_matrix[current_indebted,current_lender] = transaction
            vector_of_algebraic_debts[current_indebted] -= transaction
            vector_of_algebraic_debts[current_lender] += transaction

            if vector_of_algebraic_debts[current_lender] < 0
                push!(Lenders, current_lender)
            end
        end
    end

    return Transitions_matrix
end


############################################ main ##########################################################
function nbr_exchanges(Transitions_matrix)
    epsilon = 1e-4
    n = 0
    for i in 1:size(Transitions_matrix)[1]
        for j in 1:size(Transitions_matrix)[2]
            if Transitions_matrix[i,j] > epsilon
                n += 1
            end
        end
    end
    return n
end



A = case_tandem(Nbr_persons)
B = solving_debts_problem_flow(A)
C = heuristic_1(A)

println(A)
#println(nbr_exchanges(B))
#println(nbr_exchanges(C))
