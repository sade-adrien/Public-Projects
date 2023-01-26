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

#println(proba_legal_move(2, 12, 3))
#println(proba_legal_move(6, 7, 8))

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
