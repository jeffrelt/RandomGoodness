'''
You are given a sequence of black and white horses, and a set of k stables numbered 1 to k. 
You have to accommodate the horses into the stables in such a way that the following conditions are satisfied: 

a. You fill the horses into the stables preserving the order of horses. For instance, you cannot put for horse 1 
into stable 2 and horse 2 into stable 1. You have to preserve the ordering of horses. 

b. No stable should be empty and No horse should be left unaccommodated. 

c. Take the product (number of white horses * number of black horses) for each stable and take the sum of all these products. 
This value should be the minimum among all possible accommodation arrangements.
'''

class result:
    def __init__(self, so_far = 0, white = 0, black = 0):
        self.so_far = so_far;
        self.color = [white,black]
    
    def add(self, horse):
        temp = result(self.so_far,self.color[0],self.color[1])
        temp.color[horse]+=1
        return temp
        
    def next(self, horse=None):
        temp = result(self.score())
        if horse != None:
            temp.color[horse]+=1
        return temp
            
    def score(self):
        return self.so_far + self.color[0]*self.color[1]

def dpHorses(colors, stable_count):
    ''' dp solution - actually easier than the recursive one (certainly to debug)'''
    dp = [[None for _ in range(stable_count)] for _ in range(len(colors))]
    for i, horse in enumerate(colors):
        for stable in range(min(stable_count,i+1)):
            if i == 0:
                dp[i][stable] = result().add(horse)
            elif stable == 0:
                dp[i][stable] = dp[i-1][stable].add(colors[horse])
            elif i == stable:
                dp[i][stable] = result().add(colors[horse])
            else:
                a = dp[i-1][stable].add(colors[horse])
                b = dp[i-1][stable-1].next(colors[horse])
                dp[i][stable] = a if a.score() < b.score() else b
                
    return dp[len(colors)-1][stable_count-1].score()
    

def Horses(colors, stable_count):
    ''' just calls the recursive functions '''
    a = recHorses(colors,stable_count, len(colors)-1, stable_count).add(colors[-1])
    if stable_count <= 1:
        return a.score()
    b = recHorses(colors,stable_count, len(colors)-1, stable_count-1)

    return min(a.score(), b.score())

def recHorses(colors, stable_count, horse, stable):
    horse-=1

    if horse == 0:
        if stable == 1:
            temp = result().add(colors[0])
            return temp
        else:
            raise RuntimeError("Stable must be 1 when count is 0")
    if stable == 1:
        a = recHorses(colors,stable_count, horse, stable).add(colors[horse])
        return a
    elif stable == horse+1:
        return result().add(colors[horse])
    a = recHorses(colors,stable_count, horse, stable).add(colors[horse])
    b = recHorses(colors,stable_count, horse, stable-1).next(colors[horse])
    if a.score() < b.score():
        return a
    else:
        return b
    
print( dpHorses([0,1,0,0,0,1,1,1,0],2))
