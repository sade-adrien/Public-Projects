module Question7
using ..CantStop
using StatsBase
include("Question8.jl")
include("Question5.jl")
using .Question8
using .Question5

function policy_q7_H1(gs::game_state, adm_movement)

    active_player = gs.active_player # entier qui donne l'id du joueur
    other_players = []
    for i in 1:gs.nb_player
        if i != active_player
            push!(other_players, i)
        end
    end

    strat = true
    for other_player in other_players
        strat = strat && Question8.is_opponent_far_from_winning(gs, other_player, 0.07) #si ça vaut true
    end

    if strat
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
                for other_player in other_players
                    if gs.players_position[other_player, mov]>0
                        columns_opponent += 1
                    end
                end

            end

            push!(scores, score)
            push!(is_opponent_here, columns_opponent)

        end

        columns_open_by_me = []

        for i in gs.players_position[active_player,:]
            push!(columns_open_by_me, i>0)
        end

        indices_interest_adm_mov = sortperm(scores, rev=true)
        find_interesting_mov = false
        for n in 1:gs.nb_player
        i = 1
            while !find_interesting_mov && i<=length(indices_interest_adm_mov)
                move_already_opened = true
                for l in indices_interest_adm_mov[i]
                    move_already_opened = move_already_opened && columns_open_by_me[l]
                end
                find_interesting_mov = !move_already_opened
                i+=1
            end
            if find_interesting_mov
                return i-1
            end
        end
        return indices_interest_adm_mov[1]       #worst case scenario
    end
    return Question8.policy_q8_H1(gs, adm_movement)
end

function policy_q7_H1(gs::game_state)
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

    N_star = ceil(Question5.generalized_proba_legal_move(gs.open_columns)/(1-Question5.generalized_proba_legal_move(gs.open_columns)))

    are_opponents_far_from_winning = true
    for other_player in other_players
        are_opponents_far_from_winning = Question8.is_opponent_far_from_winning(gs, other_player)
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


end
