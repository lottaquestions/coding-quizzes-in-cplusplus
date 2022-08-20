def rodCutting(n, Price):
    #Table = [0 for d in range(len(Price)+1)]
    Table = {d:0 for d in range(1,len(Price)+1)}
    Cuts = [0 for d in range(len(Price)+1)]
    for length in range(1,len(Price)+1):
        for i in range(1,length+1):
            tmp = Price[i] + (Table[length-i] if (length-i) in Table else 0)
            if tmp > Table[length]:
                Table[length] = tmp
                Cuts[length] = i

    orderOfCutsToMaximize = []
    while n > 0:
        orderOfCutsToMaximize.append(Cuts[n])
        n -= Cuts[n]
    return Table, orderOfCutsToMaximize

rodPrices,res = rodCutting(8, {1:3, 2:5, 3:8, 4:9, 5:10, 6:17, 7:17, 8:20})

print("Rod prices", rodPrices, "Resulting cuts", res)