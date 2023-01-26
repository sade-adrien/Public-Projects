module Question5
using ..CantStop
using StatsBase
include("Question3.jl")
global nb_lancers = 0         #pas très beau mais le plus simple pour récupérer le nb de lancés au cours d'un tour

function proba_amelioree()
    return 0
end

function proba_amelioree(n_avancement::Int, column::Int)     #return the "improved probability" for each column in an array: proba of getting the associated number/the number of steps to close the column
    dices = [1, 2, 3, 4, 5, 6]
    p = 0
    global nb_cas = 0
    for d1 in dices
        for d2 in dices
            for d3 in dices
                for d4 in dices
                    comb1 = [d1+d2, d3+d4]
                    comb2 = [d1+d3, d2+d4]
                    comb3 = [d1+d4, d2+d3]
                    c = vcat(vcat(comb1, comb2), comb3)
                    if column in c
                        p += 1
                    end
                    nb_cas += 1
                end
            end
        end
    end
    p /= nb_cas
    if column<=7
        return p/(2*column-1-n_avancement)
    elseif column>7
        return p/(27-2*column-n_avancement)
    end
end


function prioritary_columns()     #return the list of the columns with the highest improved probability in the decreasing order
    return [i for i in 1:12][sortperm(proba_amelioree(), rev=true)]
end

function policy_q5_H1(gs::game_state, adm_movement)
    memory_adm_movement = adm_movement              #keeping this in memory, we might need it in the end
    if length(gs.open_columns) == 0
        global nb_lancers = 0                       #allows to reinitialize the number of throws event when there is a fail throw before
    end

    if length(gs.open_columns) < 3                  #if we haven't opened 3 columns yet, we play in the unique goal to open columns
        max_proba_amelioree, index = 0, 1
        for (i, movement) in enumerate(adm_movement)
            proba_movement = 0
            for (k, column) in enumerate(movement)
                if !(column in gs.open_columns)
                    if k==2 && movement[2] == movement[1]
                        proba_movement += proba_amelioree(gs.players_position[column]+1, column)/4
                    else
                        proba_movement += proba_amelioree(gs.players_position[column], column)
                    end
                end

                if max_proba_amelioree < proba_movement
                    max_proba_amelioree = proba_movement
                    index = i
                end
            end
        end

    else
        global nb_lancers += 1
        max_proba_amelioree, index = 0, 1
        for (i, movement) in enumerate(adm_movement)
            proba_movement = 0
            for (k, column) in enumerate(movement)
                if (column in gs.non_terminated_columns)
                    proba_movement += proba_amelioree(gs.players_position[column], column)               #Now we voluntarily sum the proba of every move in a tupple even if it's the same
                end
            end

            if max_proba_amelioree < proba_movement
                max_proba_amelioree = proba_movement
                index = i
            end
        end
    end

    return index #choose the first admissible movement offered
end

function policy_q5_H1(gs::game_state)
    if length(gs.open_columns) < 3              #we do not stop playing as long as we haven't opened 3 columns
        return false
    end

    END_OF_COLUMNS = [0 3 5 7 9 11 13 11 9 7 5 3]

    for c in gs.open_columns                     #we stop the turn as soon as there is one/3 column closed
        if gs.tentitative_movement[c] + gs.players_position[c] == END_OF_COLUMNS[c]
            return true
        end
    end

    N_star = ceil(generalized_proba_legal_move(gs.open_columns)/(1-generalized_proba_legal_move(gs.open_columns)))
    if (nb_lancers >= N_star)                  #we stop playing as soon as we reached N_star turns, without forgetting to reinitialize the number of turns
        global nb_lancers = 0
        return true
    end

    return false

end

end
