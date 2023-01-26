struct Position
    cg::Int # position du current gain (entre 1 et Gmax+1 inclus)
    tg::Int # position du tentative gain depuis le current gain (entre 1 et Gmax+2-cg inclus)
end

struct State
    pos::Position
    gain::Int
end

function states(Gmax)
    """
    INPUT : Gmax = objective gain (int)
    OUTPUT : X = list of lists of floats that gives all the existing states.
    """
    X = Array{Int}[]
    for i in 0:Gmax
        Y = Float64[]
        for j in i:Gmax
            push!(Y, j)
        end
        push!(X, Y)
    end
    return X
end

function all_states(Gmax::Int)
    """
    INPUT : Gmax = objective gain (int)
    OUTPUT : X = list of lists of State that gives all the existing states.
    """
    X = []
    for i in 1:Gmax+1
        for j in 1:Gmax+1-i+1
            push!(X, State(Position(i, j), i+j-2))
        end
    end
    return X
end

function initVt(Gmax)
    """
    INPUT : Gmax = objective gain (int)
    OUTPUT : Vt = list of lists of floats that initialises Vt to +inf for all the existing states.
    """
    Vt = Array{Float64}[]
    for i in 0:Gmax
        Y = Float64[]
        for j in i:Gmax
            push!(Y, Inf)
        end
        push!(Vt, Y)
    end
    return Vt
end

function initPit(Gmax)
    """
    INPUT : Gmax = objective gain (int)
    OUTPUT : Pi_t = list of lists of floats that initialises pi_t to -1 for all the existing states.
    """
    Pi_t = Array{Int}[]
    for i in 0:Gmax
        Y = Float64[]
        for j in i:Gmax
            push!(Y, -1)
        end
        push!(Pi_t, Y)
    end
    return Pi_t
end

function accessibles_states(list_next_states, Gmax)
    """
    INPUTS : list_next_states = a list of all the accessibles states at the next iteration (State)
            Gmax = objective gain (int)
    OUTPUT : list_states = a list of all the states that can lead to the states given in list_next_states (State)
    """
    list_states = []
    for s in list_next_states
        x = s.pos
        #println("dans accessibles_states, on a ",x.cg, " ", x.tg)
        if x.tg == 1 # si on arrive au début d'une ligne, 
            # alors on peut venir de l'état en question
            push!(list_states, s)
            # on peut aussi venir de cette colonne et les états accessibles auront notre gain
            for i in 1:(x.cg-1)
                push!(list_states, State(Position(i, x.cg-i+1), s.gain))
            end
            # on peut aussi venir de n'importe où sur notre ligne
            for i in 2:(Gmax+1-x.cg)
                push!(list_states, State(Position(x.cg, i), s.gain+i-1))
            end
        else
            # sinon, on vient forcément de la gauche
            push!(list_states, State(Position(x.cg, x.tg-1), s.gain-1))
        end
    end
    #println("les états qui pouvaient donner ce résultat sont ", list_states)
    return list_states
end

function cout_trainsition_et_proba(x::State, y::State, a, p)
    """
    INPUTS : x un état, y l'état d'après
             a la politique : 0 correspond à s'arrêter, 1 à rejouer
             p est la proba de réussir un lancer
    OUTPUTS : P = proba de passer de x à y 
              c = coût pour passer de x à Y

    """

    if x.pos.tg == 1 # si on part du début d'une ligne
        if y.pos.tg == 1 # si on arrive en début de ligne
            if x.pos.cg == y.pos.cg && a == 0 # si c'est le même état et qu'on a décidé de s'arrêter
                return 1, 1
            elseif x.pos.cg == y.pos.cg && a == 1 # si c'est le même état et qu'on a décidé de rejouer
                return 1, 1-p
            else
                return 0, 0
            end
        elseif y.pos.cg == x.pos.cg && a == 1 # si les deux états sont sur la même ligne et qu'on décide de rejouer
            if y.pos.tg == 2 # on peut passer de x à y en augmentant de 1
                return 0, p
            else
                return 0, 0
            end
        else
            return 0, 0
        end
    elseif x.pos.cg == y.pos.cg && a == 1 # si les deux états sont sur la même ligne et qu'on rejoue
        if x.gain+1 == y.gain
            return 0, p
        elseif y.pos.tg == 1 # si y est le 1er de la ligne
            return 1, 1-p
        else
            return 0, 0
        end
    elseif y.gain == x.gain && y.pos.tg == 1 && a == 0 # si les deux états sont sur la même colonne et qu'on s'arrête
        return 1, 1
    else
        return 0, 0
    end
end

function dynamic_programming_algorithm(Gmax, p)

    # X = states(Gmax)
    X = all_states(Gmax)
    T = floor(Int, 1/p*Gmax)
    #VT = 0
    #Vt = 0
    # list_V = []
    # list_pi = []
    list_Vt = [[Inf for j in 1:Gmax+2-i] for i in 1:Gmax+1]
    list_pit = [[-1 for j in 1:Gmax+2-i] for i in 1:Gmax+1]
    list_V = [list_Vt for i in 1:T]
    list_pi = [list_pit for i in 1:T]
    # t = 1
    #gain_x = X[Gmax+1][1]
    # xt = [State(Position(Gmax+1, 1), X[Gmax+1][1])] # liste des états accessibles à l'itération t-1
    # min_Gt = X[Gmax+1][1]
    #pos_x = [Gmax+1, 1]
    #pos_x = Position(Gmax+1, 1)
    policies = [0, 1] # s'arrêter ou rejouer 
    # ATTENTION : CHANGEMENT DANS POLICIES
    #while min_Gt != 0 # tant qu'on n'est pas revenu au gain de départ
    for t in T:-1:1
        #println(list_V)
        #println()
        # println("itération : ", t, ", le gain min vaut : ", min_Gt)
        println("itération : ", t)
        # list_Vt = initVt(Gmax)
        # list_pit = initPit(Gmax)
        # xt = accessibles_states(xt, Gmax)
        # for s in xt # ici je pense qu'il faut faire une boucle sur l'ensemble des états accessibles à cette itération
        for x in X
            
            # println("considérons l'état ",s)
            # if s.gain < min_Gt
            #     min_Gt = s.gain # J'AI L'IMPRESSION QUE CA RENTRE JAMAIS DANS CETTE BOUCLE
            #     println("on diminue le gain")
            # end

            Vt = Inf
            pi_t = -1
            # pos = s.pos
            for a in policies
                Q = 0 # cout optimal sachant qu'on est en x et qu'on prend la décision a
                # if a == 0 # si on décide de rejouer, on se déplace sur notre ligne de 1 à droite ou retour au départ
                #     #etats_accessibles = [[pos_x[1],1], [pos_x[1], pos_x[2]-1]]
                #     etats_accessibles = [State(Position(pos.cg,1), pos.cg-1)]
                #     probas_etats = [1-p]
                #     if s.gain+1<Gmax
                #         push!(etats_accessibles, State(Position(pos.cg, pos.tg+1), s.gain+1))
                #         push!(probas_etats, p)
                #     end
                # else # si on décide de s'arrêter, on se déplace verticalement
                #     #etats_accessibles = [[X[pos_x[1]][pos_x[2]]+1], 1]
                #     etats_accessibles = [State(Position(min(pos.cg+1, Gmax), 1), s.gain)]
                #     probas_etats = [1]
                # end

                # if pos_x[2] == 1
                #     etats_accessibles = [pos_x]
                #     for i in 2:pos_x[1]
                #         push!(etats_accessibles, [i, 1])
                #     end
                #     for i in 2:pos_x[2]
                #         push!(etats_accessibles, [pos_x[1], i])
                #     end
                # else
                #     etats_accessibles = [[pos_x[1], pos_x[2]-1]]
                # end

                for y in X
                # for i in 1:length(etats_accessibles)
                    # y = etats_accessibles[i]
                    #println("un voisin de cet état à l'itération suivante en suivant la politique ", a, " est ", y)

                    # c = 0
                    # if i==1
                    #     c += 1
                    # end
                    c, P = cout_trainsition_et_proba(x, y, a, p)

                    #if t==1
                    if t == T || x.gain == Gmax
                        Vtplus1_y = 0
                    else
                        # Vtplus1_y = list_V[T-t][y.pos.cg][y.pos.tg]
                        Vtplus1_y = list_V[t+1][y.pos.cg][y.pos.tg]
                    end
                    # Q += probas_etats[i]*(c+Vtplus1_y) 
                    # Q += P*(c+Vtplus1_y) 
                    Q += P*(c+Vtplus1_y) 
                end
                if x.gain == Gmax
                    Vt = 0
                    pi_t = 0
                end
                if Q < Vt
                    Vt = Q
                    pi_t = a
                end
            end

            list_V[t][x.pos.cg][x.pos.tg] = Vt
            list_pi[t][x.pos.cg][x.pos.tg] = pi_t
            # list_Vt[x.pos.cg][x.pos.tg] = Vt
            # list_pit[x.pos.cg][x.pos.tg] = pi_t
        end

        #push!(list_V, list_Vt)
        #push!(list_pi, list_pit)
        # t += 1
    end

    return list_V, list_pi
end

p = 0.5
Gmax = 10
lv, lpi = dynamic_programming_algorithm(Gmax, p)
println("la stratégie optimale est ", lpi)