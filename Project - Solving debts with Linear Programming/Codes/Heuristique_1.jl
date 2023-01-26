#This program is a computation of the following heuristic to solve debts problems:
#-We create two lists orderded increasingly: one of the people in debts, and the other of the people who lent money
#-We pop the last person in debts (the most indebted) and make him reimburse his debt to the people who advanced the most
#Repeat while the lists are not empty

Max_persons = 5
Max_debt = 50

Nbr_persons = 4 #rand(2:Max_persons)
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

println("*****")
A = generate_random_debts(Nbr_persons)
println(A)
println(heuristic_1(A))
