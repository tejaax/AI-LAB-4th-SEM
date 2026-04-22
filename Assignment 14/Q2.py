def backward_chaining(rules, known_facts, goal, visited):
    
    # If goal is already a known fact
    if goal in known_facts:
        return True

    # Avoid infinite loops
    if goal in visited:
        return False

    visited.add(goal)

    # Check all rules
    for conditions, result in rules:
        
        # If this rule can produce the goal
        if result == goal:

            # Check if ALL conditions can be proven
            all_true = True
            for condition in conditions:
                if not backward_chaining(rules, known_facts, condition, visited):
                    all_true = False
                    break

            if all_true:
                return True

    return False


rules_2a = [
    (['P'], 'Q'),
    (['R'], 'Q'),
    (['A'], 'P'),
    (['B'], 'R')
]

known_facts_2a = ['A', 'B']
goal_2a = 'Q'

result_2a = backward_chaining(
    rules_2a,
    known_facts_2a,
    goal_2a,
    set()
)

print("Test Case 2(a): Goal proven ->", result_2a)


rules_2b = [
    (['A'], 'B'),
    (['B', 'C'], 'D'),
    (['E'], 'C')
]

known_facts_2b = ['A', 'E']
goal_2b = 'D'

result_2b = backward_chaining(
    rules_2b,
    known_facts_2b,
    goal_2b,
    set()
)

print("Test Case 2(b): Goal proven ->", result_2b)