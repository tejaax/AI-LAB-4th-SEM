import itertools

class Symbol:
    def __init__(self, name):
        self.name = name 

    def __repr__(self):
        return self.name

class LogicEngine:
    # Basic Connectives (Unary and Binary) 
    @staticmethod
    def NOT(p): return not p
    
    @staticmethod
    def OR(p, q): return p or q
    
    @staticmethod
    def AND(p, q): return p and q
    
    @staticmethod
    def CONDITIONAL(p, q): return (not p) or q
    
    @staticmethod
    def BICONDITIONAL(p, q): return p == q

    def print_truth_table(self, expression_func, symbols, label):
        # Generate header [cite: 44, 45]
        header = [s.name for s in symbols] + [label]
        print(" | ".join(header))
        print("-" * len(" | ".join(header)))

        # Generate all 2^n boolean combinations 
        for values in itertools.product([False, True], repeat=len(symbols)):
            val_map = dict(zip([s.name for s in symbols], values))
            result = expression_func(val_map)
            
            # Use T/F for readable truth tables 
            row = ["T" if v else "F" for v in values] + ["T" if result else "F"]
            print(" | ".join(row))
        print("\n")

# Initialize Symbols [cite: 40]
P, Q, R = Symbol('P'), Symbol('Q'), Symbol('R')
engine = LogicEngine()

# --- SOLUTIONS FOR ALL 10 PROPOSITIONS  ---

print("TRUTH TABLES FOR ASSIGNMENT 13:\n")

# 1. ~P -> Q [cite: 47]
engine.print_truth_table(lambda m: engine.CONDITIONAL(engine.NOT(m['P']), m['Q']), [P, Q], "~P -> Q")

# 2. ~P ^ ~Q [cite: 48]
engine.print_truth_table(lambda m: engine.AND(engine.NOT(m['P']), engine.NOT(m['Q'])), [P, Q], "~P ^ ~Q")

# 3. P v ~Q [cite: 49]
engine.print_truth_table(lambda m: engine.OR(m['P'], engine.NOT(m['Q'])), [P, Q], "P V ~Q")

# 4. ~P -> Q [cite: 50]
engine.print_truth_table(lambda m: engine.CONDITIONAL(engine.NOT(m['P']), m['Q']), [P, Q], "~P -> Q")

# 5. ~P <-> ~Q [cite: 51]
engine.print_truth_table(lambda m: engine.BICONDITIONAL(engine.NOT(m['P']), engine.NOT(m['Q'])), [P, Q], "~P <-> ~Q")

# 6. (P v Q) ^ (~P -> Q) [cite: 52]
engine.print_truth_table(lambda m: engine.AND(engine.OR(m['P'], m['Q']), engine.CONDITIONAL(engine.NOT(m['P']), m['Q'])), [P, Q], "(P v Q) ^ (~P -> Q)")

# 7. (P v Q) -> ~R [cite: 53]
engine.print_truth_table(lambda m: engine.CONDITIONAL(engine.OR(m['P'], m['Q']), engine.NOT(m['R'])), [P, Q, R], "(P v Q) -> ~R")

# 8. ((P v Q) -> ~R) <-> ((~P ^ ~Q) -> ~R) [cite: 54]
def prop_8(m):
    lhs = engine.CONDITIONAL(engine.OR(m['P'], m['Q']), engine.NOT(m['R']))
    rhs = engine.CONDITIONAL(engine.AND(engine.NOT(m['P']), engine.NOT(m['Q'])), engine.NOT(m['R']))
    return engine.BICONDITIONAL(lhs, rhs)
engine.print_truth_table(prop_8, [P, Q, R], "Prop 8")

# 9. ((P -> Q) ^ (Q -> R)) -> (P -> R) [cite: 55] (Note: Fixed standard Syllogism)
def prop_9(m):
    hypothesis = engine.AND(engine.CONDITIONAL(m['P'], m['Q']), engine.CONDITIONAL(m['Q'], m['R']))
    return engine.CONDITIONAL(hypothesis, engine.CONDITIONAL(m['P'], m['R']))
engine.print_truth_table(prop_9, [P, Q, R], "Prop 9 (Syllogism)")

# 10. (P -> (Q v R)) -> (~P ^ ~Q ^ ~R) [cite: 56]
def prop_10(m):
    lhs = engine.CONDITIONAL(m['P'], engine.OR(m['Q'], m['R']))
    rhs = engine.AND(engine.NOT(m['P']), engine.AND(engine.NOT(m['Q']), engine.NOT(m['R'])))
    return engine.CONDITIONAL(lhs, rhs)
engine.print_truth_table(prop_10, [P, Q, R], "Prop 10")