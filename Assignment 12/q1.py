domains = {
    "P1": ["R1","R2","R3"],
    "P2": ["R1","R2","R3"],
    "P3": ["R1","R2","R3"],
    "P4": ["R1","R2","R3"],
    "P5": ["R1","R2","R3"],
    "P6": ["R1","R2","R3"]
}

constraints = {
    "P1": ["P2","P3","P6"],
    "P2": ["P1","P3","P4"],
    "P3": ["P1","P2","P5"],
    "P4": ["P2","P6"],
    "P5": ["P3","P6"],
    "P6": ["P1","P4","P5"]
}

def revise(i,j):
    revised=False

    for value in domains[i][:]:
        supported=False
        for other in domains[j]:
            if value!=other:
                supported=True
                break

        if not supported:
            domains[i].remove(value)
            revised=True

    return revised

def ac_3():
  q=[]
  for i in constraints:
    for j in constraints[i]:
      q.append((i,j))
  count=0
  while len(q)!=0:
    count+=1
    i,j=q.pop(0)
    change=revise(i,j)
   
    
    if count<=5:
      if change==True:
        print(f"{i}->{j} checked → Domain Reduced")
      else:
        print(f"{i}->{j} checked → No Change")
    if change:     
      if len(domains[i])==0 :
        return False
      for k in constraints[i]:
        if k==j:
          continue
        q.append((k,i))
  return True

domains["P1"]=["R1"]
if ac_3():
    print("Arc consistent")
    print(domains)
else:
    print("Failure")