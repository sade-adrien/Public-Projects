module Question6
using ..CantStop
using StatsBase
include("Question5.jl")
using .Question5
global nb_lancers = 0         #pas très beau mais le plus simple pour récupérer le nb de lancés au cours d'un tour


function policy_q6_H1(gs::game_state, adm_movement)
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
                    score += Question5.proba_amelioree(gs.players_position[active_player,mov]+1, mov)/4
                else
                    score += Question5.proba_amelioree(gs.players_position[active_player,mov], mov)
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
            proba = Question5.proba_amelioree(pos, i)
            if  proba != Inf && proba > 0.07
                return false
            end
        end
    end
    return true
end

function policy_q6_H1(gs::game_state)
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

    N_star = ceil(Question5.generalized_proba_legal_move(gs.open_columns)/(1-Question5.generalized_proba_legal_move(gs.open_columns)))

    if (nb_lancers >= N_star && is_opponent_far_from_winning(gs, other_player)) #we stop playing if the opponent is far from winning as soon as we reached N_star turns, without forgetting to reinitialize the number of turns
        global nb_lancers = 0
        return true
    end

    return false
end


end
