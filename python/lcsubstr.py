'''
Created on Feb 12, 2016

@author: Jeffrey Thompson
'''

def test(a,b):
    if a == b:
        print("Pass")
    else:
        print("FAIL: received: {}, expected: {}".format(a,b))

def isPalPosible(word):
    chars = set()
    for ch in word:
        if ch in chars:
            chars.remove(ch)
        else:
            chars.add(ch)
    return len(chars) <= (1 if len(word) & 1 else 0)

test(isPalPosible('abcba'),True)
test(isPalPosible('abcbad'),False)
test(isPalPosible('abba'),True)
test(isPalPosible('a'),True)
test(isPalPosible(''),True)


def lcsubstrDP(A,B,K):
    dp = [[0 for _ in range(len(B))] for _ in range(len(B))]
    for ai,ac in enumerate(A):
        for bi,bc in enumerate(B):
            if ac == bc:
                dp[ai][bi] = 1 + (0 if bi == 0 or ai == 0 else dp[ai-1][bi-1])
                if dp[ai][bi] == K:
                    return A[ai-dp[ai][bi]+1:ai+1]
    return ''

test(lcsubstrDP('abcdefg','abcd',3),'abc')    
test(lcsubstrDP('abcdefg','xfcdefes',4),'cdef')    
test(lcsubstrDP('abcdefg','abcd',5),'')  
test(lcsubstrDP('abcdefg','',1),'')  

class trie:
    def __init__(self):
        self.root = {}
    
    def add(self, word):
        walker = self.root
        for ch in word:
            if ch in walker:
                walker = walker[ch]
            else:
                walker[ch] = {}
                walker = walker[ch]
        walker['*END*'] = word
    
    def __contains__(self, word):
        walker = self.root
        for ch in word:
            if ch in walker:
                walker = walker[ch]
            else:
                return False
        if '*END*' in walker:
            return True
        else:
            return False
        
def lcsubstrTrie(A,B,K):
    kstrings = trie()
    if len(B) < len(A):
        A,B = B,A
    for i in range(len(A)-K+1):
        kstrings.add(A[i:i+K])
    for i in range(len(B)-K+1):
        if B[i:i+K] in kstrings:
            return B[i:i+K]
    return ''

test(lcsubstrTrie('abcdefg','abcd',3),'abc')    
test(lcsubstrTrie('abcdefg','xfcdefes',4),'cdef')    
test(lcsubstrTrie('abcdefg','abcd',5),'')  
test(lcsubstrTrie('abcdefg','',1),'')  
