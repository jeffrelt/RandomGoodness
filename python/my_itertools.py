def permutations(A, K=None):
    ''' lexicographical ordered permutations generator 
        If K is given only permutations of length K are yielded
        None sent for K: all permutations of all lengths will be yielded (different than itertools)
    '''
    if not K:
        yield tuple()
    A = tuple(A) # in case we were given an iterator of some sort
    build = [ [i] for i in reversed(range(len(A)))]
    while build:
        sofar = build.pop()
        if K == None:
            yield tuple(A[i] for i in sofar)
        elif len(sofar) == K:
            yield tuple(A[i] for i in sofar)
            continue
        s = set(sofar)
        for i in reversed(range(len(A))):
            if i not in s:
                build.append(sofar+[i])
            
        

def combinations(A, K=None):
    ''' lexicographical ordered combination generator 
        If K is given only combos of length K are yielded
        None sent for K: all combos of all lengths will be yielded (different than itertools)
    '''
    def reversed_enumerate(Iterable, start=0):
        ''' needed as you cannot reverse an enumeration '''
        last = len(Iterable) - 1 + start
        return ((last-i,x) for i,x in enumerate(reversed(Iterable)))
    
    if not K:
        yield tuple()
    A = tuple(A) # in case we were given an iterator of some sort
    build = [ (i, (x,)) for i,x in reversed_enumerate(A)]
    while build:
        last, sofar = build.pop()
        if K == None:
            yield sofar
        elif len(sofar) == K:
            yield sofar
            continue
        last+=1
        for i, x in reversed_enumerate(A[last:],last):
            build.append( (i, sofar+(x,)) )
        

if __name__ == '__main__':
    import itertools
    
    def check(A, B):
        if A == B:
            print("Pass")
        else:
            print("FAIL! \nrecieved : {} \nexpecting: {}".format(str(A),str(B)))
    
    
    s = '123456'
    print("Testing combinations:")
    r1 = list(combinations(s,2))
    r2 = list(itertools.combinations(s,2))
    check(r1,r2)
    
    r1 = list(combinations(s,3))
    r2 = list(itertools.combinations(s,3))
    check(r1,r2)
    
    r1 = list(combinations(s))
    r2 = sorted(sum((list(itertools.combinations(s,l))
             for l in range(len(s)+1)), []))
    check(r1,r2)
    print("Testing permutations:")
    r1 = list(permutations(s,2))
    r2 = list(itertools.permutations(s,2))
    check(r1,r2)
    
    r1 = list(permutations(s,3))
    r2 = list(itertools.permutations(s,3))
    check(r1,r2)
    
    r1 = list(permutations(s))
    r2 = sorted(sum((list(itertools.permutations(s,l))
             for l in range(len(s)+1)), []))
    check(r1,r2)
