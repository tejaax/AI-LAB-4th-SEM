def solve_send_more_money():
    solutions = []
    M = 1
    for c1 in [0, 1]:
        for c2 in [0, 1]:
            for c3 in [0, 1]:
                for S in range(1, 10): 
                    if S == M:
                        continue
                    O = S + M + c3 - 10
                    if O < 0 or O > 9 or O in {S, M}:
                        continue    
                    for E in range(0, 10):
                        if E in {S, M, O}:
                            continue
                        N = E + O + c2 - 10 * c3
                        if N < 0 or N > 9 or N in {S, M, O, E}:
                            continue

                        for R in range(0, 10):
                            if R in {S, M, O, E, N}:
                                continue
                            # From: N + R + c1 = E + 10*c2
                            if (N + R + c1) % 10 != E:
                                continue
                            if (N + R + c1) // 10 != c2:
                                continue
                            for D in range(0, 10):
                                if D in {S, M, O, E, N, R}:
                                    continue
                                Y = D + E - 10 * c1
                                if Y < 0 or Y > 9:
                                    continue
                                if Y in {S, M, O, E, N, R, D}:
                                    continue
                                SEND  = 1000*S + 100*E + 10*N + D
                                MORE  = 1000*M + 100*O + 10*R + E
                                MONEY = 10000*M + 1000*O + 100*N + 10*E + Y
                                if SEND + MORE == MONEY:
                                    solutions.append((S, E, N, D, M, O, R, Y))

    return solutions

solutions = solve_send_more_money()

for sol in solutions:
    S, E, N, D, M, O, R, Y = sol

    SEND  = 1000*S + 100*E + 10*N + D
    MORE  = 1000*M + 100*O + 10*R + E
    MONEY = 10000*M + 1000*O + 100*N + 10*E + Y

    print("Solution Found:")
    print(f"S={S}, E={E}, N={N}, D={D}, M={M}, O={O}, R={R}, Y={Y}")
    print(f"{SEND} + {MORE} = {MONEY}")