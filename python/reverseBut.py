'''
Created on Feb 12, 2016

@author: Jeffrey Thompson
'''

def test(a,b):
    if a == b:
        print("Pass")
    else:
        print("FAIL: received: {}, expected: {}".format(a,b))

def reverseBut(s, but_these):
    s = list(s)
    low = 0
    high = len(s)-1
    while low < high:
        if s[low] in but_these:
            low+=1
        elif s[high] in but_these:
            high-=1
        else:
            s[low], s[high] = s[high], s[low]
            low+=1
            high-=1
    return ''.join(s)

exclude = 'aeiou '
s1 = 'hi there how are you'
s2 = reverseBut(s1,exclude)
print(s2)
s2 = reverseBut(s2,exclude)
test(s2,s1)

