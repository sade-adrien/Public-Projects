module Policies_42 #Replace 42 by your groupe number
using ..CantStop # to access function exported from CantStop
using StatsBase

############################################################################################################################################################################
"""
First, some features we'll be needing
"""
global nb_lancers = 0
function proba_legal_move(i, j, k)
    dices = [1, 2, 3, 4, 5, 6]
    p = 0
    nb_cas = 0
    for d1 in dices
        for d2 in dices
            for d3 in dices
                for d4 in dices
                    comb1 = [d1+d2, d3+d4]
                    comb2 = [d1+d3, d2+d4]
                    comb3 = [d1+d4, d2+d3]
                    c = vcat(vcat(comb1, comb2), comb3)
                    if i in c || j in c || k in c
                        p += 1
                    end
                    nb_cas += 1
                end
            end
        end
    end
    return p/nb_cas
end
function generalized_proba_legal_move(open_columns)
    dices = [1, 2, 3, 4, 5, 6]
    p = 0
    nb_cas = 0
    for d1 in dices
        for d2 in dices
            for d3 in dices
                for d4 in dices
                    comb1 = [d1+d2, d3+d4]
                    comb2 = [d1+d3, d2+d4]
                    comb3 = [d1+d4, d2+d3]
                    c = vcat(vcat(comb1, comb2), comb3)
                    for col in open_columns
                        if col in c
                            p += 1
                            break
                        end
                    end
                    nb_cas += 1
                end
            end
        end
    end
    return p/nb_cas
end
function proba_amelioree()
    return 0
end
function proba_amelioree(n_avancement::Int, column::Int)     #return the "improved probability" for each column in an array: proba of getting the associated number/the number of steps left to close the column
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
function is_opponent_far_from_winning(gs::game_state, other_player::Int)
    col_closed = 0
    END_OF_COLUMNS = [0 3 5 7 9 11 13 11 9 7 5 3]
    for (c, p) in enumerate(END_OF_COLUMNS)
        if c == 1
            continue
        end
        if p == gs.players_position[other_player,:][c]
            col_closed += 1
        end
    end

    if col_closed >= 2
        for (i, pos) in enumerate(gs.players_position[other_player,:])
            proba = proba_amelioree(pos, i)
            if  proba != Inf && proba > 0.07
                return false
            end
        end
    end
    return true
end
############################################################################################################################################################################


function policy_q1(gs::game_state, adm_movement)
    return 1 #choose the first admissible movement offered
end
function policy_q1(gs::game_state)
    return (sum(gs.tentitative_movement) > 2)
end

#Question 2
function policy_q2(gs::game_state, adm_movement)
    return 1
end
function policy_q2(gs::game_state)
    return (sum(gs.tentitative_movement) > 2)
end

#Question 3
function policy_q3(gs::game_state, adm_movement)
    return 1
end
function policy_q3(gs::game_state)
    return (sum(gs.tentitative_movement) > 2)
end

#Question 4
function policy_q4(gs::game_state, adm_movement)
    return 1
end
function policy_q4(gs::game_state)
    return (sum(gs.tentitative_movement) > 2)
end

#Question 5
function policy_q5(gs::game_state, adm_movement)
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
                    proba_movement += proba_amelioree(gs.players_position[column], column)               #Now we sum the proba of every move in a tupple even if it's the same
                end
            end

            if max_proba_amelioree < proba_movement
                max_proba_amelioree = proba_movement
                index = i
            end
        end
    end

    return index
end
function policy_q5(gs::game_state)
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

#Question 6
function policy_q6_old(gs::game_state, adm_movement)
    active_player = gs.active_player # entier qui donne l'id du joueur
    other_player = 1
    if active_player==1
        other_player = 2
    end

    if length(gs.open_columns) > 2
        global nb_lancers += 1
    elseif length(gs.open_columns) == 0
        global nb_lancers = 0
    end
    scores = [] # liste des intérets de chaque mouvement, sans prendre en compte l'adversaire
    is_opponent_here = [] # liste qui nous dit pour chaque mouvement si on sera confronté à l'adversaire
    for movs in adm_movement
        score = 0
        columns_opponent = 0
        for (k, mov) in enumerate(movs)
            # ici on met à jour le score qui nous dit si la colonne est bien ou pas
            if !(mov in gs.open_columns)
                if k==2 && movs[2] == movs[1]
                    score += proba_amelioree(gs.players_position[active_player,mov]+1, mov)/4
                else
                    score += proba_amelioree(gs.players_position[active_player,mov], mov)
                end
            end

            # on ajoute de 1 columns_opponent si l'autre joueur est sur cette colonne
            if gs.players_position[other_player, mov]>0
                columns_opponent += 1
            end

        end
        columns_opponent = columns_opponent/length(movs)

        push!(scores, score)
        push!(is_opponent_here, columns_opponent)

    end
    indices_interest_adm_mov = sortperm(scores, rev=true)
    find_interesting_mov = false
    i = 1

    while !find_interesting_mov && i<=length(scores)
        find_interesting_mov = (is_opponent_here[i]==0)
        i+=1
    end
    if find_interesting_mov
        return i-1
    else
        return indices_interest_adm_mov[1]
    end
end
function policy_q6_old(gs::game_state)
    active_player = gs.active_player # entier qui donne l'id du joueur
    other_player = 1
    if active_player==1
        other_player = 2
    end

    if length(gs.open_columns) < 3              #we do not stop playing as long as we haven't opened 3 columns
        return false
    end

    END_OF_COLUMNS = [0 3 5 7 9 11 13 11 9 7 5 3]

    for c in gs.open_columns                     #we stop the turn as soon as there is one/3 column closed
        if gs.tentitative_movement[c] + gs.players_position[active_player, c] == END_OF_COLUMNS[c]
            return true
        end
    end

    N_star = ceil(generalized_proba_legal_move(gs.open_columns)/(1-generalized_proba_legal_move(gs.open_columns)))

    if (nb_lancers >= N_star && is_opponent_far_from_winning(gs, other_player)) #we stop playing if the opponent is far from winning as soon as we reached N_star turns, without forgetting to reinitialize the number of turns
        global nb_lancers = 0
        return true
    end

    return false
end

function policy_q6(gs::game_state, adm_movement)
    active_player = gs.active_player # entier qui donne l'id du joueur
    other_player = 1
    if active_player==1
        other_player = 2
    end

    if length(gs.open_columns) > 2
        global nb_lancers += 1
    elseif length(gs.open_columns) == 0
        global nb_lancers = 0
    end
    scores = [] # liste des intérets de chaque mouvement, sans prendre en compte l'adversaire
    for movs in adm_movement
        score = 0
        for (k, mov) in enumerate(movs)
            # ici on met à jour le score qui nous dit si la colonne est bien ou pas
            if !(mov in gs.open_columns)
                if k==2 && movs[2] == movs[1]
                    score += proba_amelioree(gs.players_position[active_player,mov]+1, mov)/4
                else
                    score += proba_amelioree(gs.players_position[active_player,mov], mov)
                end
            end
        end
        push!(scores, score)
    end
    indices_interest_adm_mov = sortperm(scores, rev=true)

    return indices_interest_adm_mov[1]
end
function policy_q6(gs::game_state)
    active_player = gs.active_player # entier qui donne l'id du joueur
    other_player = 1
    if active_player==1
        other_player = 2
    end

    if length(gs.open_columns) < 3              #we do not stop playing as long as we haven't opened 3 columns
        return false
    end

    END_OF_COLUMNS = [0 3 5 7 9 11 13 11 9 7 5 3]
    for c in gs.open_columns                     #we stop the turn as soon as there is one/3 column closed
        if gs.tentitative_movement[c] + gs.players_position[active_player, c] == END_OF_COLUMNS[c]
            return true
        end
    end

    N_star = ceil(generalized_proba_legal_move(gs.open_columns)/(1-generalized_proba_legal_move(gs.open_columns)))
    N_star = N_star - 3      #New N_star

    if (nb_lancers >= N_star && is_opponent_far_from_winning(gs, other_player)) #we stop playing if the opponent is far from winning as soon as we reached N_star turns, without forgetting to reinitialize the number of turns
        global nb_lancers = 0
        return true
    end

    return false
end

#Question 7
function policy_q7(gs::game_state, adm_movement)
    return policy_q8(gs::game_state, adm_movement)
end
function policy_q7(gs::game_state)
    return policy_q8(gs::game_state)
end

#Question 8
function policy_q8(gs::game_state, adm_movement)
    active_player = gs.active_player # entier qui donne l'id du joueur
    other_players = []
    for i in 1:gs.nb_player
        if i != active_player
            push!(other_players, i)
        end
    end

    if length(gs.open_columns) > 2
        global nb_lancers += 1
    elseif length(gs.open_columns) == 0
        global nb_lancers = 0
    end
    scores = [] # liste des intérets de chaque mouvement, sans prendre en compte l'adversaire
    for movs in adm_movement
        score = 0
        for (k, mov) in enumerate(movs)
            # ici on met à jour le score qui nous dit si la colonne est bien ou pas
            if !(mov in gs.open_columns)
                if k==2 && movs[2] == movs[1]
                    score += proba_amelioree(gs.players_position[active_player,mov]+1, mov)/4
                else
                    score += proba_amelioree(gs.players_position[active_player,mov], mov)
                end
            end
        end
        push!(scores, score)
    end
    indices_interest_adm_mov = sortperm(scores, rev=true)
    return indices_interest_adm_mov[1]
end
function policy_q8(gs::game_state)
    active_player = gs.active_player # entier qui donne l'id du joueur actif
    other_players = []
    for i in 1:gs.nb_player
        if i != active_player
            push!(other_players, i)
        end
    end

    if length(gs.open_columns) < 3              #we do not stop playing as long as we haven't opened 3 columns
        return false
    end

    END_OF_COLUMNS = [0 3 5 7 9 11 13 11 9 7 5 3]

    for c in gs.open_columns                     #we stop the turn as soon as there is one/3 column closed
        if gs.tentitative_movement[c] + gs.players_position[active_player, c] == END_OF_COLUMNS[c]
            return true
        end
    end

    N_star = ceil(generalized_proba_legal_move(gs.open_columns)/(1-generalized_proba_legal_move(gs.open_columns)))
    N_star = N_star - 3

    are_opponents_far_from_winning = true
    for other_player in other_players
        are_opponents_far_from_winning = is_opponent_far_from_winning(gs, other_player)
        if !are_opponents_far_from_winning
            break
        end
    end

    if (nb_lancers >= N_star && are_opponents_far_from_winning) #we stop playing if all opponents are far from winning as soon as we reached N_star turns, without forgetting to reinitialize the number of turns
        global nb_lancers = 0
        return true
    end

    return false
end

end #end of module
