def is_safe(node, color, assignment, graph):
    for neighbor in graph[node]:
        if neighbor in assignment and assignment[neighbor] == color:
            return False
    return True


def backtrack(assignment, graph, colors):
    if len(assignment) == len(graph):
        return assignment

    unassigned = [node for node in graph if node not in assignment]
    node = unassigned[0]

    for color in colors:
        if is_safe(node, color, assignment, graph):
            assignment[node] = color

            result = backtrack(assignment, graph, colors)
            if result:
                return result

            del assignment[node]

    return None


def find_min_colors(graph):
    n = len(graph)

    for k in range(1, n + 1):
        colors = list(range(k))

        solution = backtrack({}, graph, colors)

        if solution:
            return k, solution

    return None, None



graph = {
    'Kutchh': ['Banaskantha', 'Patan', 'Surendranagar', 'Rajkot', 'Jamnagar'],
    
    'Banaskantha': ['Kutchh', 'Patan', 'Mehsana', 'Sabarkantha'],
    
    'Patan': ['Banaskantha', 'Mehsana', 'Surendranagar', 'Kutchh'],
    
    'Mehsana': ['Patan', 'Banaskantha', 'Sabarkantha', 'Gandhinagar', 'Ahmedabad'],
    
    'Sabarkantha': ['Banaskantha', 'Mehsana', 'Gandhinagar', 'Panchmahal', 'Kheda'],
    
    'Gandhinagar': ['Mehsana', 'Sabarkantha', 'Ahmedabad', 'Kheda'],
    
    'Ahmedabad': ['Mehsana', 'Gandhinagar', 'Kheda', 'Anand', 'Surendranagar', 'Bhavnagar'],
    
    'Kheda': ['Ahmedabad', 'Gandhinagar', 'Sabarkantha', 'Vadodara', 'Anand', 'Panchmahal'],
    
    'Panchmahal': ['Sabarkantha', 'Kheda', 'Vadodara', 'Dahod'],
    
    'Dahod': ['Panchmahal', 'Vadodara'],
    
    'Vadodara': ['Panchmahal', 'Dahod', 'Narmada', 'Bharuch', 'Anand', 'Kheda'],
    
    'Anand': ['Ahmedabad', 'Kheda', 'Vadodara', 'Bharuch'],
    
    'Bharuch': ['Vadodara', 'Narmada', 'Surat', 'Anand'],
    
    'Narmada': ['Vadodara', 'Bharuch', 'Surat'],
    
    'Surat': ['Bharuch', 'Narmada', 'Navsari', 'Dang'],
    
    'Navsari': ['Surat', 'Valsad', 'Dang'],
    
    'Valsad': ['Navsari', 'Dang'],
    
    'Dang': ['Surat', 'Navsari', 'Valsad'],
    
    'Bhavnagar': ['Ahmedabad', 'Surendranagar', 'Amreli', 'Rajkot'],
    
    'Amreli': ['Bhavnagar', 'Junagadh', 'Rajkot'],
    
    'Junagadh': ['Amreli', 'Rajkot', 'Porbandar'],
    
    'Porbandar': ['Junagadh', 'Rajkot', 'Jamnagar'],
    
    'Rajkot': ['Surendranagar', 'Amreli', 'Junagadh', 'Porbandar', 'Jamnagar', 'Bhavnagar', 'Kutchh'],
    
    'Jamnagar': ['Kutchh', 'Rajkot', 'Porbandar'],
    
    'Surendranagar': ['Kutchh', 'Patan', 'Ahmedabad', 'Rajkot', 'Bhavnagar']
}


min_colors, solution = find_min_colors(graph)


if solution:
    print(f"Minimum colors required: {min_colors}")
    for node in solution:
        print(f"{node} -> Color {solution[node]}")
else:
    print("No solution exists")

