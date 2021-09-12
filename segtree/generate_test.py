import random
random.seed()

N = int(1e3)
count = int(1e3)

mas = []
for i in range(int(N)):
    mas.append(random.randint(0, 1e9))

def suma(mas, l, r):
    summ=0
    for i in range(l,r):
        summ+=mas[i]
    return summ

with open('input_generated.txt', 'w') as f:
    f.write(str(N)+" "+str(count)+"\n")
    for i in range(N):
        f.write(str(mas[i])+" ")
    f.write("\n")
    for i in range(int(count)):
        typ = random.randint(1,2)
        if typ==1:
            index=random.randint(0, N-1)
            value=random.randint(0, 1e9)
            mas[index]=value
            f.write(str(typ)+" "+str(index)+" "+str(value)+"\n")
        else:
            r=random.randint(1,N-1)
            l=random.randint(0,r-1)
            summ = suma(mas,l,r)
            f.write(str(typ)+" "+str(l)+" "+str(r)+" "+str(summ)+"\n")